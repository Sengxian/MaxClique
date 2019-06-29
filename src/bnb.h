#ifndef _BNB_H_
#define _BNB_H_
//Branch & Bound
#include "Strategy.h"
typedef std::vector<int> ints;
class maxclq:public Strategy{
public:
    maxclq():maxClique(ints(0)),LB(0){}
    ints getMaxClique(const Graph &G);
private:
    ints maxClique;//current maximum clique, lower bound
    int LB;
    void update(ints& C);
    void search(const Graph& G, ints C, ints V);
    int esti(const Graph& G, const ints &V);
    ints intersect(const ints& A, const ints& B);
};

#endif