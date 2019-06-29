#ifndef _BBMCX_H_
#define _BBMCX_H_
#include "Strategy.h"

class BBMCX : public Strategy {
  public:
    std::vector<int> getMaxClique(const Graph &G);
  private:
    std::vector<int> currentClique, currentMaxClique;
    Graph G;

    void REFMC(int s, const std::vector<int> &L, const std::vector<int> &color);
    void calcColor(std::vector<int> &L, std::vector<int> &color, int k);
};
#endif