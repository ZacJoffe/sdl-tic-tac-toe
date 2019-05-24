#include <SDL2/SDL.h>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum States { EMPTY, X, O, TIE };

const int magicSquare[3][3] = {
    {8, 1, 6},
    {3, 5, 7},
    {4, 9, 2}
};

class Board {
private:
    States s[3][3];
    //int square[3][3];
    int moveCount;

    void drawCircle(SDL_Renderer *renderer) {

    }

    void drawX(SDL_Renderer *renderer, int i, int j) {
        int x1 = i * SCREEN_WIDTH / 3;
        int y1 = j * SCREEN_HEIGHT / 3;

        int x2 = x1 + SCREEN_WIDTH / 3;
        int y2 = y1 + SCREEN_HEIGHT / 3;

        std::cout << x1 << " " << y1 << std::endl;
        std::cout << x2 << " " << y2 << std::endl;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x2, y1, x1, y2);
    }

public:
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s[i][j] = EMPTY;
                //square[i][j] = magicSquare[i][j];
            }
        }

        moveCount = 0;
    }

    ~Board() {}

    void draw(SDL_Renderer *renderer) {
        for (float x = SCREEN_WIDTH / 3.0; x < SCREEN_WIDTH; x += SCREEN_WIDTH / 3.0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, int(x), 0, int(x), SCREEN_HEIGHT);
            // std::cout << x << std::endl;
        }

        for (float y = SCREEN_HEIGHT / 3.0; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT / 3.0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, 0, int(y), SCREEN_WIDTH, int(y));
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                switch (s[i][j]) {
                    case X:
                        this->drawX(renderer, i, j);
                        break;
                    case O:
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // returns true if successful, false if there is a piece already placed in the index
    bool insert(int i, int j) {
        if (s[i][j] != EMPTY) {
            return false;
        }

        // x goes first!
        if (moveCount % 2 == 0) {
            s[i][j] = X;
        } else {
            s[i][j] = O;
        }

        moveCount++;

        return true;
    }

    void print() {
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                std::cout << s[i][j] << " ";
            }

            std::cout << std::endl;
        }
    }

    /*
    // returns: EMPTY if still going, X if x wins, O if o wins, and TIE if it's a tied game
    States checkWin() {
        // check rows
        for (int i = 0; i < 3; i++) {
            int sum = 0;
            for (int j = 0; j < 3; j++) {
                if (s[i][j] != EMPTY) {
                    sum += magicSquare[i][j];
                }
            }
        }

    }
    */
};

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

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

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

                b.print();
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        b.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    return 0;
}