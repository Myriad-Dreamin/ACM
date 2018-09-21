#include <cstdio>
#include <cmath>
using namespace std;
const int N=10000000,lgN=log2(N),uplimN=N+lgN+1;
bool np[uplimN+5];
int prim[uplimN/(lgN-10)+5],psiz=0;
int main(){
    for(int i=2;i<=uplimN;i++){
        if(!np[i]){
            prim[++psiz]=i;
            //printf("%d ",i);
        }
        for(int j=1;j<=psiz;j++){
            if(((long long)i*prim[j])>uplimN)break;
            np[i*prim[j]]=1;
            if(i%prim[j]==0)break;
        }
    }
    printf("\n%d %d\n",psiz,uplimN/(lgN-10)+5);
}