#include "point.hpp"
#include "board.hpp"
#include <iostream>

float Board::degToRad(float degrees) {
    return degrees * M_PI / 180.0;
}

void Board::drawCircle(SDL_Renderer *renderer, int i, int j) {
    Point center = getCenter(i, j);
    // center.print();

    int radius = SCREEN_HEIGHT / 6;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 360; i++) {
        Point p(center.getX() + radius * cos(degToRad(i)), center.getY() + radius * sin(degToRad(i)));
        SDL_RenderDrawPoint(renderer, static_cast<int>(p.getX()), static_cast<int>(p.getY()));
    }
}

void Board::drawX(SDL_Renderer *renderer, int i, int j) {
    Point p1(i * SCREEN_WIDTH / 3, j * SCREEN_HEIGHT / 3);
    // int x1 = i * SCREEN_WIDTH / 3;
    // int y1 = j * SCREEN_HEIGHT / 3;

    Point p2(p1.getX() + SCREEN_WIDTH / 3, p1.getY() + SCREEN_HEIGHT / 3);
    // int x2 = x1 + SCREEN_WIDTH / 3;
    // int y2 = y1 + SCREEN_HEIGHT / 3;

    // std::cout << x1 << " " << y1 << std::endl;
    // std::cout << x2 << " " << y2 << std::endl;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_RenderDrawLine(renderer, p2.getX(), p1.getY(), p1.getX(), p2.getY());
}

void Board::drawLine(SDL_Renderer *renderer) {
    switch (this->w.getWin()) {
        case ROW:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, this->w.getPoint().getX() + SCREEN_WIDTH / 6.0, 0, this->w.getPoint().getX() + SCREEN_WIDTH / 6.0, SCREEN_HEIGHT);
            break;
        case COL:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, 0, this->w.getPoint().getY() + SCREEN_HEIGHT / 6.0, SCREEN_WIDTH, this->w.getPoint().getY() + SCREEN_HEIGHT / 6.0);
            break;
        case DIAG:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
        case REVERSEDIAG:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT);
            break;
        default:
            break;
    }
}

Board::Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->s[i][j] = EMPTY;
        }
    }

    this->moveCount = 0;
    this->w = WinState();
}

Board::~Board() {}

void Board::draw(SDL_Renderer *renderer) {
    for (float x = SCREEN_WIDTH / 3.0; x < SCREEN_WIDTH; x += SCREEN_WIDTH / 3.0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, static_cast<int>(x), 0, static_cast<int>(x), SCREEN_HEIGHT);
        // std::cout << x << std::endl;
    }

    for (float y = SCREEN_HEIGHT / 3.0; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT / 3.0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, static_cast<int>(y), SCREEN_WIDTH, static_cast<int>(y));
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (this->s[i][j]) {
                case X:
                    this->drawX(renderer, i, j);
                    break;
                case O:
                    this->drawCircle(renderer, i, j);
                    break;
                default:
                    break;
            }
        }
    }

    this->drawLine(renderer);
}

// returns true if successful, false if there is a piece already placed in the index
bool Board::insert(int i, int j) {
    if (this->s[i][j] != EMPTY) {
        return false;
    }

    // x goes first!
    if (this->moveCount % 2 == 0) {
        this->s[i][j] = X;
    } else {
        this->s[i][j] = O;
    }

    this->moveCount++;

    return true;
}

void Board::print() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            std::cout << this->s[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

// returns: EMPTY if still going, X if x wins, O if o wins, and TIE if it's a tied game
States Board::checkWin(SDL_Renderer *renderer) {
    if (this->moveCount == 9) {
        return TIE;
    }

    int sumX;
    int sumO;

    // check rows
    for (int i = 0; i < 3; i++) {
        sumX = 0;
        sumO = 0;
        for (int j = 0; j < 3; j++) {
            if (this->s[i][j] == X) {
                sumX += magicSquare[i][j];
            }

            if (this->s[i][j] == O) {
                sumO += magicSquare[i][j];
            }
        }

        if (sumX == MAGIC_TOTAL) {
            this->w = WinState(ROW, Point(i, 0));
            // this->drawLine(renderer, ROW, i, 0);
            return X;
        }

        if (sumO == MAGIC_TOTAL) {
            this->w = WinState(ROW, Point(i, 0));
            // this->drawLine(renderer, ROW, i, 0);
            return O;
        }
    }

    //  check cols
    for (int j = 0; j < 3; j++) {
        sumX = 0;
        sumO = 0;
        for (int i = 0; i < 3; i++) {
            if (this->s[i][j] == X) {
                sumX += magicSquare[i][j];
            }

            if (this->s[i][j] == O) {
                sumO += magicSquare[i][j];
            }
        }

        if (sumX == MAGIC_TOTAL) {
            this->w = WinState(COL, Point(0, j));
            // this->drawLine(renderer, COL, 0, j);
            return X;
        }

        if (sumO == MAGIC_TOTAL) {
            this->w = WinState(COL, Point(0, j));
            // this->drawLine(renderer, COL, 0, j);
            return O;
        }   
    }

    // check diagonal
    sumX = 0;
    sumO = 0;
    for (int i = 0; i < 3; i++) {
        if (this->s[i][i] == X) {
            sumX += magicSquare[i][i];
        }

        if (this->s[i][i] == O) {
            sumO += magicSquare[i][i];
        }

        if (sumX == MAGIC_TOTAL) {
            this->w = WinState(DIAG, Point());
            // this->drawLine(renderer, DIAG, 0, 0);
            return X;
        }

        if (sumO == MAGIC_TOTAL) {
            this->w = WinState(DIAG, Point());
            // this->drawLine(renderer, DIAG, 0, 0);
            return O;
        }
    }

    // reverse diagonal
    sumX = 0;
    sumO = 0;
    for (int i = 2; i >= 0; i--) {
        if (this->s[i][i] == X) {
            sumX += magicSquare[i][i];
        }

        if (this->s[i][i] == O) {
            sumO += magicSquare[i][i];
        }

        if (sumX == MAGIC_TOTAL) {
            this->w = WinState(REVERSEDIAG, Point());
            // this->drawLine(renderer, REVERSEDIAG, 0, 0);
            return X;
        }

        if (sumO == MAGIC_TOTAL) {
            this->w = WinState(REVERSEDIAG, Point());
            // this->drawLine(renderer, REVERSEDIAG, 0, 0);
            return O;
        }
    }

    return EMPTY;
}

void Board::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->s[i][j] = EMPTY;
        }
    }

    this->moveCount = 0;
    this->w = WinState();
}
