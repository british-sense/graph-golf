#pragma once

#include "node.hpp"

struct Edge {

    // member variable
    Node u, v;

    // operator
    bool operator == (const Edge & e) const;
    bool operator != (const Edge & e) const;
};

bool Edge::operator == (const Edge & e) const {
    return (u == e.u && v == e.v) || (u == e.v && v == e.u);
}
bool Edge::operator != (const Edge & e) const {
    return !((u == e.u && v == e.v) || (u == e.v && v == e.u));
}