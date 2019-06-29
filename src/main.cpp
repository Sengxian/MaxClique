#include <iostream>
#include <string>
#include "Graph.h"
#include "MaxCLQ.h"
#include "BBMCX.h"
#include "Estimator.h"
using namespace std;

int main(int argc, char** argv) {
    Graph G;
    if (argc == 1) {
        cout << "Please input testcase name, e.g. ./main brock200_0" << endl;
        return 0;
    } else {
        G.loadGraph((string("../testcase/") + string(argv[1]) + string(".clq")).data());
    }
    
    // Estimate runtime
    Estimator estimator;
    if(argc==2)estimator.estimate(new BBMCX(), G);
    else if(argc==3)estimator.estimate(new MaxCLQ(), G);
    return 0;
}
