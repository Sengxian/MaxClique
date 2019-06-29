#ifndef _BBMCX_H_
#define _BBMCX_H_
#include "Strategy.h"

class BBMCX : public Strategy {
  public:
    std::vector<int> getMaxClique(const Graph &G);
};

#endif