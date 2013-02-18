/**
 * paddle.h
 *
 * TODO:
 *   [*]移动挡板的功能。
 */
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL/SDL.h>

#include "vector2.h"

typedef struct paddle_res {
    SDL_Surface *image;
    SDL_Rect rect;
} paddle_res_t;

typedef struct paddle {
    vector2_t pos;
    float horizontal_speed;
    float half_width;
    float half_height;

    paddle_res_t res;
} paddle_t;
#define paddle_s sizeof(paddle_t)

void paddle_draw(paddle_t *paddle, SDL_Surface *dst, SDL_Rect *dst_rect);
void paddle_move(paddle_t *paddle, unsigned long delta);

#endif
