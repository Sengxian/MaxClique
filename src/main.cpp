#include "Graph.h"
#include "bnb.h"
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char** argv) {
    Graph G;
    G.loadGraph((string("../testcase/")+string(argv[1])+string(".clq")).data());
    maxclq Maxclq;
    ints V = Maxclq.getMaxClique(G);
    cout<<V.size()<<endl;
    for(auto x:V)cout<<x<<" ";
    cout<<endl;
    return 0;
}
