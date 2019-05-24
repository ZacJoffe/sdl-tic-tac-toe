#pragma once

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
