#include <iostream>
#include <vector>
#include <string>

#include "point.hpp"

struct GridGraph {

    // member variables
    int height, width;
    int dimension, length;
    std::vector< std::vector< std::vector< int > > > grid;
    int diameter;
    double aspl;

    // constracter
    GridGraph();
    GridGraph(int h, int w);
    GridGraph(int h, int w, int d, int l);

    // menber function
    void generate_random_graph();
    void generate_random_regular_graph();
    void generate_cayley_graph();
    void generate_symmetory_graph(int p);
    std::vector< int > at(const Point pt);
    void calculate_aspl();
    bool is_connectable_node(const Point pt);
    std::vector<Point> connectable_node_list();

    // operator
    bool operator == (const GridGraph & g) const;
    bool operator != (const GridGraph & g) const;
    bool operator < (const GridGraph & g) const;
    bool operator <= (const GridGraph & g) const;
    bool operator > (const GridGraph & g) const;
    bool operator >= (const GridGraph & g) const;
};

// constractor
GridGraph::GridGraph() {}
GridGraph::GridGraph(int h, int w) : height(h), width(w) {}
GridGraph::GridGraph(int h, int w, int d, int l) : height(h), width(w), diameter(d), length(l) {}

// member function
void GridGraph::generate_random_graph() {
    std::vector<Point> can_connect_node;
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {

        }
    }
}
void GridGraph::generate_random_regular_graph() {}
void GridGraph::generate_cayley_graph() {}
void GridGraph::generate_symmetory_graph(int g) { // g = 1, 2, 4, 8

}
std::vector< int > GridGraph::at(const Point pt) {
    return grid.at(pt.h).at(pt.w);
}
void GridGraph::calculate_aspl() {}
bool GridGraph::is_connectable_node(const Point pt) {
    if(grid.at(pt.h).at(pt.w).size() >= diameter) return false;
    for(int h = pt.h - length; h <= pt.h + length; h++) {
        if(h < 0 || height <= h) continue;
        for(int w = pt.w - length; w <= pt.w + length; h++) {
            if(w < 0 || width <= w) continue;
            if(pt == Point(h, w)) continue;
            if(grid.at(h).at(w).size() < diameter) return true;
        }
    }
    return false;
}
std::vector<Point> GridGraph::connectable_node_list() {
    std::vector<Point> connectable_node;
    for(int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            Point pt(h, w);
            if(is_connectable_node(pt)) connectable_node.emplace_back(pt);
        }
    }
    return connectable_node;
}

// operator
bool GridGraph::operator == (const GridGraph & g) const {
    return grid == g.grid;
}
bool GridGraph::operator != (const GridGraph & g) const {
    return grid != g.grid;
}
bool GridGraph::operator < (const GridGraph & g) const {
    return aspl < g.aspl;
}
bool GridGraph::operator <= (const GridGraph & g) const {
    return aspl <= g.aspl;
}
bool GridGraph::operator > (const GridGraph & g) const {
    return aspl > g.aspl;
}
bool GridGraph::operator >= (const GridGraph & g) const {
    return aspl >= g.aspl;
}