#include "Estimator.h"
#include <iostream>
#include <ctime>

void Estimator::estimate(Strategy *stg, const Graph &G) {
    int start = clock();

    std::vector<int> maxClique = stg->getMaxClique(G);

    std::cout << maxClique.size() << std::endl;
    for (int i = 0; i < (int)maxClique.size(); ++i)
        std::cout << maxClique[i] << (i + 1 == (int)maxClique.size() ? '\n' : ' ');

    std::cerr << "Time used: " << (clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
}
