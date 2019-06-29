#include "Graph.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
bool Graph::loadGraph(const char *filename) {
    std::ifstream in(filename);
    if (in) {
        std::string tmp;
        std::stringstream ss;
        int m;
        int u, v;
        while(getline(in,tmp)){
            if(tmp[0] == 'p'){
    
                ss.clear();
                ss.str(tmp);
                ss >> tmp >> tmp;
                ss >> this->n >> m;
    //            std::cout<<n<<" "<<m<<std::endl;
                G.resize(n);
                for(int i = 0;i < n;++i)G[i].resize(n);
    
            }
            else if(tmp[0]=='e'){
//                std::cout<<tmp<<std::endl;
                ss.clear();
                ss.str(tmp);
                ss >> tmp;
                ss >> u >> v;
                u--;v--;
  //              std::cout<<u<<" "<<v<<std::endl;
                G[u][v]=G[v][u]=1;
            }
        }
        return true;
    } else {
        return false;
    }
}
int Graph::degree(int v)const{
    int cnt=0;
    const ints& V=G[v];
    for(auto&& x:V)cnt+=x;
    return cnt;
}
int Graph::mindeg(ints &V)const{
    int min=n,v=-1;
    for(auto x:V){
        int cnt=degree(x);
        if(cnt<min)v=x;
    }
    return v;
}
const ints& Graph::operator [] (const int &idx) const {
    return G[idx];
}
ints Graph::neighbour(int v)const{
    ints V;
    for(int i=0;i<n;++i)if(G[v][i])V.push_back(i);
    return V;
}
/*
Graph Graph::without(int v){
    Graph Q(n-1);
    for(int i=0;i<v;++i){
        for(int j=0;j<v;++j){
            Q[i][j]=G[i][j];            
        }
    }
    
    for(int i=v;i<n-1;++i){
        for(int j=0;j<v;++j){
            Q[i][j]=G[i+1][j];
        }
    }

    for(int i=0;i<v;++i){
        for(int j=v;j<n-1;++j){
            Q[i][j]=G[i][j+1];
        }
    }
    
    for(int i=v;i<n-1;++i){
        for(int j=v;j<n-1;++j){
            Q[i][j]=G[i+1][j+1];
        }
    }
    return Q;
}

Graph Graph::neighbour(int v){
    ints
}
*/