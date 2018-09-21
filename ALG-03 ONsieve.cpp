#include <cstdio>
#include <cmath>
using namespace std;



//坑点1:筛到大于N的第一个质数一般不容易错,大于N的第一个质数<N+lgN
//坑点2:i*prim[j]会>long long
//坑点3:N/lgN是渐进的,当N比较大的时候误差比较小
/*
#include <cmath>
 */
const int N=10000000,lgN=log2(N),uplimN=N+lgN+1;
bool np[uplimN+5];
int prim[uplimN/(lgN-10)+5],psiz=0;
void sieve(){
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
    //printf("\n%d %d\n",psiz,uplimN/(lgN-10)+5);
}
int main(){
    sieve();
}
