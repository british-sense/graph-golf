#pragma once

#include "point.hpp"

struct Node : Point{

    // member variable
    int id;

    // constractor
    Node();
    Node(int id);
    Node(int h, int w);

    // operator
    bool operator == (const Node & n) const;
    bool operator != (const Node & n) const;
};

Node::Node() {}
Node::Node(int _id) : id(_id) {}
Node::Node(int _h, int _w) : Point(_h, _w) {}

bool Node::operator == (const Node & n) const {
    return id == n.id;
}
bool Node::operator != (const Node & n) const {
    return id != n.id;
}