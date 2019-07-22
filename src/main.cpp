#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>

#include "board.hpp"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
TTF_Font *font = nullptr;

// if any sdl call fails, returns false and logs error, otherwise return true for success
bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Window could be not created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, NULL); // enable hardware acceleration flag?
    if (renderer == NULL) {
        std::cout << "Rendered could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0) {
        std::cout << "Font could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    std::string fontName = "assets/Roboto-Black.ttf";

    //  font = TTF_OpenFont(fontName.c_str(), 12);
    font = TTF_OpenFont("assets/Roboto-Black.ttf", 24);
    if (font == NULL) {
        std::cout << "Font could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

int main() {
    if (!init()) {
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    Board b;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int xPos;
                int yPos;

                SDL_GetMouseState(&xPos, &yPos);
                // std::cout << xPos << " " << yPos << std::endl;

                int i;
                int j;

                if (xPos < SCREEN_WIDTH / 3) {
                    i = 0;
                } else if (xPos < 2 * SCREEN_WIDTH / 3) {
                    i = 1;
                } else {
                    i = 2;
                }

                if (yPos < SCREEN_HEIGHT / 3) {
                    j = 0;
                } else if (yPos < 2 * SCREEN_HEIGHT / 3) {
                    j = 1;
                } else {
                    j = 2;
                }


                std::cout << xPos << " " << yPos << std::endl;
                std::cout << i << " " << j << std::endl;

                if (!b.insert(i, j)) {
                    std::cout << "Already taken!" << std::endl;
                }

                // b.print();
            }
        }

        /*
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        b.draw(renderer);
        SDL_RenderPresent(renderer);
        */

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (b.checkWin(renderer)) {
            case X:
                std::cout << "X Wins!" << std::endl;

                b.draw(renderer);
                b.drawGameOver(renderer, font, X);
                SDL_RenderPresent(renderer);

                SDL_Delay(2000);
                b.reset();
                break;
            case O:
                std::cout << "O Wins!" << std::endl;

                b.draw(renderer);
                b.drawGameOver(renderer, font, O);
                SDL_RenderPresent(renderer);

                SDL_Delay(2000);
                b.reset();
                break;
            case TIE:
                std::cout << "Tie!!!" << std::endl;

                b.draw(renderer);
                b.drawGameOver(renderer, font, TIE);
                SDL_RenderPresent(renderer);

                SDL_Delay(2000);
                b.reset();
                break;
            default:
                b.draw(renderer);
                SDL_RenderPresent(renderer);
                break;
        }
    }

    return 0;
}
