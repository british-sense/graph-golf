#include <iostream>

class Point {

    // menber variable
    int h, w;

    // constractor
    Point();
    Point(int h, int w);

    // member function
    int get_height();
    int get_width();

    // operator
    bool operator < (const GridGraph & g) const;
    bool operator <= (const GridGraph & g) const;
    bool operator > (const GridGraph & g) const;
    bool operator >= (const GridGraph & g) const;
};

int Point::get_height() {
    return h;
}
int Point::get_width() {
    return w;
}