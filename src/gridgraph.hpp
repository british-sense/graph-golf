#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <tuple>

#include "params.hpp"
#include "point.hpp"
#include "node.hpp"
#include "edge.hpp"
#include "utils.hpp"

struct GridGraph {

    // member variables
    int height, width;
    int degree, length;
    std::vector< std::vector< std::vector< Node > > > grid;
    int diameter;
    double aspl;

    // constracter
    GridGraph();
    GridGraph(int h, int w);
    GridGraph(int h, int w, int d, int l);

    // menber function
    void generate_random_graph();
    void generate_random_regular_graph();
    void generate_symmetory_graph(int g, std::string pattern);
    std::vector< Node > at(const Node & pt);
    void calculate_aspl();
    bool is_connectable_node(const Node & pt);
    std::vector<Node> connectable_node_list();
    Node select_random_node(std::vector<Node> & node_list);
    std::tuple<Node, Node> select_connection_node(std::vector<Node> & node_list);
    void add_edge(const Edge & e);
    void remove_edge(const Edge & e);
    void output();


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
GridGraph::GridGraph(int h, int w) : height(h), width(w), grid(std::vector< std::vector< std::vector< Node > > >(h, std::vector< std::vector< Node > >(w))) {}
GridGraph::GridGraph(int h, int w, int d, int l) : height(h), width(w), degree(d), length(l), grid(std::vector< std::vector< std::vector< Node > > >(h, std::vector< std::vector< Node > >(w))) {}

// member function
void GridGraph::generate_random_graph() {
    std::vector<Node> connectable_node(connectable_node_list());
    while(!connectable_node.empty()) {
        auto [u, v] = select_connection_node(connectable_node);
        if(connectable_node.empty()) break;
        add_edge(Edge(u, v));
        if(this->at(u).size() == degree) connectable_node.erase(std::find(connectable_node.begin(), connectable_node.end(), v));
        if(this->at(v).size() == degree) connectable_node.erase(std::find(connectable_node.begin(), connectable_node.end(), u));
    }
}
void GridGraph::generate_random_regular_graph() {}
void GridGraph::generate_symmetory_graph(int g, std::string pattern = "Node") { // g = 1, 2, 4, 8
}
std::vector< Node > GridGraph::at(const Node & pt) {
    return grid.at(pt.h).at(pt.w);
}
void GridGraph::calculate_aspl() {}

bool GridGraph::is_connectable_node(const Node & n) {
    if(grid.at(n.h).at(n.w).size() >= diameter) return false;
    for(int h = n.h - length; h <= n.h + length; h++) {
        if(h < 0 || height <= h) continue;
        for(int w = n.w - length; w <= n.w + length; w++) {
            if(w < 0 || width <= w) continue;
            if(n == Node(h, w)) continue;
            if(grid.at(h).at(w).size() < diameter) return true;
        }
    }
    return false;
}
std::vector<Node> GridGraph::connectable_node_list() {
    std::vector<Node> connectable_node;
    for(int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            Node n(h, w);
            if(is_connectable_node(n)) connectable_node.emplace_back(n);
        }
    }
    return connectable_node;
}
Node GridGraph::select_random_node(std::vector<Node> & node_list) {
    std::uniform_int_distribution<int> list_range(0, node_list.size() - 1);
    return node_list.at(list_range(params::mt));
}
std::tuple<Node, Node> GridGraph::select_connection_node(std::vector<Node> & node_list) {
    Node u, v;
    while(manhattan_distance(u, v) <= length) {
        u = select_random_node(node_list);
        if(!is_connectable_node(u)) {
            node_list.erase(std::find(node_list.begin(), node_list.end(), u));
            u.clear();
            if(node_list.empty()) break;
            else continue;
        }
        v = select_random_node(node_list);
        if(!is_connectable_node(v)) {
            node_list.erase(std::find(node_list.begin(), node_list.end(), v));
            v.clear();
            if(node_list.empty()) break;
            else continue;
        }
    }
    return {u, v};
}
void GridGraph::add_edge(const Edge & e) {
    this->at(e.u).emplace_back(e.v);
    this->at(e.v).emplace_back(e.u);
}
void GridGraph::remove_edge(const Edge & e) {
    this->at(e.u).erase(std::find(this->at(e.u).begin(), this->at(e.u).end(), e.v));
    this->at(e.v).erase(std::find(this->at(e.v).begin(), this->at(e.v).end(), e.u));
}
void GridGraph::output() {
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            Node n(h, w);
            std::cout << n.Point::output() + " : ";
            for(int d = 0; d < this->at(n).size(); d++) {
                std::cout << this->at(n).at(d).Point::output << ", ";
            }
            std::cout << std::endl;
        }
    }
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