#ifndef _MAXCLQ_H_
#define _MAXCLQ_H_
//Branch & Bound
#include "Strategy.h"

class MaxCLQ : public Strategy {
  public:
    MaxCLQ() : maxClique(ints(0)), LB(0) {}
    ints getMaxClique(const Graph &G);
  private:
    ints maxClique; // current maximum clique, lower bound
    int LB;
    void update(ints &C);
    void search(const Graph &G, ints C, ints V);
    int esti(const Graph& G, const ints &V);
    ints intersect(const ints &A, const Graph&G,int v);// intersect A with the neighbour of x
};

#endif