#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>

class Graph {
  public:
    int n; // number of the vertices
    std::vector<std::vector<int> > G; // adjacency matrix

    bool loadGraph(const char *filename);
    const std::vector<int>& operator [] (const int &idx) const;
};

#endif