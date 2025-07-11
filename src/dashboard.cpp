//
// Created by pcuser on 7/9/25.
//

#include "dashboard.h"
#include "obd.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_main.h>

#include <stdlib.h>
#include <unistd.h>


int main() {

    // initialise window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Dashboard",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        930, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    sleep(5);
    return 0;
}
