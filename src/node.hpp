#pragma once

#include <string>

#include "point.hpp"

struct Node : Point{

    // member variable
    int id;

    // constractor
    Node();
    Node(int id);
    Node(int h, int w);

    void clear();
    std::string output();

    // operator
    bool operator == (const Node & n) const;
    bool operator != (const Node & n) const;
};

Node::Node() {}
Node::Node(int _id) : id(_id) {}
Node::Node(int _h, int _w) : Point(_h, _w), id(_h * _w + _w) {}

// member function
void Node::clear() {
    *this = Node();
}
std::string Node::output() {
    return std::to_string(id) + Point::output();
}

bool Node::operator == (const Node & n) const {
    return id == n.id && Point::operator==(n);
}
bool Node::operator != (const Node & n) const {
    return id != n.id && Point::operator!=(n);
}