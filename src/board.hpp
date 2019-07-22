#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "point.hpp"
#include "winState.hpp"

#define MAGIC_TOTAL 15

enum States { EMPTY, X, O, TIE };
// enum WinStates { ROW, COL, DIAG, REVERSEDIAG };

const int magicSquare[3][3] = {
    {8, 1, 6},
    {3, 5, 7},
    {4, 9, 2}
};

class Board {
private:
    States s[3][3];
    int moveCount;
    WinState w;

    float degToRad(float degrees);
    void drawCircle(SDL_Renderer *renderer, int i, int j);
    void drawX(SDL_Renderer *renderer, int i, int j);
    void drawLine(SDL_Renderer *renderer);
public:
    Board();
    ~Board();

    void draw(SDL_Renderer *renderer);
    void drawGameOver(SDL_Renderer *renderer, TTF_Font *font, States winner);

    bool insert(int i, int j);
    void print();
    States checkWin(SDL_Renderer *renderer);
    void reset();
};
