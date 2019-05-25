#pragma once

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 1280;

class Point {
private:
    float x;
    float y;
public:
    Point(float x, float y);
    Point();
    ~Point();

    void print();

    float getX() const;
    float getY() const;
};

Point getCenter(int i, int j);
