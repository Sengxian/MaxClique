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
    }
    return 0;
}