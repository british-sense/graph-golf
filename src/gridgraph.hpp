#include <iostream>
#include <vector>
#include <string>

#include "point.hpp"

class GridGraph {

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
    void generate_cayley_graph();
    void generate_symmetory_graph(int p);
    std::vector< int > at(const Point p);
    double get_diameter();
    double get_aspl();
    void calculate_aspl();

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
void GridGraph::generate_random_graph() {}
void GridGraph::generate_cayley_graph() {}
void GridGraph::generate_symmetory_graph(int g) { // g = 1, 2, 4, 8

}
std::vector< int > GridGraph::at(const Point p) {}
double GridGraph::get_diameter() {
    return diameter;
}
double GridGraph::get_aspl() {
    return aspl;
}
void GridGraph::calculate_aspl() {}

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