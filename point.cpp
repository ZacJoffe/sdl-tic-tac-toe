#include "point.hpp"
#include <iostream>

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::~Point() {}

void Point::print() {
    std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
}

float Point::getX() const { return this->x; }
float Point::getY() const { return this->y; }

Point getCenter(int i, int j) { return Point((i * SCREEN_WIDTH / 3.0) + (SCREEN_WIDTH / 6.0), (j * SCREEN_HEIGHT / 3.0) + (SCREEN_HEIGHT / 6.0)); }
