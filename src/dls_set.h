#ifndef dls_set_h
#define dls_set_h
#include "Strategy.h"
#include <cstring>
#include <cassert>
#include <algorithm>
class dls_set{
public:
    int* lst,*ind;//list, index
    int N,sz;
//    dls_set():lst(0),ind(0),N(0),sz(0){}
    dls_set(int n):lst(0),ind(0),N(n),sz(0){
        lst=new int[n];
        ind=new int[n];
        memset(ind,-1,sizeof(ind));
    }
    void add(int x){
        if(ind[x]==-1){
            lst[sz]=x;
            ind[x]=sz++;
        }
    }
    void del(int x){
        if(ind[x]==-1)assert(0);
        lst[ind[x]]=lst[sz-1];
        ind[[lst[sz-1]]]=ind[x];
        ind[x]=-1;
        --sz;
    }
    ~dls_set(){
        if(lst)delete lst;
        if(ind)delete ind;
    }
};
#endif