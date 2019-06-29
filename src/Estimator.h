#ifndef _ESTIMATOR_H_
#define _ESTIMATOR_H_
#include "Strategy.h"

class Estimator {
  public:
     void estimate(Strategy *stg, const Graph &G);
};

#endif