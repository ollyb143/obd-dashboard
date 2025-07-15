//
// Created by pcuser on 7/9/25.
//

#include "obd.h"

#define TEST_RPM "41 0C 2B 1F"

const int MAX_RPM = 6000;
const int MIN_RPM = 800;

char response[64];

const int getRPM(int* rpm, char* buffer, size_t size){

  /*
  srand(time(NULL));
  rpm[0] = rand() % (MAX_RPM - MIN_RPM) + MIN_RPM;
  snprintf(buffer, size, "%d", rpm[0]);
  return 1;
  */

  // Generating random RPM value for testing without OBD2
  srand(time(NULL));
  int rpmNo = rand() % (MAX_RPM - MIN_RPM) + MIN_RPM;

  // Converting RPM into Hex OBD PID message
  int val = rpmNo * 4;
  int rpmA = ((val >> 8) & 0xFF);
  int rpmB = val & 0xFF;

  snprintf(response, sizeof(response), "41 0C %02X %02X", rpmA, rpmB);

  // Handling rpm response value
  int A, B;

  if(sscanf(response, "41 0C %X %X", &A, &B) == 2) {
    *rpm = ((A << 8) | B) / 4;
    sprintf(buffer, "%d", *rpm);
    return 1;
  } else {
    fprintf(stderr, "Invalid response format: %s\n", response);
    return -1;
  }

}
