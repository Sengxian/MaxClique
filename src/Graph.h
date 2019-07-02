#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>

typedef std::vector<int> ints;

class Graph {
  public:
    int n; // number of the vertices
    std::vector<ints > G; // adjacency matrix
    
    Graph(int sz = 0) : n(sz) {
      G.resize(n);
      for (int i = 0; i < n; ++i)
        G[i].resize(n);
    }

    bool loadGraph(const char *filename); // load graph from file
    const ints &operator[](const int &idx) const;
    ints &operator[](const int &idx);
    int degree(int v, ints &V) const;
    int mindeg(ints &V) const;
    ints neighbour(int v) const;
};

#endif