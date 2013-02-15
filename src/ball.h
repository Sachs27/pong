/**
 * ball.h
 */

#ifndef BALL_H
#define BALL_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "line2.h"

typedef struct ball_res {
    SDL_Surface *image;
    SDL_Rect rect;
    Mix_Chunk *sound_collided;
} ball_res_t;

typedef struct ball ball_t;
struct ball {
    vector2_t pos;
    float radius;

    vector2_t v;

    line2_t *obstacles;
    size_t obstacle_count;

    ball_res_t res;

    void (*on_collided)(ball_t *ball, size_t obstacle_index);
};
#define ball_s sizeof(ball_t)

void ball_set_obstacles(ball_t *ball, line2_t *obstacles, size_t count);
void ball_move(ball_t *ball, int delta);
void ball_draw(ball_t *ball, SDL_Surface *dst, SDL_Rect *dst_rect);

#endif
