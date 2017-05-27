#include "main.h"
#include "game.h"

char play(SDL_Surface *screen)
{
    char quit = 0;
    char run = 1;
    char direction = UP;
    char food = 0;
    int lenght = 1;
    long score = 0;
    char snake_head_found = 0;
    int b;

    char x;
    char y;

    srand(time(NULL));

    putenv("SDL_VIDEO_WINDOW_POS=center");

    SDL_Surface *background = NULL, *red = NULL, *blue = NULL;

    background = IMG_Load("game.bmp");
    red = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    blue = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);

    SDL_FillRect(red, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
    SDL_FillRect(blue, NULL, SDL_MapRGB(screen->format, 0, 0, 255));

    int grille[40][40] = {0};
    grille[20][38] = SNAKE_HEAD;

    do
    {
        x = random(0, 39);
        y = random(0, 39);
    }
    while(grille[x][y]  > 2);
    grille[x][y] = FOOD;
    food = 1;

    SDL_Rect bg_position, position;

    bg_position.x = 0;
    bg_position.y = 0;

    position.x = 0;
    position.y = 0;

    screen = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Snake", NULL);

    SDL_Event event;

    while(run)
    {
        food = 0;
        SDL_BlitSurface(background, NULL, screen, &bg_position);
        for(x = 0; x < 40; x++)
        {
            for(y = 0; y < 40; y++)
            {
                if(grille[x][y] == FOOD)
                {
                    food = 1;
                    position.x = x * 10;
                    position.y = y * 10;

                    SDL_BlitSurface(red, NULL, screen, &position);
                }
                else if(grille[x][y] == SNAKE_HEAD && snake_head_found == 0)
                {
                    snake_head_found = 1;
                    position.x = x * 10;
                    position.y = y * 10;

                    SDL_BlitSurface(blue, NULL, screen, &position);

                    switch(direction)
                    {
                    case UP:
                        if(y == 0 || grille[x][y - 1] > 3)
                        {
                            run = 0;
                        }
                        else
                        {
                            grille[x][y - 1] = SNAKE_HEAD;
                            if(lenght == 1)
                            {
                                grille[x][y] = EMPTY;
                            }
                            else
                            {
                                grille[x][y] = 4;
                            }
                        }
                        break;

                    case RIGHT:
                        if(x == 39 || grille[x + 1][y] > 3)
                        {
                            run = 0;
                        }
                        else
                        {
                            grille[x + 1][y] = SNAKE_HEAD;
                            if(lenght == 1)
                            {
                                grille[x][y] = EMPTY;
                            }
                            else
                            {
                                grille[x][y] = 4;
                            }
                        }
                        break;

                    case DOWN:
                        if(y == 39 || grille[x][y + 1] > 3)
                        {
                            run = 0;
                        }
                        else
                        {
                            grille[x][y + 1] = SNAKE_HEAD;
                            if(lenght == 1)
                            {
                                grille[x][y] = EMPTY;
                            }
                            else
                            {
                                grille[x][y] = 4;
                            }
                        }
                        break;

                    case LEFT:
                        if(x == 0 || grille[x - 1][y] > 3)
                        {
                            run = 0;
                        }
                        else
                        {
                            grille[x - 1][y] = SNAKE_HEAD;
                            if(lenght == 1)
                            {
                                grille[x][y] = EMPTY;
                            }
                            else
                            {
                                grille[x][y] = 4;
                            }
                        }
                        break;
                    }
                }

                if(grille[x][y] > 3)
                {
                    position.x = x * 10;
                    position.y = y * 10;

                    SDL_BlitSurface(blue, NULL, screen, &position);

                    if(lenght > grille[x][y] - 2)
                    {
                        grille[x][y]++;
                    }
                    else
                    {
                        grille[x][y] = EMPTY;
                    }
                }
            }
        }
        snake_head_found = 0;
        SDL_Flip(screen);
        SDL_Delay(60);
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            run = 0;
            quit = 1;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                run = 0;
                break;

            case SDLK_UP:
                if(direction != DOWN)
                {direction = UP;}
                break;

            case SDLK_RIGHT:
                if(direction != LEFT)
                {direction = RIGHT;}
                break;

            case SDLK_DOWN:
                if(direction != UP)
                {direction = DOWN;}
                break;

            case SDLK_LEFT:
                if(direction != RIGHT)
                {direction = LEFT;}
                break;
            }
            break;
        }

        if(!food)
        {
            do
            {
                x = random(0, 39);
                y = random(0, 39);
            }
            while(grille[x][y] > 2);
            grille[x][y] = FOOD;
            food = 1;
            lenght+=5;
            score+= 10;
        }

        if(run == 0)
        {
            FILE *snake_score = NULL;
            snake_score = fopen("game.sc", "r");

            if(snake_score == NULL)
            {
                FILE *put_score = NULL;
                put_score = fopen("game.sc", "w+");

                fprintf(put_score, "%ld", score);

                fclose(put_score);
            }
            else
            {
                long score_found;
                fscanf(snake_score, "%ld", &score_found);
                fclose(snake_score);

                if(score > score_found)
                {
                    FILE *put_score = NULL;
                    put_score = fopen("game.sc", "w+");

                    fprintf(put_score, "%ld", score);

                    fclose(put_score);
                }
            }
        }
    }

    return quit;
}
