<<<<<<< HEAD
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
=======
#include<cstdio>
#include<cstdlib>
bool e[1000][1000];
int main(){
    int n=30,m=0;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if(rand()%4<=2)e[i][j]=true,++m;
        }
    }
    printf("p edge %d %d\n", n, m);
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if(e[i][j])printf("e %d %d\n",i,j);
        }
>>>>>>> f62743e95535f8187f7bdb5ba5e0b030662eac57
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