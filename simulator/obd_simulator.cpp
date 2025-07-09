#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>

int rpm = 0;

void* simRPM(void* arg) {
    while (1) {
        rpm = rand() % 4000 + 800;
        usleep(500000);
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, simRPM, NULL);

    int master_fd = posix_openpt(O_RDWR);
    if (master_fd < 0) {
        perror("Error opening posix_openpt");
        exit(1);
    }

    grantpt(master_fd);
    unlockpt(master_fd);
    char *slave_path = ptsname(master_fd);
    printf("OBD sim is available on: %s\n", slave_path);

    while (1) {

        char buffer[256] = {0};
        int n = read(master_fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Dashboard request: %s\n", buffer);

            if (strstr(buffer, "010C")) {
                int val = rpm * 4;
                int A = ((val >> 8) & 0xFF);
                int B = val & 0xFF;

                char response[64];
                snprintf(response, sizeof(response), "41 0C %02X %02X\r", A, B);
                write(master_fd, response, strlen(response));

            } else {
                write(master_fd, "NO DATA\r", 8);
            }
        }
    }

    // Engine Speed PID = 0C (returns 2 Bytes)
    // Vehicle Speed PID = 0D (returns 1 Byte)

}
