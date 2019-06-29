#include "Graph.h"
#include "bnb.h"
#include <iostream>
using namespace std;
int main() {
    Graph G;
    G.loadGraph("../testcase/brock200_4.clq");
    maxclq Maxclq;
    ints V = Maxclq.getMaxClique(G);
    cout<<V.size()<<endl;
    for(auto x:V)cout<<x<<" ";
    cout<<endl;
    return 0;
}
