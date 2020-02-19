#pragma once

#include <iostream>
#include <string>

struct Point {

    // menber variable
    int h, w;

    // constractor
    Point();
    Point(int _h, int _w);

    // member function
    std::string output();

    // operator
    bool operator == (const Point & pt) const;
    bool operator != (const Point & pt) const;
    bool operator < (const Point & pt) const;
    bool operator <= (const Point & pt) const;
    bool operator > (const Point & pt) const;
    bool operator >= (const Point & pt) const;
};

// constractor
Point::Point() {}
Point::Point(int _h, int _w) : h(_h), w(_w) {}

// member function
std::string Point::output() {
    std::cout << "(" + std::to_string(h) + ", " + std::to_string(w) +")" << std::endl;
}


// operator
bool Point::operator == (const Point & pt) const {
    return (h == pt.h) && (w == pt.w);
}
bool Point::operator != (const Point & pt) const {
    return !((h == pt.h) && (w == pt.w));
}
bool Point::operator < (const Point & pt) const {
    return std::pair<int, int>(h, w) < std::pair<int, int>(pt.h, pt.w);
}
bool Point::operator <= (const Point & pt) const {
    return std::pair<int, int>(h, w) <= std::pair<int, int>(pt.h, pt.w);
}
bool Point::operator > (const Point & pt) const {
    return std::pair<int, int>(h, w) > std::pair<int, int>(pt.h, pt.w);
}
bool Point::operator >= (const Point & pt) const {
    return std::pair<int, int>(h, w) >= std::pair<int, int>(pt.h, pt.w);
}