#ifndef MENU_H
#define MENU_H

    SDL_Surface *video_init(int width ,int height)
    {
        putenv("SDL_VIDEO_WINDOW_POS=center");

        SDL_Surface *screen = NULL;
        SDL_Surface *background = NULL;

        background = IMG_Load("bg.bmp");

        SDL_Rect bg_position;

        bg_position.x = 0;
        bg_position.y = 0;

        SDL_Init(SDL_INIT_VIDEO);
        screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

        SDL_BlitSurface(background, NULL, screen, &bg_position);

        SDL_FreeSurface(background);
        return screen;
    }

#endif
