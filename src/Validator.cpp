#include "Validator.h"

bool Validator::check(const Graph &G, std::vector<int> maxClique) {
    for (int i = 0; i < (int)maxClique.size(); ++i)
        for (int j = 0; j < i; ++j)
            if (!G[maxClique[i]][maxClique[j]])
                return false;
    return true;
}
