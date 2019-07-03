#include "dls.h"
#include <cstdlib>
#include <cstdio>
static int Rand(int n){
    return rand()%n;
}
ints DLS::getMaxClique(const Graph &G){
    dls_set result=DLS_MC(G,1000000,2,10000);
    return ints(result.lst,result.lst+result.sz);   
    
}
void DLS::initPenalty(int n){
    penalty.resize(n);
    std::fill(penalty.begin(),penalty.end(),0);
    mark.resize(n);T=1;
    std::fill(mark.begin(),mark.end(),0);
}
void DLS::updatePenalty(){
    --PDcnt;
    if(PDcnt==0){
        for(auto &x:penalty){
            if(x)--x;
        }
        PDcnt=PD;
    }
    //after PD rounds, positive penalties are decreased by 1
}
bool DLS::expand(const Graph &G, dls_set& C, int &v){//return true if at least one point is added
    dls_set N(G,C);++T;
    if(N.sz==0)return false;
    while(N.sz != 0){
        v=MinPenalty(N);
        C.add(v);
        ++numSteps;
        N.del_not_neigh(G,v);
    }
    return true;
}
int DLS::MinPenalty(const dls_set& S){
    int p=-1,min=0x3f3f3f3f;
    for(int i=0;i<S.sz;++i){
        if(mark[S.lst[i]]==T)continue;
        if(penalty[S.lst[i]]<min){
            min=penalty[S.lst[i]];
            p=S.lst[i];
        }
    }
    return p;
}
void DLS::plateauSearch(const Graph &G, dls_set &C, int C_, int &v){
    dls_set NL(G,C,1);++T;
    while(NL.sz!=0){
        v=MinPenalty(NL);
        C.del_not_neigh(G,v);
        C.add(v);mark[v]=T;
        ++numSteps;
        dls_set N(G,C);
        if(N.sz!=0)break;
        --C_;
        if(C_==0)break;
        dls_set tmp(G,C,1);
        NL=tmp;
    }
}
void DLS::update(dls_set& A){
    if(A.sz>LB){
        LB=A.sz;
        maxClique=A;
    }
}
dls_set DLS::DLS_MC(const Graph &G, int target, int pd, int maxSteps){// pd: penalty delay maxSteps: iteration limit
    // return the max clique it can find with size<=target

    // initilization, C contains one randomly selected point
    numSteps=0;
    int v=Rand(G.n);
    dls_set C(G.n);
    C.add(v);
    initPenalty(G.n);
    PD=pd;PDcnt=pd;
 
    while(numSteps < maxSteps){
        expand(G,C,v);
        int C_=C.sz;
        plateauSearch(G, C, C_, v);
        while(expand(G, C, v)){ // alternate between expand and plateauSearch
            plateauSearch(G, C, C_, v);
            if(C.sz >= target)return C;
        }
        for(int i=0;i<C.sz;++i){
            penalty[C.lst[i]]++;
        }
        update(C);
        updatePenalty();
        if(pd > 1){
            C.clear();C.add(v);
        }else{
            v=Rand(G.n);
            // rearrange(G,C,v);
            // pd==1 part was not implemented, because pd > 1 provide better performance
        }
    }
    return maxClique;
    //return C;
}