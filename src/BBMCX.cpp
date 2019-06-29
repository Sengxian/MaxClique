#include "BBMCX.h"
#include <algorithm>
#include <iostream>
#define len(x) ((int)x.size())

std::vector<int> BBMCX::getMaxClique(const Graph &G) {
    this->G = G;
    currentClique.assign(G.n, 0);
    currentMaxClique.clear();

    std::vector<int> V(G.n, 0), col(G.n, G.n);
    for (int i = 0; i < G.n; ++i) V[i] = i;

    REFMC(0, V, col);

    std::sort(currentMaxClique.begin(), currentMaxClique.end());
    
    return currentMaxClique;
}

using std::cout;
using std::endl;

void BBMCX::REFMC(int s, const std::vector<int> &L, const std::vector<int> &color) {
    for (int i = len(L) - 1; i >= 0 && s + color[i] > len(currentMaxClique); --i) {
        int u = L[i];
        std::vector<int> newS, newL;
        
        // calculate new candidate set
        for (auto v : L) if (v != u && G[u][v]) newL.push_back(v);

        currentClique[s] = u;

        if (len(newL) == 0) {
            // update max clique
            if (s + 1 > len(currentMaxClique)) {
                currentMaxClique.assign(s + 1, 0);
                for (int j = 0; j < s + 1; ++j)
                    currentMaxClique[j] = currentClique[j];
            }
            continue;
        }

        std::vector<int> color(len(newL), 0);
        calcColor(newL, color, len(currentClique) - (s + 1));
        // cout << u << ' ' << len(newL) << ' ' << color[0] << ' ' << endl;
        REFMC(s + 1, newL, color);
    }
}

void BBMCX::calcColor(std::vector<int> &L, std::vector<int> &color, int k) {
    for (int &col : color) col = len(L);
}
