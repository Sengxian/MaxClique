#ifndef _BBMCX_H_
#define _BBMCX_H_
#include "Strategy.h"

class BBMCX : public Strategy {
  public:
    std::vector<int> getMaxClique(const Graph &G);
    std::vector<int> order;
    bool cmp(int i, int j);
  private:
    std::vector<int> currentClique, currentMaxClique;
    std::vector<std::vector<int> > C;
    std::vector<int> deg, inC, isForbidden;
    Graph G;
    int cnt, cnt1;

    void greedy();
    void REFMC(int s, const std::vector<int> &L, const std::vector<int> &color);
    void calcOrder(const std::vector<int> &L);
    void calcColor(std::vector<int> &L, std::vector<int> &color, int k);
    bool reColor(int u, int k);
    bool reColorIC(int u, int k);
};
#endif