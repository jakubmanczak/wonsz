#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef enum direction{
  DIRECTION_UNDEFINED,
  DIRECTION_UP, DIRECTION_RIGHT,
  DIRECTION_DOWN, DIRECTION_LEFT
} direction;

typedef struct player{
  SDL_Point pos;
  direction direction;

  int len; int incr;
  SDL_Point *posHistory;
} player;

extern int mapw;
extern int maph;
extern int desiredfps;

extern player p;
extern int keyUp;
extern int keyRight;
extern int keyDown;
extern int keyLeft;

extern SDL_Point apple;

/// @brief initialises game variables
void InitGameVars();

/// @brief executes game routines
void DoGameRoutines();

/// @brief draws to SDL_Texture *gametex
void DrawGameTex(SDL_Renderer *r);

#endif