#include "MaxCLQ.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
int step=0;
ints MaxCLQ::getMaxClique(const Graph &G){
    ints V;
    for(int i=0;i<G.n;++i)V.push_back(i);
    search(G,ints(0),V);
    std::cout<<step<<std::endl;
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

static int getLooseSet(const Graph &G, const ints& Vec,ints& tested, std::vector<ints > &color, int cN, int x){
    //try to find a loose set containing color x,return 0: not found 1: found
    //cN: number of colors
    std::map<int, std::set<int> >  __color;
    ints col(G.n,0);
    for(int i = 0;i < cN;++i){
        if(!tested[i]){
            __color[i]=std::set<int>(color[i].begin(),color[i].end());
            for(auto x:color[i]){
                col[x]=i;
            }
        }
    }
    ints V;
    for(auto v: Vec){
        if(!tested[col[v]])V.push_back(v);
    }
    ints LooseSet;
    LooseSet.push_back(x);

    bool flag=false;
    for(auto v: color[x]){
        ints ok(cN,0);
        std::map<int, std::set<int> > COLOR = __color;
        ok[x]=1;
        for(auto i:V){
            if(!G[i][v])COLOR[col[i]].erase(i);
        }
        COLOR.erase(x);
        bool f,g;
        while(1){
            f=false;
            int tmp=-1;
            for(auto &PAIR:COLOR){
                if(!ok[PAIR.first]&&PAIR.second.empty()){
                    LooseSet.push_back(PAIR.first);
                    tmp=PAIR.first;
                    f=true;break;
                }
            }
            if(f){
                COLOR.erase(tmp);
                break;
            }
            g=false;
            tmp=-1;
            for(auto &PAIR:COLOR){
                if(PAIR.second.size()==1){
                    tmp=PAIR.first;
                    ok[PAIR.first]=1;
                    LooseSet.push_back(PAIR.first);
                    g=true;
                    int v=*(PAIR.second.begin());
                    for(auto i:V){
                       if(!G[i][v])COLOR[col[i]].erase(i);
                    }
                    break;  
                }
            }
            if(g) COLOR.erase(tmp);
            else break;

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

static int getLooseSet(const Graph &G, ints& tested, std::vector<ints > &color, int cN, int x){
    //try to find a loose set containing color x,return 0: not found 1: found
    //cN: number of colors
    //std::cout<<"cN"<<cN<<" x"<<x<<std::endl;
    std::vector<ints > __color;
    ints SEQ;
    for(int i = 0;i < cN;++i){
        if(!tested[i]){
            __color.push_back(color[i]);            
            SEQ.push_back(i);
        }
    }
    ints LooseSet;
    LooseSet.push_back(x);
    bool flag=false;
    int N=__color.size();
    for(auto v: color[x]){
        ints ok(cN,0);
        //std::cout<<"v="<<v<<std::endl;
        std::vector<ints > COLOR = __color;
        ok[x]=1;
        for(auto& vec:COLOR){
            int n=vec.size();
            int i,j;
            for(i=0,j=0;i<n;++i){
                if(G[v][vec[i]])vec[j++]=vec[i];
            }
            vec.resize(j);
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
            g=false;
            for(int i=0;i<N;++i){
                if(COLOR[i].size()==1){
                    ok[SEQ[i]]=1;
                    LooseSet.push_back(SEQ[i]);
                    g=true;
                    int v=COLOR[i][0];
                    for(auto& vec:COLOR){
                       int n=vec.size();
                        int i,j;
                        for(i=0,j=0;i<n;++i){
                            if(G[v][vec[i]])vec[j++]=vec[i];
                        }
                        vec.resize(j);
                    }
                    break;  
                }
            }
            if(!g)break;
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
    std::vector<ints> color;
    getColor(color, G, V);
    return color.size();
    //advanced upper bound
    int UB=color.size();
    //std::cout<<"color"<<UB<<std::endl;
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
//            inconsSets += getLooseSet(G, tested, color, UB, pr.second);
            inconsSets += getLooseSet(G,V, tested, color, UB, pr.second);
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
 //   std::cout<<cnt<<std::endl;
   // std::cout<<C.size()<<" "<<V.size()<<std::endl;
   ++step;
    if (V.empty()){ 
        update(C);
        return;
    }
    int ub = C.size() + esti(G,V);
    //std::cout<<"UB=="<<ub<<std::endl;
    if (ub <= LB) return;
    int v = G.mindeg(V);
    C.push_back(v);
    search(G, C, intersect(V, G.neighbour(v)));
    C.pop_back();
    V.erase(std::find(V.begin(), V.end(), v));   
    search(G, C, V);
}
