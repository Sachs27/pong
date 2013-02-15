/**
 * pong.c
 */

#include "pong.h"
#include "log.h"

static SDL_Surface *s_image_pong = 0;
static int s_image_pong_ref_count = 0;

/**
 *  static func
 */
static void s_ball_on_collided(ball_t *ball, size_t obstacle_index)
{
    float tmp;
    vector2_t normal;

    Mix_PlayChannel(-1, ball->res.sound_collided, 0);
    normal = line2_normal(ball->obstacles + obstacle_index);
    if (vector2_dot(normal, ball->v) > 0) {
        normal = vector2_reverse(normal);
    }
    normal = vector2_normalize(normal);
    tmp = vector2_dot(ball->v, normal);
    normal = vector2_mul(normal, tmp);
    normal = vector2_reverse(normal);
    ball->v = vector2_add(normal, vector2_add(ball->v, normal));
    return ;
}

static SDL_Surface *load_image_pong()
{
    log_enter_func(__func__);

    if (s_image_pong_ref_count == 0) {
        s_image_pong = SDL_LoadBMP("res/pong.bmp");
        if (s_image_pong) {
            Uint32 color_key;

            color_key = SDL_MapRGB(s_image_pong->format, 0xff, 0, 0xff);
            SDL_SetColorKey(s_image_pong, SDL_SRCCOLORKEY, color_key);
            ++s_image_pong_ref_count;
            log_put_msg_in_func("load res/pong.bmp success.\n");
        }
    } else {
        ++s_image_pong_ref_count;
    }

    log_leave_func(__func__);
    return s_image_pong;
}

static void free_image_pong()
{
    log_enter_func(__func__);
    --s_image_pong_ref_count;
    if (s_image_pong_ref_count == 0) {
        SDL_FreeSurface(s_image_pong);
        s_image_pong = 0;
        log_put_msg_in_func("free res/pong.bmp.\n");
    }
    log_leave_func(__func__);
    return ;
}

/**
 *  extern func
 */

int pong_create_ball(pong_t *pong)
{
    log_enter_func(__func__);

    if (!pong) {
        return -1;
    }

    pong->ball.res.image = load_image_pong();
    if (!pong->ball.res.image) {
        return -1;
    }

    pong->ball.res.sound_collided = Mix_LoadWAV("res/collided.wav");
    if (!pong->ball.res.sound_collided) {
        return -1;
    }

    pong->ball.res.rect.x = 100;
    pong->ball.res.rect.y = 0;
    pong->ball.res.rect.w = 20;
    pong->ball.res.rect.h = 20;

    pong->ball.pos.x = pong->rect.w / 2.0f;
    pong->ball.pos.y = pong->rect.h / 2.0f;
    pong->ball.v.x = 50.0f;
    pong->ball.v.y = 30.0f;
    pong->ball.on_collided = s_ball_on_collided;
    pong->ball.radius = 10.0f;
    pong->ball.obstacle_count = 4;
    pong->ball.obstacles = (line2_t *)malloc(                                  \
                            line2_s * pong->ball.obstacle_count);
    {
        int i;
        line2_t ob[4] = {
            {
                {pong->rect.w-1, 0},
                {pong->rect.w-1, pong->rect.h-1}
            },
            {
                {0,0},
                {0, pong->rect.h-1}
            },
            {
                {0,0},
                {pong->rect.w-1, 0}
            },
            {
                {0, pong->rect.h-1},
                {pong->rect.w-1, pong->rect.h-1}
            }
        };
        i = pong->ball.obstacle_count;
        while (i--) {
            pong->ball.obstacles[i] = ob[i];
        }
    }

    log_leave_func(__func__);
    return 0;
}

void pong_destroy_ball(pong_t *pong)
{
    log_enter_func(__func__);

    if (!pong) {
        return ;
    }

    if (pong->ball.res.image) {
        free_image_pong();
        pong->ball.res.image = 0;
    }

    if (pong->ball.res.sound_collided) {
        Mix_FreeChunk(pong->ball.res.sound_collided);
        pong->ball.res.sound_collided = 0;
    }

    if (pong->ball.obstacles) {
        free(pong->ball.obstacles);
        pong->ball.obstacles = 0;
    }

    log_leave_func(__func__);
    return ;
}

int pong_create_player(pong_t *pong)
{
    log_enter_func(__func__);

    if (!pong) {
        return -1;
    }

    pong->player.res.image = load_image_pong();
    if (!pong->player.res.image) {
        return -1;
    }
    pong->player.res.rect.x = 0;
    pong->player.res.rect.y = 0;
    pong->player.res.rect.w = 100;
    pong->player.res.rect.h = 20;

    pong->player.half_width = 50.f;
    pong->player.half_height = 10.f;
    pong->player.pos.x = pong->rect.w / 2.f;
    pong->player.pos.y = pong->rect.h - pong->player.half_height;

    log_leave_func(__func__);
    return 0;
}

void pong_destroy_player(pong_t *pong)
{
    log_enter_func(__func__);

    if (!pong) {
        return ;
    }

    if (pong->player.res.image) {
        free_image_pong();
        pong->player.res.image = 0;
    }
    log_leave_func(__func__);
    return ;
}

int pong_update(pong_t *pong, int delta)
{
    ball_move(&pong->ball, delta);
    return 0;
}

int pong_render(pong_t *pong)
{
    static Uint32 clear_color = 0;
    int i;

    if (!clear_color) {
        clear_color = SDL_MapRGB(pong->screen->format, 0xff, 0xff, 0xff);
    }

    SDL_FillRect(pong->screen, &pong->rect, clear_color);
    ball_draw(&pong->ball, pong->screen, &pong->rect);
    paddle_draw(&pong->player, pong->screen, &pong->rect);
    SDL_UpdateRect(pong->screen, pong->rect.x, pong->rect.y,                   \
                           pong->rect.w, pong->rect.h);
    return 0;
}
