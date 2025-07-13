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
#include <iostream>


int main() {
    
    // initialise window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Dashboard",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        930, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    
    if (TTF_Init() == -1){
      std::cerr << "TTF_Init Error" << TTF_GetError() << std::endl;
      exit(1);
    }

    TTF_Font* myFont = TTF_OpenFont("../assets/DejaVuSerif-Italic.ttf", 32);
    if(myFont == nullptr){
      std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
      exit(1);
    }

    // Pixels from the text
    SDL_Surface* surfaceText = TTF_RenderText_Solid(myFont, getRPM(), {255, 255, 255});

    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);

    // Free the surface
    SDL_FreeSurface(surfaceText);

    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 930;
    rectangle.h = 720;

    bool isRunning = true;

    while (isRunning){
      SDL_Event event;
      
      // Handlng Input
      while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
          isRunning = false;
        }
      }
      
      // Handle Updates
      SDL_Surface* surfaceText = TTF_RenderText_Solid(myFont, getRPM(), {255, 255, 255});
      SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
      SDL_FreeSurface(surfaceText);

      // Clear and Draw screen
      SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      // Render the text on a rectangle
      SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
      
      // Show what has been drawn
      SDL_RenderPresent(renderer);

      sleep(1);
    }

    SDL_DestroyTexture(textureText);

    SDL_DestroyWindow(win);
    
    SDL_Quit();
    return 0;
}
