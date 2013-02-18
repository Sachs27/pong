/**
 * pong.h
 */
#ifndef PONG_PONG_H
#define PONG_PONG_H

#include <SDL/SDL.h>

#include "ball.h"
#include "paddle.h"

typedef struct pong {
    SDL_Surface *screen;
    SDL_Rect rect;

    ball_t ball;
    paddle_t player;
    paddle_t computer;
}pong_t;

int pong_create_ball(pong_t *pong);
void pong_destroy_ball(pong_t *pong);
int pong_create_player(pong_t *pong);
void pong_destroy_player(pong_t *pong);
int pong_update(pong_t *pong, unsigned long delta);
int pong_render(pong_t *pong);

#endif
