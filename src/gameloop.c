#include "gameloop.h"

int mapw = 32;
int maph = 18;
int desiredfps = 8;

player p;
int keyUp;
int keyRight;
int keyDown;
int keyLeft;

SDL_Point apple;

void InitGameVars(){
  p.pos.x = rand() % mapw; p.pos.y = rand() % maph;
  p.direction = DIRECTION_UNDEFINED;
  p.incr = 0; p.len = 0; p.posHistory = NULL;

  apple.x = p.pos.x; apple.y = p.pos.y;
  while(apple.x == p.pos.x) apple.x = rand() % mapw;
  while(apple.y == p.pos.y) apple.y = rand() % maph;
}

void DoGameRoutines(){
  if(keyUp) p.direction = DIRECTION_UP;
  if(keyRight) p.direction = DIRECTION_RIGHT;
  if(keyDown) p.direction = DIRECTION_DOWN;
  if(keyLeft) p.direction = DIRECTION_LEFT;

  if(p.incr){
    p.incr = 0; p.len += 1;
    p.posHistory = realloc(p.posHistory, p.len * sizeof(SDL_Point));
  }

  if(p.len){
    for(int i = p.len - 1; i ; i--){
      *(p.posHistory + i) = *(p.posHistory + (i - 1));
    }
    *p.posHistory = p.pos;
  }

  if(p.direction == DIRECTION_UP) p.pos.y -= 1;
  if(p.direction == DIRECTION_RIGHT) p.pos.x += 1;
  if(p.direction == DIRECTION_DOWN) p.pos.y += 1;
  if(p.direction == DIRECTION_LEFT) p.pos.x -= 1;

  if(p.pos.x == apple.x && p.pos.y == apple.y){
    p.incr = 1; int run = 1;
    while(run){
      apple.x = rand() % mapw; apple.y = rand() % maph; run = 0;
      if(p.pos.x == apple.x && p.pos.y == apple.y) run = 1;
      for(int i = 0; i < p.len; i++){
        if(p.pos.x == (p.posHistory + i)->x && p.pos.y == (p.posHistory + i)->y){
          run = 1;
        }
      }
    }
  }

  if(p.pos.x < 0 || p.pos.x >= mapw || p.pos.y < 0 || p.pos.y >= maph) InitGameVars();
  for(int i = 0; i < p.len; i++){
    if(
      p.pos.x == (p.posHistory + i)->x &&
      p.pos.y == (p.posHistory + i)->y
    ) InitGameVars();
  }
}

void DrawGameTex(SDL_Renderer *r){
  SDL_Rect rect; rect.w = 1; rect.h = 1;

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(r);

  // apple
  rect.x = apple.x; rect.y = apple.y;
  SDL_SetRenderDrawColor(r, 0xFF, 0x77, 0x77, 0xFF);
  SDL_RenderFillRect(r, &rect);

  // pos history
  if(p.len){
    for(int i = 0; i < p.len; i++){
      rect.x = (p.posHistory + i)->x; rect.y = (p.posHistory + i)->y;
      SDL_SetRenderDrawColor(r, 0x77, 0x77, 0x77, 0xFF);
      SDL_RenderFillRect(r, &rect);
    }
  }

  // current pos
  rect.x = p.pos.x; rect.y = p.pos.y;
  SDL_SetRenderDrawColor(r, 0xCC, 0xCC, 0xCC, 0xFF);
  SDL_RenderFillRect(r, &rect);
}