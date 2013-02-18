/**
 * ball.c
 */

#include "ball.h"

/**
 *  static func
 */
static int
ball_collided(ball_t *ball, int *obstacle_index)
{
    int i;

    i = ball->obstacle_count;
    while (i--) {
        if (line2_distance(ball->obstacles + i, ball->pos) <= ball->radius) {
            if (obstacle_index) {
                *obstacle_index = i;
            }
            return 1;
        }
    }
    return 0;
}

/**
 *  extern func
 */
void
ball_draw(ball_t *ball, SDL_Surface *dst, SDL_Rect *dst_rect)
{
    SDL_Rect rect;

    rect.x = (int)(ball->pos.x - ball->radius + (dst_rect ? dst_rect->x : 0));
    rect.y = (int)(ball->pos.y - ball->radius + (dst_rect ? dst_rect->y : 0));
    rect.w = ball->radius * 2;
    rect.h = ball->radius * 2;
    SDL_BlitSurface(ball->res.image, &ball->res.rect, dst, &rect);
    return ;
}

void
ball_move(ball_t *ball, int delta)
{
    vector2_t delta_pos;
    int obstacle_index;

    delta_pos = vector2_mul(ball->v, 0.001f * delta);
    ball->pos = vector2_add(ball->pos, delta_pos);
    if (ball->on_collided && ball_collided(ball, &obstacle_index)) {
        ball->pos = vector2_add(ball->pos, vector2_reverse(delta_pos));
        ball->on_collided(ball, obstacle_index);
    }
    return ; 
}

void
ball_set_obstacles(ball_t *ball, line2_t *obstacles, size_t count)
{
    int i = count;

    while (i--) {
        ball->obstacles[i] = obstacles[i];
    }
    return ;
}

