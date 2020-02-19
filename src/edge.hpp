#pragma once

#include "node.hpp"

struct Edge {

    // member variable
    Node u, v;

    // constractor
    Edge();
    Edge(Node u, Node v);

    // member function
    std::string output();

    // operator
    bool operator == (const Edge & e) const;
    bool operator != (const Edge & e) const;
};

Edge::Edge() {}
Edge::Edge(Node _u, Node _v) : u(_u), v(_v) {}

std::string Edge::output() {
    return u.Point::output() + " -- " + v.Point::output();
}

bool Edge::operator == (const Edge & e) const {
    return (u == e.u && v == e.v) || (u == e.v && v == e.u);
}
bool Edge::operator != (const Edge & e) const {
    return !((u == e.u && v == e.v) || (u == e.v && v == e.u));
}