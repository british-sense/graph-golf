#pragma once

#include <string>
#include <random>

namespace params{

    // general
    static int degree;
    static std::string input_edgefile;
    static std::string output_edgefile;

    // general graph
    static int node;

    // grid graph
    static int height;
    static int width;
    static int length;

    // others
    static int seed;
    static std::mt19937 mt;
}