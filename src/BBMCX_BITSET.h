#ifndef _BBMCX_BITSET_H_
#define _BBMCX_BITSET_H_
#include "Strategy.h"
#include <bitset>

class BBMCX_BITSET : public Strategy {
  public:
    std::vector<int> getMaxClique(const Graph &G);
    bool cmp(int i, int j);
  private:
    static const int SIZE = 800;
    std::vector<int> currentClique, currentMaxClique;
    std::vector<std::vector<int> > C;
    std::vector<int> deg, isForbidden;
    std::vector<int> order, newOrder;
    std::bitset<SIZE> in;
    std::vector<std::bitset<SIZE> > Cb, Gb, GbR;
    Graph G;
    int cnt, cnt1;

    static void print(const std::vector<int> &vec, const char *str = "", int del = 0);
    void greedy();
    void REFMC(int s, const std::vector<int> &L, const std::vector<int> &color);
    void calcOrder(const std::vector<int> &L);
    void calcColor(std::vector<int> &L, std::vector<int> &color, int k, bool reCalc = false);
    bool reColorIC(int u, int k);
};

#endif