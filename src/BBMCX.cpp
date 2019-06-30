#include "BBMCX.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <climits>
#include <cassert>
#define len(x) ((int)x.size())

using std::cout;
using std::endl;

void print(const std::vector<int> &vec, const char *str = "", int del = 0) {
    cout << str;
    for (auto x : vec) cout << x + del << ' '; cout << endl;
}

std::vector<int> BBMCX::getMaxClique(const Graph &G) {
    int n = G.n;

    this->G = G;
    currentClique.assign(n, 0);
    currentMaxClique.clear();
    inC.assign(n, false);
    isDeleted.assign(n, false);
    isForbidden.assign(n, false);
    C.resize(n);
    order.assign(n, 0);
    cnt = 0;

    // calculate L
    std::vector<int> deg(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (G[i][j]) ++deg[i], ++deg[j];
    
    std::vector<int> V(n, 0), col(n, *std::max_element(deg.begin(), deg.end()) + 1);

    // smallest degree-last
    for (int i = 0; i < n; ++i) {
        int u = -1, mn = INT_MAX;
        for (int j = 0; j < n; ++j)
            if (deg[j] <= mn) u = j, mn = deg[j];
        // print(deg, "deg ");
        deg[u] = INT_MAX, col[i] = std::min(i + 1, col[i]);
        V[n - i - 1] = u;
        order[u] = n - i - 1;
        // V[i] = u;
        for (int v = 0; v < n; ++v)
            if (G[u][v]) --deg[v];
    }

    // print(V, "V: ", 1);

    REFMC(0, V, col);
    std::cerr << "Iteration num: " << cnt << std::endl;
    std::sort(currentMaxClique.begin(), currentMaxClique.end());
    
    return currentMaxClique;
}

bool BBMCX::cmp(int i, int j) {
    return order[i] < order[j];
}

void BBMCX::REFMC(int s, const std::vector<int> &L, const std::vector<int> &color) {
    ++cnt;
    std::vector<int> newL, col;

/*
    cout << "Clique: ";
    for (int i = 0; i < s; ++i) cout << currentClique[i] + 1 << ' '; cout << endl;
    print(L, "L: ", 1);
    print(color, "color: ");
*/

    for (int i = len(L) - 1; i >= 0 && s + color[i] > len(currentMaxClique); --i) {
        int u = L[i];

        newL.clear(), col.clear(); 
        // calculate new candidate set
        for (int j = 0; j < i; ++j) if (G[u][L[j]]) newL.push_back(L[j]);

        currentClique[s] = u;
        
        // update max clique
        if (s + 1 > len(currentMaxClique)) {
            currentMaxClique.assign(s + 1, 0);
            for (int j = 0; j < s + 1; ++j)
                currentMaxClique[j] = currentClique[j];
        }

        if (len(newL) == 0) continue;

        col.assign(len(newL), 0);
        calcColor(newL, col, len(currentMaxClique) - (s + 1) + 1);
        REFMC(s + 1, newL, col);
    }
}

void BBMCX::calcColor(std::vector<int> &L, std::vector<int> &color, int k) {
    static std::vector<int> U, V, F;

    U = L;

    std::sort(U.begin(), U.end(), [&](const int &i, const int &j) {
        return order[i] < order[j];
    });

    // print(U, "L: ", 1);
    // cout << k << endl;
    // print(color, "color: ");

    int t = len(L),
        cnt = 0, c = 0;

    for (c = 0; U.size(); ++c, U = V) {
        isForbidden[c] = false;
        for (int u : U) inC[u] = true;
        V.clear(), C[c].clear(); 
        for (int j = 0; j < len(U); ++j) {
            int u = U[j];
            if (inC[u]) {
                if (c + 1 < k || !reColorIC(u, k)) {
                    C[c].push_back(u);
                    for (int t = j + 1; t < len(U); ++t)
                        inC[U[t]] &= !G[u][U[t]];
                } else inC[u] = false;
            } else V.push_back(u);
        }
    }

    for (int i = 0; i < c; ++i)
        for (int u : C[i])
            L[cnt] = u, color[cnt++] = i + 1;

    L.resize(cnt), color.resize(cnt);
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

bool BBMCX::reColorIC(int u, int k) {
    for (int c1 = 0; c1 < k - 1; ++c1) {
        if (isForbidden[c1]) continue;
        int v = -1;
        for (int t : C[c1])
            if (G[u][t]) {
                if (v >= 0) {
                    v = -2;
                    break;
                } else {
                    v = t;
                }
            }
        
        if (v >= 0) {
            for (int c2 = c1 + 1; c2 < k - 1; ++c2) {
                if (isForbidden[c2]) continue;
                bool flag = true;
                for (int t : C[c2])
                    if (G[v][t] && G[u][t]) {
                        flag = false;
                        break;
                    }
                if (flag) {
                    isForbidden[c1] = isForbidden[c2] = true;
                    return true;
                }            
           } 
           for (int c2 = 0; c2 < c1; ++c2) {
                if (isForbidden[c2]) continue;
                bool flag = true;
                for (int t : C[c2])
                    if (G[v][t] && G[u][t]) {
                        flag = false;
                        break;
                    }
                if (flag) {
                    isForbidden[c1] = isForbidden[c2] = true;
                    return true;
                }            
           } 
        }
    }

    return false;
}
