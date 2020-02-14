#include <iostream>
#include <vector>

class GeneralGraph {

    // member variables
    int dimension;
    std::vector< std::vector< int > > graph;
    int diameter;
    double aspl;

    // constracter
    GeneralGraph();

    // menber function
    void generate_random_graph();
    void generate_cayley_graph();
    void generate_symmetory_graph(int p);
    std::vector< int > at(const int id);
    double get_diameter();
    double get_aspl();
    void calculate_aspl();

    // operator
    bool operator == (const GeneralGraph & g) const;
    bool operator != (const GeneralGraph & g) const;
    bool operator < (const GeneralGraph & g) const;
    bool operator <= (const GeneralGraph & g) const;
    bool operator > (const GeneralGraph & g) const;
    bool operator >= (const GeneralGraph & g) const;
};