#pragma once

#include <iostream>
#include <cmath>

#include "point.hpp"

int manhattan_distance(const Point & pt1, const Point & pt2) {
    return std::abs(pt1.h - pt2.h) + std::abs(pt1.w - pt2.w);
}