#include <iostream>
#include <vector>

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

    // operator
    bool operator == (const GridGraph & g) const;
    bool operator != (const GridGraph & g) const;
    bool operator < (const GridGraph & g) const;
    bool operator <= (const GridGraph & g) const;
    bool operator > (const GridGraph & g) const;
    bool operator >= (const GridGraph & g) const;
};