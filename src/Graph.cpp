#include "Graph.h"
#include <fstream>

bool Graph::loadGraph(const char *filename) {
    std::ifstream in(filename);
    if (in) {

        return true;
    } else {
        return false;
    }
}

const std::vector<int>& Graph::operator [] (const int &idx) const {
    return G[idx];
}
