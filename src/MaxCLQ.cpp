#include "MaxCLQ.h"
#include <algorithm>
#include <iostream>

ints MaxCLQ::getMaxClique(const Graph &G){
    ints V;
    for(int i=0;i<G.n;++i)V.push_back(i);
    search(G,ints(0),V);
    return maxClique;
}

int MaxCLQ::esti(const Graph& G, const ints& V){
    return G.n;
}

void MaxCLQ::update(ints &C){
    int m=C.size();
    if(m>LB){
        LB=m;
        maxClique=C;
    }
}

ints MaxCLQ::intersect(const ints& A, const ints& B){
    ints C;
    for(ints::const_iterator pt1=A.begin(),pt2=B.begin();pt1!=A.end()&&pt2!=B.end();){
        if((*pt1)==(*pt2))C.push_back(*pt1),++pt1,++pt2;
        else if((*pt1)<(*pt2))++pt1;
        else ++pt2;
    }
    return C;
}

void MaxCLQ::search(const Graph &G, ints C, ints V){
    //std::cout<<C.size()<<" "<<V.size()<<std::endl;
    if (V.empty()){ 
        update(C);
        return;
    }
    int ub = C.size() + esti(G,V);
    if (ub <= LB) return;
    int v = G.mindeg(V);
    C.push_back(v);
    search(G, C, intersect(V, G.neighbour(v)));
    C.pop_back();
    V.erase(std::find(V.begin(), V.end(), v));   
    search(G, C, V);
}