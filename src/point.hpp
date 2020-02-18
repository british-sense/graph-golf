#include <iostream>

struct Point {

    // menber variable
    int h, w;

    // constractor
    Point();
    Point(int h, int w);

    // member function
    int get_height();
    int get_width();

    // operator
    bool operator < (const Point & g) const;
    bool operator <= (const Point & g) const;
    bool operator > (const Point & g) const;
    bool operator >= (const Point & g) const;
};