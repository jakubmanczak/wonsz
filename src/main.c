#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <SDL.h>

#include "gameloop.h"

SDL_Window *window = NULL; SDL_Renderer *renderer = NULL;
SDL_Texture *gametex = NULL;
int quit = 0;

// frame limiting
u_int32_t timenext;
uint32_t timeleft(){
  uint32_t now;
  now = SDL_GetTicks();
  if(timenext <= now) return 0;
  else return timenext - now;
}

void boot(){
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow(
    "wonsz", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    1280, 720, 0
  );
  renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_PRESENTVSYNC
  );
  gametex = SDL_CreateTexture(
    renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
    mapw, maph
  );

  srand(time(NULL));
  InitGameVars();
}

void loop(){

  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT) quit = 1;
  }
  keys = SDL_GetKeyboardState(NULL);

  DoGameRoutines();

  SDL_SetRenderTarget(renderer, gametex);
  DrawGameTex(renderer);
  SDL_SetRenderTarget(renderer, NULL);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, gametex, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_Delay(timeleft());
  timenext += (1000 / desiredfps);
}

int main(int argc, char **argv){
  boot();

  timenext = SDL_GetTicks() + (1000 / desiredfps);
  while(!quit) loop();

  SDL_DestroyTexture(gametex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}