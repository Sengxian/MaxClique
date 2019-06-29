#ifndef _STRATEGY_H_
#define _STRATEGY_H_
#include "Graph.h"
class Strategy {
  public:
    virtual std::vector<int> getMaxClique(const Graph &G) = 0;
};

#endif