#include "pong.h"

int main(int argc, char *argv[])
{
    pong_t pong;
    int quit;
    unsigned long last_ticks, delta_ticks;
    SDL_Event e;

    log_enter_func(__func__);
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    pong.screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    if (!pong.screen) {
        log_put_msg_in_func("SDL_SetVideoMode FAILED\n");
        goto EXIT;
    }
    SDL_WM_SetCaption("Pong", 0);
    pong.rect.x = 0;
    pong.rect.y = 0;
    pong.rect.w = 320;
    pong.rect.h = 480;

    if (pong_create_ball(&pong) != 0) {
        log_put_msg_in_func("pong_create_ball FAILED\n");
        goto EXIT;
    }

    if (pong_create_player(&pong) != 0) {
        log_put_msg_in_func("pong_create_player FAILED\n");
        goto EXIT;
    }
    
    quit = 0;
    last_ticks = SDL_GetTicks();
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = !quit;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = !quit;
                }
            }
        }
        if ((delta_ticks = SDL_GetTicks() - last_ticks) < 33) {
            SDL_Delay(3);
        } else {
            pong_update(&pong, delta_ticks);
            pong_render(&pong);
            last_ticks += 33;
        }
    }
EXIT:
    pong_destroy_ball(&pong);
    pong_destroy_player(&pong);
    Mix_CloseAudio();
    SDL_Quit();
    log_leave_func(__func__);
    return 0;
}
