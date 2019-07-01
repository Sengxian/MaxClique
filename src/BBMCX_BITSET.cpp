#include "BBMCX_BITSET.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <climits>
#include <cassert>
#define len(x) ((int)x.size())

void BBMCX_BITSET::print(const std::vector<int> &vec, const char *str, int del) {
    std::cout << str;
    for (auto x : vec) std::cout << x + del << ' '; std::cout << std::endl;
}

std::vector<int> BBMCX_BITSET::getMaxClique(const Graph &G) {
    int n = G.n;

    this->G = G;
    currentClique.assign(n, 0);
    currentMaxClique.clear();
    isForbidden.assign(n, false);
    C.resize(n);
    order.assign(n, 0);
    newOrder.assign(n, 0);
    cnt = 0;
    cnt1 = 0;

    // init bitset
    Gb.resize(n), GbR.resize(n);
    Cb.resize(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (G[i][j]) Gb[i].set(j), GbR[i].reset(j);
            else Gb[i].reset(j), GbR[i].set(j);

    // calculate L
    deg.assign(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (G[i][j]) ++deg[i], ++deg[j];
    
    greedy(); // apply greedy algorithm for better pruning
    std::cerr << "Greedy result: " << currentMaxClique.size() << std::endl;

    std::vector<int> V(n, 0), col(n, *std::max_element(deg.begin(), deg.end()) + 1);

    // smallest degree-last
    for (int i = 0; i < n; ++i) {
        int u = -1, mn = INT_MAX;
        for (int j = 0; j < n; ++j)
            if (deg[j] <= mn) u = j, mn = deg[j];
        // print(deg, "deg ");
        deg[u] = INT_MAX, col[i] = std::min(i + 1, col[i]);
        V[n - i - 1] = u;
        newOrder[u] = order[u] = n - i - 1;
        // V[i] = u;
        for (int v = 0; v < n; ++v)
            if (G[u][v]) --deg[v];
    }

    // print(V, "V: ", 1);
    REFMC(0, V, col);
    std::cerr << "Iteration num: " << cnt << std::endl;
    std::cerr << "Iteration num: " << cnt1 << std::endl;
    std::sort(currentMaxClique.begin(), currentMaxClique.end());

    return currentMaxClique;
}

void BBMCX_BITSET::greedy() {
    std::vector<int> V, U;
    for (int i = 0; i < G.n; ++i) V.push_back(i);
    while (V.size()) {
        int idx = -1, mx = -1;
        for (int u : V)
            if (deg[u] >= mx) {
                mx = deg[u], idx = u;
            }
        currentMaxClique.push_back(idx);
        U.clear();
        for (int u : V) if (u != idx && G[idx][u])
            U.push_back(u);
        V = U;
    }
}

bool BBMCX_BITSET::cmp(int i, int j) {
    return order[i] < order[j];
}

void BBMCX_BITSET::REFMC(int s, const std::vector<int> &L, const std::vector<int> &color) {
    ++cnt;

    // cout << "Clique: ";
    // for (int i = 0; i < s; ++i) cout << currentClique[i] + 1 << ' '; cout << endl;
    // print(L, "L: ", 1);
    // print(color, "color: ");

    std::vector<int> newL, col, proned;

    for (int i = len(L) - 1; i >= 0 && (color[i] == -1 || (s + color[i] > len(currentMaxClique))); --i) {
        if (color[i] == -1) {
            // ++cnt1;
            proned.push_back(L[i]);
            continue;
        }

        int u = L[i];

        currentClique[s] = u;
        
        // update max clique
        if (s + 1 > len(currentMaxClique)) {
            currentMaxClique.assign(s + 1, 0);
            for (int j = 0; j < s + 1; ++j)
                currentMaxClique[j] = currentClique[j];
        }

        // calculate new candidate set

        newL.clear(), col.clear(); 
        for (int j = 0; j < i; ++j) if (G[u][L[j]]) newL.push_back(L[j]);
        for (int v : proned) if (G[u][v]) newL.push_back(v);

        if (len(newL) == 0) continue;

        col.assign(len(newL), 0);
        calcColor(newL, col, len(currentMaxClique) - (s + 1) + 1, s < 4);
        REFMC(s + 1, newL, col);
    }
}

inline bool tension(int &a, const int &b) {
    return b <= a ? a = b, true : false;
}

void BBMCX_BITSET::calcOrder(const std::vector<int> &L) {
    for (int u : L) deg[u] = 0;

    for (int i = 0; i < len(L); ++i)
        for (int j = 0; j < i; ++j)
            deg[L[i]] += G[L[i]][L[j]], deg[L[j]] += G[L[i]][L[j]];

    // smallest degree-last
    for (int i = 0; i < len(L); ++i) {
        int u = -1, mn = INT_MAX;
        for (int j = 0; j < len(L); ++j)
            if (tension(mn, deg[L[j]])) u = L[j];
        deg[u] = INT_MAX, newOrder[u] = len(L) - i - 1;
        for (int v : L)
            deg[v] -= G[u][v];
    }
}

void BBMCX_BITSET::calcColor(std::vector<int> &L, std::vector<int> &color, int k, bool reCalc) {
    static std::vector<int> U, V, F;

    U = L;

    if (reCalc) {
        calcOrder(L);
        std::sort(U.begin(), U.end(), [&](const int &i, const int &j) {
            return newOrder[i] < newOrder[j];
        });
    } else {
        std::sort(U.begin(), U.end(), [&](const int &i, const int &j) {
            return order[i] < order[j];
        });
    }

    for (int c = 0, cnt = 0; U.size(); ++c, U = V) {
        isForbidden[c] = false;
        in.set();
        V.clear(), C[c].clear(), Cb[c].reset();
        for (int j = 0; j < len(U); ++j) {
            int u = U[j];
            if (in[u]) {
                if (c + 1 < k || !reColorIC(u, k)) {
                    C[c].push_back(u), L[cnt] = u, color[cnt++] = c + 1;
                    Cb[c].set(u), in &= GbR[u];
                } else {
                    // successfully reColor
                    L[cnt] = u, color[cnt++] = -1;
                }
            } else V.push_back(u);
        }
    }
}

bool BBMCX_BITSET::reColorIC(int u, int k) {
    for (int c1 = 0; c1 < k - 1; ++c1) if (!isForbidden[c1]) {
        if ((Cb[c1] & Gb[u]).count() == 1) {
            int v = -1;
            for (int t : C[c1]) if (G[u][t]) {
                v = t;
                break;
            }
            for (int c2 = c1 + 1; c2 < k - 1; ++c2)
                if (!isForbidden[c2] && (Cb[c2] & Gb[u] & Gb[v]).none()) {
                    isForbidden[c1] = isForbidden[c2] = true;
                    return true;
                }
           for (int c2 = 0; c2 < c1; ++c2)
                if (!isForbidden[c2] && (Cb[c2] & Gb[u] & Gb[v]).none()) {
                    isForbidden[c1] = isForbidden[c2] = true;
                    return true;
                }            
        }
    }

    return false;
}
