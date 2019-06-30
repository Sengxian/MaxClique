#include "BBMCX.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <climits>
#include <cassert>
#define len(x) ((int)x.size())

using std::cout;
using std::endl;

std::vector<int> BBMCX::getMaxClique(const Graph &G) {
    int n = G.n;

    this->G = G;
    currentClique.assign(n, 0);
    currentMaxClique.clear();
    inC.assign(n, false);
    C.resize(n);

    // calculate L
    std::vector<int> deg(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (G[i][j]) ++deg[i], ++deg[j];
    
    std::vector<int> V(n, 0), col(n, *std::max_element(deg.begin(), deg.end()) + 1);

    // smallest degree-last
    for (int i = 0; i < n; ++i) {
        int u = min_element(deg.begin(), deg.end()) - deg.begin();
        deg[u] = INT_MAX, col[i] = std::min(i + 1, col[i]);
        V[i] = u;
        for (int v = 0; v < n; ++v)
            if (G[u][v]) --deg[v];
    }

    REFMC(0, V, col);

    std::sort(currentMaxClique.begin(), currentMaxClique.end());
    
    return currentMaxClique;
}

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
        // return;
        // cout << u << ' ' << len(newL) << ' ' << color[0] << ' ' << endl;
        REFMC(s + 1, newL, color);
    }
}

void BBMCX::calcColor(std::vector<int> &L, std::vector<int> &color, int k) {
    // for (int &col : color) col = len(L);

    static std::vector<int> U, V;
    U = L;

    int t = len(L), cnt = 0, c = 0;

    for (c = 0; U.size(); ++c) {
        for (int u : U) inC[u] = true;
        for (int j = 0; j < len(U); ++j) if (inC[U[j]]) {
            int u = U[j];
            bool flag = false;
            if (c + 1 >= k) {
                // recolor
                flag = reColor(u, k);
            }
            if (flag == false) {
                for (int k = j + 1; k < len(U); ++k) {
                    if (G[u][U[k]]) inC[U[k]] = false;
                }
            } else inC[U[k]] = false;
        }

        V.clear(), C[c].clear(); 
        for (int u : U)
            if (inC[u]) C[c].push_back(u);
            else V.push_back(u); 
        U = V;
    }

    for (int i = 0; i < c; ++i)
        for (int u : C[i])
            L[cnt] = u, color[cnt++] = i + 1;
    // for (auto u : L) cout << u << ' '; cout << endl;
}

bool BBMCX::reColor(int u, int k) {
    for (int c1 = 0; c1 < k - 2; ++c1) {
        int v = -1;
        for (int t : C[c1])
            if (G[u][t]) {
                if (v != -1) {
                    v = -2;
                    break;
                } else {
                    v = t;
                }
            }
        
        if (v >= 0) {
            for (int c2 = c1 + 1; c2 < k - 1; ++c2) {
                bool flag = true;
                for (int t : C[c2])
                    if (G[v][t]) {
                        flag = false;
                        break;
                    }
                if (flag) {
                    C[c2].push_back(v);
                    C[c1].push_back(u);
                    C[c1].erase(std::find(C[c1].begin(), C[c1].end(), v));
                    return true;
                }            
           } 
        } else if (v == -1) {
            C[c1].push_back(u);
            return true;
        }
    }

    return false;
}
