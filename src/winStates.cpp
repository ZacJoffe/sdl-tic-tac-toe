#include "winState.hpp"

WinState::WinState(Win w, Point p) {
    this->w = w;
    this->p = p;
}

WinState::WinState() {
    this->w = NONE;
    this->p = Point();
}

WinState::~WinState() {}

Win WinState::getWin() {
    return this->w;
}

Point WinState::getPoint() {
    return this->p;
}
