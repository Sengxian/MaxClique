#ifndef dls_h
#define dls_h
#include "dls_set.h"
class DLS:public Strategy{
public:
    DLS():maxClique(1),LB(0){}
    ints getMaxClique(const Graph &G);
private:
    dls_set maxClique; // current maximum clique, lower bound
    int LB;
    void update(dls_set &C);
    int PD,PDcnt;//penalty delay;
    int numSteps;
    ints penalty;
    ints mark;int T;
    void initPenalty(int n);//set penalty to zero
    void updatePenalty();
    int MinPenalty(const dls_set& S);
    dls_set DLS_MC(const Graph &G, int target, int pd, int maxSteps);//heuristic to find a clique of size target
    bool expand(const Graph &G, dls_set& C, int &v);//return true if at least one point is added
    void plateauSearch(const Graph &G, dls_set &C,int C_, int &v);
};
#endif