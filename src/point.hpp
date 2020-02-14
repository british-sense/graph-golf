#include <iostream>

class Point {

    // menber variable
    int h, w;

    // constractor
    Point();
    Point(int h, int w);

    // member function

    // operator
    bool operator < (const GridGraph & g) const;
    bool operator <= (const GridGraph & g) const;
    bool operator > (const GridGraph & g) const;
    bool operator >= (const GridGraph & g) const;
};