#pragma once

#include "point.hpp"

struct Node : Point{
    
    // member variable
    int id;

    // operator
    bool operator == (const Node & n) const;
    bool operator != (const Node & n) const;
};

bool Node::operator == (const Node & n) const {
    return id == n.id;
}
bool Node::operator != (const Node & n) const {
    return id != n.id;
}