#include <iostream>
#include <ctime>
#include "Estimator.h"
#include "Validator.h"

void Estimator::estimate(Strategy *stg, const Graph &G) {
    int start = clock();

    std::vector<int> maxClique = stg->getMaxClique(G);

    std::cout << maxClique.size() << std::endl;
    for (int i = 0; i < (int)maxClique.size(); ++i)
        std::cout << maxClique[i] << (i + 1 == (int)maxClique.size() ? '\n' : ' ');

    Validator validator;

    if (validator.check(G, maxClique)) std::cerr << "Test passed!" << std::endl;
    else std::cerr << "Failed on test!" << std::endl;

    std::cerr << "Time used: " << (clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
}
