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
int Graph::degree(int v, ints &V)const{
    int cnt=0;
    for(auto x:V)cnt+=G[x][v];
    return cnt;
}
int Graph::mindeg(ints &V)const{
    int min=n,v=-1;
    for(auto x:V){
        int cnt=degree(x,V);
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