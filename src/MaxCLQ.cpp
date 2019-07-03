#include "MaxCLQ.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>
int step=0;
static int S[1000000];
static ints deg;
static int depth=0;
bool cmp(int a,int b){
    return deg[a]>deg[b];
}
ints MaxCLQ::getMaxClique(const Graph &G){
    deg.clear();
    deg.resize(G.n);
    std::fill(deg.begin(),deg.end(),0);
    for(int i=0;i<G.n;++i)
        for(int j=0;j<G.n;++j)
            deg[i]+=G[i][j];
    ints V;
    for(int i=0;i<G.n;++i)V.push_back(i);
    sort(V.begin(),V.end(),cmp);
    search(G,ints(0),V);
    // std::cerr<<step<<std::endl;
    return maxClique;
}
static void getColor(std::vector<ints > &color, const Graph &G, const ints& V){
    static ints Vec;
    //V=Vec;
    //std::sort(V.begin(),V.end(),cmp);
    if(S[depth]<=0.075*step){
        Vec=V;
        for(auto x:Vec)deg[x]=0;
        for(auto x:Vec)
            for(auto y:Vec)
                deg[x]+=G[x][y];
        std::sort(Vec.begin(),Vec.end(),cmp);
        for(auto &&x:Vec){
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
    else{        
        for(auto &&x:V){
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
}

static int getLooseSet(const Graph &G, ints& tested, std::vector<ints > &color, int cN, int x){
    //try to find a loose set containing color x,return 0: not found 1: found
    //cN: number of colors
    static std::vector<ints > __color;
    __color.clear();
    ints SEQ;
    for(int i = 0;i < cN;++i){
        if(!tested[i]){
            __color.push_back(color[i]);            
            SEQ.push_back(i);
        }
    }
    static ints LooseSet;
    LooseSet.clear();   
    LooseSet.push_back(x);
    bool flag=false;
    int N=__color.size();
    static std::queue<int> unit;
    static std::vector<ints > COLOR;
    for(auto v: color[x]){
        while(!unit.empty())unit.pop();
        ints ok(cN,0);
        COLOR = __color;
        ok[x]=1;
        int ind=0;
        for(auto& vec:COLOR){
            int n=vec.size();
            int i,j;
            for(i=0,j=0;i<n;++i){
                if(G[v][vec[i]])vec[j++]=vec[i];
            }
            vec.resize(j);
            if(j==1)unit.push(ind);
            ++ind;
        }
        bool f,g;
        while(1){
            f=false;
            for(int i=0;i<N;++i){
                if(!ok[SEQ[i]]&&COLOR[i].empty()){
                    LooseSet.push_back(SEQ[i]);
                    f=true;break;
                }
            }
            if(f)break;
            if(unit.empty())break;
            int p=unit.front();unit.pop();
            ok[SEQ[p]]=1;
            LooseSet.push_back(SEQ[p]);
            g=true;
            int v=COLOR[p][0];
            int ind=0;
            for(auto& vec:COLOR){
                int n=vec.size();
                int i,j;
                for(i=0,j=0;i<n;++i){
                    if(G[v][vec[i]])vec[j++]=vec[i];
                }
                vec.resize(j);
                if(j==1&&j<n)unit.push(ind);
                ++ind;
            }
        }
        if(!f){
            flag=true;
            break;
        }
    }
    tested[x]=true;
    if(flag)return 0;
    else{
        for(auto x:LooseSet){
            tested[x]=true;
        }
        return 1;
    }
}

int MaxCLQ::esti(const Graph& G, const ints& V){
    static std::vector<ints> color;
    static std::vector<ints> __color;
    static std::vector<std::pair<int, int> > seq;
    color.clear();
    getColor(color, G, V);
    int UB=color.size();
    ints tested(UB, 0);
    __color.clear();seq.clear();
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
ints MaxCLQ::intersect(const ints& A, const Graph &G,int v){//intersect A with neighbour(v) in G
    ints C;
    for(auto x:A){
        if(G[x][v])C.push_back(x);
    }
    return C;
}

void MaxCLQ::search(const Graph &G, ints C, ints V){
    ++step;
    ++depth;
    ++S[depth];
    if (V.empty()){ 
        update(C);
        --depth;
        return;
    }
    int ub = C.size() + esti(G,V);
    if (ub <= LB){ 
        --depth;
        return;
    }
    int v = G.mindeg(V);
    C.push_back(v);
    search(G, C, intersect(V,G,v));
    C.pop_back();
    V.erase(std::find(V.begin(), V.end(), v));   
    search(G, C, V);
    --depth;
}
