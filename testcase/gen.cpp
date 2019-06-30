#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MAXN = 200;

bool G[MAXN][MAXN];

int main(int argc, char **argv) {
    srand(time(NULL));
    int N = atoi(argv[1]);
    for (int i = 0; i < N * 5; ++i) {
        int u = rand() % N;
        int v = rand() % N;
        G[u][v] = true;
    }

    int cnt = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < i; ++j)
            if (!G[i][j]) cnt++;
    
    cout << "p " << N << ' ' << cnt << endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < i; ++j)
            if (!G[i][j])
                cout << "e " << i + 1 << ' ' << j + 1 << endl;

    return 0;
}