#ifndef dls_set_h
#define dls_set_h
#include "Strategy.h"
#include <cstring>
#include <cassert>
#include <algorithm>
class dls_set{// set consisting of two array in DLS algorithm 
public:
    int* lst,*ind;// list, index
    int N,sz;//N: memory occupied sz: elements stored
    dls_set(int n):lst(0),ind(0),N(n),sz(0){
        lst = new int[n];
        ind = new int[n];
        memset(ind,-1,sizeof(int)*N);// -1 for not exist
    }
    dls_set(const Graph &G, const dls_set &C):lst(0),ind(0),N(G.n),sz(0){ // construct improving set of C in G
        lst = new int[G.n];
        ind = new int[G.n];
        memset(ind, -1, sizeof(int)*N);
        for(int i=0;i<G.n;++i){
            bool flag=true;
            for(int j=0;j<C.sz;++j){
                if(!G[i][C.lst[j]]){
                    flag=false;
                    break;
                }
            }
            if(flag){
                lst[sz]=i;
                ind[i]=sz++;
            }
        }
    }
    dls_set(const Graph &G, const dls_set &C, int t):lst(0),ind(0),N(G.n),sz(0){ // construct level set of C in G
        lst = new int[G.n];
        ind = new int[G.n];
        memset(ind, -1, sizeof(int)*N);
        for(int i=0;i<G.n;++i){
            int cnt=0;
            for(int j=0;j<C.sz;++j){
                if(!G[i][C.lst[j]]){
                    ++cnt;
                    if(cnt>1)break;
                }
            }
            if(cnt==1){
                lst[sz]=i;
                ind[i]=sz++;
            }
        }
    }
    void add(int x){// O(1)
        if(ind[x]==-1){
            lst[sz]=x;
            ind[x]=sz++;
        }
    }
    void del(int x){// O(1)
        if(ind[x]==-1)assert(0);
        lst[ind[x]]=lst[sz-1]; //use the last element in list to overwrite the deleted element
        ind[lst[sz-1]]=ind[x];
        ind[x]=-1;
        --sz;
    }
    void del_not_neigh(const Graph &G, int v){
        for(int i=0;i<sz;++i){
            if(!G[lst[i]][v]){
                del(lst[i]);
                --i;
            }
        }
    }
    ~dls_set(){
        if(lst)delete lst;
        if(ind)delete ind;
    }
    dls_set(const dls_set& B):N(B.N),sz(B.sz){

        lst=new int[B.N];
        ind=new int[B.N];
        memcpy(lst,B.lst,sizeof(int)*N);
        memcpy(ind,B.ind,sizeof(int)*N);
    }
    dls_set& operator =(dls_set& B){
        if(lst)delete lst;
        if(ind)delete ind;
        N=B.N;sz=B.sz;
        lst=new int[B.N];
        ind=new int[B.N];
        memcpy(lst,B.lst,sizeof(int)*N);
        memcpy(ind,B.ind,sizeof(int)*N);
        return *this;
    }
    void clear(){
        for(int i=0;i<sz;++i){
            ind[lst[i]]=-1;
        }
        sz=0;
    }
};
#endif