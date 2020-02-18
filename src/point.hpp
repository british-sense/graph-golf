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
    bool operator == (const Point & pt) const;
    bool operator != (const Point & pt) const;
    bool operator < (const Point & pt) const;
    bool operator <= (const Point & pt) const;
    bool operator > (const Point & pt) const;
    bool operator >= (const Point & pt) const;
};

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