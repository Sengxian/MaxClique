#ifndef _STRATEGY_H_
#define _STRATEGY_H_

class Strategy {
  public:
    virtual std::vector<int> getMaxClique(const Graph &G) = 0;
};

#endif