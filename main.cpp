#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const int WIDTH = 720, HEIGHT = 720;
SDL_Window *window = NULL;
SDL_Surface *background = NULL;
SDL_Renderer * renderer = NULL;
SDL_Texture * texture = NULL;

int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Chessboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);  // 0 -> SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, 0);
    background = SDL_LoadBMP_RW(SDL_RWFromFile("chessboard.bmp", "rb"), 1);
    texture = SDL_CreateTextureFromSurface(renderer, background);

    if(NULL == window)
    {
        cout << "Cannot create window" << SDL_GetError() << endl;
        return 1;
    }

    SDL_Event WindowEvent;
    while(!quit)
    {
        SDL_WaitEvent(&WindowEvent);

        if(WindowEvent.type == SDL_QUIT)
        {
            quit = true;
            break;
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}