#include<cstdio>
#include<cstdlib>
int main(){
    int n=20;
    printf("p edge %d %d\n", n, n*(n-1)/2);
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            printf("e %d %d\n",i,j);
        }
    }
    return 0;
}