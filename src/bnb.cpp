#include "bnb.h"
#include <algorithm>
ints maxclq::getMaxClique(const Graph &G){
    ints V;
    for(int i=0;i<G.n;++i)V.push_back(i);
    search(G,ints(0),V);
    return maxClique;
}
int maxclq::esti(const Graph& G, const ints& V){
    return G.n;
}
void maxclq::update(ints &C){
    int m=C.size();
    if(m>LB){
        LB=m;
        maxClique=C;
    }
}
ints maxclq::intersect(const ints& A, const ints& B){
    ints C;
    for(ints::const_iterator pt1=A.begin(),pt2=B.begin();pt1!=A.end()&&pt2!=B.end();){
        if((*pt1)==(*pt2))C.push_back(*pt1),++pt1,++pt2;
        else if((*pt1)<(*pt2))++pt1;
        else ++pt2;
    }
    return C;
}
void maxclq::search(const Graph &G, ints C, ints V){
    if (V.empty()) update(C);
    int ub = C.size() + esti(G,V);
    if (ub <= LB) return;
    int v = G.mindeg();
    C.push_back(v);
    search(G, C, intersect(V, G.neighbour(v)));
    C.pop_back();
    V.erase(std::find(V.begin(), V.end(), v));   
    search(G, C, V);
}