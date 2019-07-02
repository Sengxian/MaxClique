#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_
#include <vector>
#include "Graph.h"

class Validator {
  public:
    bool check(const Graph &G, std::vector<int> maxClique); // check if it's a clique
};

#endif