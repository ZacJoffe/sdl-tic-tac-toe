#include <SDL2/SDL.h>
#include "point.hpp"

#define MAGIC_TOTAL 15

enum States { EMPTY, X, O, TIE };

const int magicSquare[3][3] = {
    {8, 1, 6},
    {3, 5, 7},
    {4, 9, 2}
};

class Board {
private:
    States s[3][3];
    int moveCount;

    float degToRad(float degrees);
    void drawCircle(SDL_Renderer *renderer, int i, int j);
    void drawX(SDL_Renderer *renderer, int i, int j);

public:
    Board();
    ~Board();

    void draw(SDL_Renderer *renderer);
    bool insert(int i, int j);
    void print();
    States checkWin();
    void reset();
};
