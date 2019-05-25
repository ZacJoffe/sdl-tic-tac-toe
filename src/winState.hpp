#pragma once

#include "point.hpp"

enum Win { ROW, COL, DIAG, REVERSEDIAG };

class WinState {
private:
    Win w;
    Point p;

public:
    WinState(Win w, Point p);
    WinState();
    ~WinState();

    Win getWin();
    Point getPoint();
};