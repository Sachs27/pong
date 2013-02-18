/**
 * paddle.c
 */

#include "paddle.h"

void
paddle_draw(paddle_t *paddle, SDL_Surface *dst, SDL_Rect *dst_rect)
{
    SDL_Rect rect;

    rect.x = (int)(paddle->pos.x - paddle->half_width                          \
              + (dst_rect ? dst_rect->x : 0));
    rect.y = (int)(paddle->pos.y - paddle->half_height                         \
              + (dst_rect ? dst_rect->y : 0));
    rect.w = paddle->half_width * 2;
    rect.h = paddle->half_height * 2;
    SDL_BlitSurface(paddle->res.image, &paddle->res.rect, dst, &rect);
    return ;
}

