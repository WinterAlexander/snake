#include "main.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL, *icon = NULL, *score = NULL;
    SDL_Event event;

    icon = IMG_Load("favicon.bmp");

    TTF_Init();

    TTF_Font *font = NULL;
    font = TTF_OpenFont("font.ttf", 16);

    SDL_Rect score_position;

    score_position.x = 0;
    score_position.y = 350;

    char reset = 1;
    char run = 1;
    long number;
    char result[20] = "";
    SDL_Color ttf_white = {255, 255, 255};

    while(run)
    {
        if(reset)
        {
            screen = video_init(400, 400);
            SDL_WM_SetCaption("Snake", NULL);
            SDL_WM_SetIcon(icon, NULL);
            FILE* snake_ts = NULL;
            snake_ts = fopen("game.sc", "r");

            if(snake_ts == NULL)
            {
                number = 0;
            }
            else
            {
                fscanf(snake_ts, "%ld", &number);
                fclose(snake_ts);
            }

            sprintf(result, "Best score: %ld", number);
            score = TTF_RenderText_Blended(font, result, ttf_white);
            SDL_BlitSurface(score, NULL, screen, &score_position);
            SDL_Flip(screen);
            reset = 0;
        }

        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            run = 0;
            break;


        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(play(screen) == 1)
                {
                    run = 0;
                }
                reset = 1;
            }
            break;
        }
    }

    TTF_CloseFont(font);
    return EXIT_SUCCESS;
}
