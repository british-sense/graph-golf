#pragma once

#include <string>

#include "params.hpp"

void input_setting(int argc, char * argv[]) {
    // -f : input edgefile name
    // -o : output edgefile name
    // -h : height value
    // -w : width value
    // -d : degree value
    // -l : length value
    // -s : seed value
    for(int i = 1; i < argc; i++){
        std::string opt(argv[i]);
        std::string args(argv[(i + 1) % argc]);
        if(opt == "-f" || opt == "--input") params::input_edgefile = args;
        if(opt == "-o" || opt == "--output") params::output_edgefile = args;
        if(opt == "-h" || opt == "--height") params::height = std::stoi(args);
        if(opt == "-w" || opt == "--width") params::width = std::stoi(args);
        if(opt == "-d" || opt == "--degree") params::degree = std::stoi(args);
        if(opt == "-l" || opt == "--length") params::length = std::stoi(args);
        if(opt == "-s" || opt == "--seed") params::seed = std::stoi(args);
    }
    params::mt = std::mt19937(params::seed);
}