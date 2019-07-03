#include <iostream>
#include <string>
#include "Graph.h"
#include "MaxCLQ.h"
#include "BBMCX.h"
#include "BBMCX_BITSET.h"
#include "Estimator.h"
#include "dls.h"
using namespace std;

int main(int argc, char** argv) {
    Graph G;
    if (argc == 1) {
        cout << "Please input testcase name, e.g. ./main brock200_0" << endl;
        return 0;
    } else if (argc == 2) {
        cout << "Please input strategy:\n";
        cout << "\t 1 - BBMCX_BITSET\n";
        cout << "\t 2 - BBMCX\n";
        cout << "\t 3 - MaxCLQ\n";
        cout << "\t 4 - DLS\n";
        return 0;
    } else {
        if (!G.loadGraph((string("../testcase/") + string(argv[1]) + string(".clq")).data())) {
            cout << "Cannot read data!" << endl;
            return 0;
        }
    }
    
    Strategy *stg;

    if (argv[2][0] == '1') stg = new BBMCX_BITSET();
    else if (argv[2][0] == '2') stg = new BBMCX();
    else if (argv[2][0] == '3') stg = new MaxCLQ();
    else if (argv[2][0] == '4') stg = new DLS();
    else {
        cout << "error strategy!\n";
        return 0;
    }

    // Estimate runtime
    Estimator estimator;
    estimator.estimate(stg, G);

    return 0;
}
