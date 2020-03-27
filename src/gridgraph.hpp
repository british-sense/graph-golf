#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <tuple>
#include <cstring>
#include <immintrin.h>

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
    const std::vector< Node > & at(const Node & n) const;
    std::vector< Node > & at(const Node & n);
    uint64_t mul(const uint64_t * A, uint64_t * B, unsigned int row_len);
    void calculate_aspl();
    bool is_connectable_node(const Node & n);
    bool exists_edge(const Node & u, const Node & v);
    std::vector<Node> get_connectable_node_list();
    Node get_random_node();
    Node select_random_node(const std::vector<Node> & node_list);
    std::tuple<Node, Node> select_random_connection_nodes(std::vector<Node> & node_list);
    Edge get_random_edge();
    Edge select_random_edge(const std::vector<Edge> & edge_list);
    std::vector<Edge> get_swappable_edge_list(const Edge & e);
    std::tuple<Edge, Edge> get_random_swapping_edges();
    void add_edge(const Edge & e);
    void remove_edge(const Edge & e);
    void swap_edge(Edge & e1, Edge & e2);
    void hill_climbing(const int max_evaluation_count);
    void output();
    void output_edgefile(const std::string & filename);
    void input_edgefile(const std::string & filename);


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
    std::vector<Node> connectable_node(get_connectable_node_list());
    while(!connectable_node.empty()) {
        auto [u, v] = select_random_connection_nodes(connectable_node);
        if(connectable_node.empty()) break;
        add_edge(Edge(u, v));
        if(at(u).size() == degree) connectable_node.erase(std::find(connectable_node.begin(), connectable_node.end(), u));
        if(at(v).size() == degree) connectable_node.erase(std::find(connectable_node.begin(), connectable_node.end(), v));
    }
}
void GridGraph::generate_random_regular_graph() {
}
void GridGraph::generate_symmetory_graph(int g, std::string pattern = "point") { // g = 1, 2, 4, 8
}
std::vector< Node > & GridGraph::at(const Node & n) {
    return grid.at(n.h).at(n.w);
}
const std::vector< Node > & GridGraph::at(const Node & n) const {
    return grid.at(n.h).at(n.w);
}
uint64_t GridGraph::mul(const uint64_t * A, uint64_t * B, unsigned int row_len){
        
    uint64_t c = 0;
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            Node n(h, w);
            __m256i * x = (__m256i *) (B + (h * width + w) * row_len);

            for(auto itr = at(n).begin(); itr != at(n).end(); itr++) {
                int n = itr->h * width + itr->w;
                __m256i * y = (__m256i *) (A + n * row_len);
                for(std::size_t j = 0; j < row_len / 4; j++) {
                    __m256i yy = _mm256_load_si256(y + j);
                    __m256i xx = _mm256_load_si256(x + j);
                    _mm256_store_si256(x + j, _mm256_or_si256(xx, yy));
                }
            }
            for(unsigned int i = 0; i < row_len; i++) {
                c += _mm_popcnt_u64(((uint64_t *)x)[i]);
            }
        }
    }
    return c;  
}
void GridGraph::calculate_aspl() {
    // Mori's aspl code.
    uint64_t m = height * width;
    unsigned int row_len = (m + 63) / 64;

    row_len = (row_len + 3) / 4 * 4;
    uint64_t * A = (uint64_t *)_mm_malloc(row_len * m * sizeof(uint64_t), 32);
    uint64_t * B = (uint64_t *)_mm_malloc(row_len * m * sizeof(uint64_t), 32);

    std::memset(A, 0, row_len * m * sizeof(uint64_t));
    std::memset(B, 0, row_len * m * sizeof(uint64_t));
    for(unsigned int i = 0; i < m; i++) {
        A[(i) * row_len + (i) / 64] |= (0x1ULL << ((i) % 64));
        B[(i) * row_len + (i) / 64] |= (0x1ULL << ((i) % 64));
    }

    uint64_t apsp = m * (m - 1);
    unsigned int k = 0;
    for(k = 1; k <= m; k++) {
        uint64_t num = mul(A, B, row_len);

        std::swap(A, B);

        if(num == m * m) break;
        apsp += m * m - num;
    }

    if(k <= m) {
        diameter = k;
        aspl = static_cast<double>(apsp) / (m * (m - 1));
    } else {
        diameter = std::numeric_limits<int>::max();
        aspl = std::numeric_limits<double>::max();
    }
    _mm_free(A);
    _mm_free(B);
}
bool GridGraph::is_connectable_node(const Node & u) {
    if(at(u).size() >= degree) return false;
    for(int h = u.h - length; h <= u.h + length; h++) {
        if(h < 0 || height <= h) continue;
        for(int w = u.w - (length - std::abs(h - u.h)); w <= u.w + (length - std::abs(h - u.h)); w++) {
            if(w < 0 || width <= w) continue;
            Node v(h, w);
            if(u == v) continue;
            if(exists_edge(u, v)) continue;
            if(at(v).size() < degree) return true;
        }
    }
    return false;
}
bool GridGraph::exists_edge(const Node & u, const Node & v) {
    return std::find(at(u).begin(), at(u).end(), v) != at(u).end();
}
std::vector<Node> GridGraph::get_connectable_node_list() {
    std::vector<Node> connectable_node;
    for(int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            Node n(h, w);
            if(is_connectable_node(n)) connectable_node.emplace_back(n);
        }
    }
    return connectable_node;
}
Node GridGraph::select_random_node(const std::vector<Node> & node_list) {
    std::uniform_int_distribution<int> list_range(0, node_list.size() - 1);
    return node_list.at(list_range(params::mt));
}
Node GridGraph::get_random_node() {
    std::uniform_int_distribution<int> h_range(0, height - 1);
    std::uniform_int_distribution<int> w_range(0, width - 1);
     return Node(h_range(params::mt), w_range(params::mt));
}
std::tuple<Node, Node> GridGraph::select_random_connection_nodes(std::vector<Node> & node_list) {
    Node u, v;
    bool is_selected = false;
    while(manhattan_distance(u, v) > length || u == v || exists_edge(u, v) || !is_selected) {
        is_selected = false;
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
        is_selected = true;
    }
    return {u, v};
}
Edge GridGraph::get_random_edge() {
    Node u(get_random_node());
    std::uniform_int_distribution<int> d_range(0, at(u).size() - 1);
    Node v(at(u).at(d_range(params::mt)));
    return Edge(u, v);
}
Edge GridGraph::select_random_edge(const std::vector<Edge> & edge_list) {
    std::uniform_int_distribution<int> e_range(0, edge_list.size() - 1);
    return edge_list.at(e_range(params::mt));
}
std::vector<Edge> GridGraph::get_swappable_edge_list(const Edge & e1) {
    std::vector<Edge> edge_list;
    for(int h = e1.u.h - length; h <= e1.u.h + length; h++) {
        if(h < 0 || height <= h) continue;
        for(int w = e1.u.w - (length - std::abs(h - e1.u.h)); w <= e1.u.w + (length - std::abs(h - e1.u.h)); w++) {
            if(w < 0 || width <= w) continue;
            Node v(h, w);
            if(e1.u == v) continue;
            for(auto itr = at(v).begin(); itr != at(v).end(); itr++) {
                if(manhattan_distance(e1.v, *itr) <= length) edge_list.emplace_back(Edge(v, *itr));
            }
        }
    }
    return edge_list;
}
std::tuple<Edge, Edge> GridGraph::get_random_swapping_edges() {
    Edge e1(get_random_edge());
    std::vector<Edge> swappable_edges(get_swappable_edge_list(e1));
    Edge e2(select_random_edge(swappable_edges));
    return {e1, e2};
}
void GridGraph::add_edge(const Edge & e) {
    if(std::find(at(e.u).begin(), at(e.u).end(), e.v) != at(e.u).end()) return;
    at(e.u).emplace_back(e.v);
    at(e.v).emplace_back(e.u);
}
void GridGraph::remove_edge(const Edge & e) {
    if(std::find(at(e.u).begin(), at(e.u).end(), e.v) != at(e.u).end()) return;
    at(e.u).erase(std::find(at(e.u).begin(), at(e.u).end(), e.v));
    at(e.v).erase(std::find(at(e.v).begin(), at(e.v).end(), e.u));
}
void GridGraph::swap_edge(Edge & e1, Edge & e2) {
    remove_edge(e1);
    remove_edge(e2);
    std::swap(e1.v, e2.u);
    add_edge(e1);
    add_edge(e2);
}
void GridGraph::hill_climbing(const int max_evaluation_count = 1e3) {
    for(int evaluation_count = 0; evaluation_count < max_evaluation_count; evaluation_count++) {
        double before_aspl = aspl;
        auto [e1, e2] = get_random_swapping_edges(); // <- this function has bug.
        swap_edge(e1, e2);
        calculate_aspl();
        if(aspl > before_aspl) swap_edge(e1, e2);
    }
}
void GridGraph::output() {
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            Node n(h, w);
            std::cout << n.Point::output() + " : ";
            for(int d = 0; d < at(n).size(); d++) {
                std::cout << at(n).at(d).Point::output() << ((d != at(n).size() - 1) ? ", " : " ");
            }
            std::cout << std::endl;
        }
    }
}
void GridGraph::output_edgefile(const std::string & filename) {
    std::ofstream outputfile("../data/" + filename + ".edges");
    for(int h = 0; h < height; h++){    
        for(int w = 0; w < width; w++){
            Node u(h, w);
            for(const auto & v : at(u)){
                if(u <= v) outputfile << u.Point::output() << " " << v.Point::output() << std::endl;
            }
        }
    }
}
void GridGraph::input_edgefile(const std::string & filename) {
    std::ifstream inputfile("../data/" + filename + ".edges");
    if (inputfile.fail()) {
        std::cerr << "Failed to open input file." << std::endl;
        exit(0);
    }

    std::string str;
    while(std::getline(inputfile, str)){
        Node u, v;
        sscanf(str.data(), "%d,%d %d,%d", &u.h, &u.w, &v.h, &v.w);
        add_edge(Edge(u, v));
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
    if(diameter < g.diameter) return true;
    else if(diameter == g.diameter) return aspl < g.aspl;
    else return false;
}
bool GridGraph::operator <= (const GridGraph & g) const {
    if(diameter < g.diameter) return true;
    else if(diameter == g.diameter) return aspl <= g.aspl;
    else return false;
}
bool GridGraph::operator > (const GridGraph & g) const {
    if(diameter > g.diameter) return true;
    else if(diameter == g.diameter) return aspl > g.aspl;
    else return false;
}
bool GridGraph::operator >= (const GridGraph & g) const {
    if(diameter > g.diameter) return true;
    else if(diameter == g.diameter) return aspl >= g.aspl;
    else return false;
}