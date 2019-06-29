#include "MaxCLQ.h"
#include <algorithm>
#include <iostream>
ints MaxCLQ::getMaxClique(const Graph &G){
    ints V;
    for(int i=0;i<G.n;++i)V.push_back(i);
    search(G,ints(0),V);
    return maxClique;
}

static void getColor(std::vector<ints > &color, const Graph &G, const ints& V){
    for(auto&& x:V){
        bool flag=false;
        for(auto& vec:color){
            flag=true;
            for(auto&& p:vec){
                if(G[p][x]){
                    flag=false;
                    break;
                }
            }
            if(flag){
                vec.push_back(x);
                break;
            }
        }
        if(!flag){
            color.push_back(ints(1,x));
        }
    }
}
static int getLooseSet(const Graph &G, ints& tested, std::vector<ints > &color, int cN, int x){
    //try to find a loose set containing color x,return 0: not found 1: found
    //cN: number of colors
    std::vector<ints > __color;
    for(int i = 0;i < cN;++i){
        if(!tested[i]){
            __color.push_back(color[i]);            
        }
    }
    ints LooseSet;LooseSet.push_back(x);
    ints del(cN,0);
    bool flag=false;
    for(auto v: color[x]){
        std::fill(del.begin(),del.end(),0);
        del[x]=1;

        while(1){
            
        }
    }
    if(flag)return 0;
    else{
        for(auto x:LooseSet){
            tested[x]=true;
        }
        return 1;
    }
}
int MaxCLQ::esti(const Graph& G, const ints& V){
    std::vector<ints> color;
    getColor(color, G, V);
//    return color.size();
    //advanced upper bound
    int UB=color.size();
    ints tested(UB, 0);
    std::vector<ints> __color;
    std::vector<std::pair<int, int> > seq;
    int ind=0;
    for(auto &vec : color){
        seq.push_back(std::make_pair(vec.size(), ind) );
        ++ind;
    }
    std::sort(seq.begin(), seq.end());
    int inconsSets = 0;//inconsistent sets
    for(auto pr : seq){
        if(!tested[pr.second]){
            inconsSets += getLooseSet(G, tested, color, UB, pr.second);
        }
    }
    return UB-inconsSets;
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
