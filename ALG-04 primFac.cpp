#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;
inline int rand(){
    static int seed = 2333;
    return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
}
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
    int psiz2=0;
    printf("%d %d %d\n",psiz,psiz2,uplimN/(lgN-10)+5);
}
int Fac2[15],Ft2=0;
void calprim2(int n){
	Ft2=0;
	int sqrtn=sqrt(n+1);
	for(int i=2;i<=sqrtn;i++){
		if(n%i==0){
			Fac2[++Ft2]=i;
			while(n%i==0)n/=i;
		}
	}
	if(n>1)Fac2[++Ft2]=n;
	// for(int i=1;i<=Ft2;i++)printf("%d ",Fac2[i]);
	// puts("");
}
int Fac[15],Ft=0;
void calprim(int n){
	Ft=0;
	int sqrtn=sqrt(n+1);
	for(int i=1;prim[i]<=sqrtn;i++){
		if(n%prim[i]==0){
			Fac[++Ft]=prim[i];
			while(n%prim[i]==0)n/=prim[i];
		}
	}
	if(n>1)Fac[++Ft]=n;
	// for(int i=1;i<=Ft;i++)printf("%d ",Fac[i]);
	// puts("");
}
const int fflm=1e5;
int ff=1e5,test[fflm+5];
int main(){
	long tottime1=0,tottime2=0,tottime3=0;
	sieve();
	for(int i=1;i<=ff;i++)test[i]=rand()%N+1;
	//return 0;
	long beg=clock();
	for(int i=1;i<=ff;i++){
		calprim2(test[i]);
	}
	tottime1=clock()-beg;
	beg=clock();
	for(int i=1;i<=ff;i++){
		calprim(test[i]);
	}
	tottime2=clock()-beg;
	beg=clock();
	int n;
	for(int i=1;i<=ff;i++){
		Ft=0;
		n=test[i];
		for (int j = 1; n!=1&&j<=psiz; j++) {
			if (n%prim[j] == 0) {
				int p = prim[j];
				while (n%prim[j] == 0) {
					Fac[++Ft]=prim[j];
					p += prim[j];
					n /= prim[j];
				}
			}
		}
		if (n > 1)Fac[++Ft]=n;
		// for(int i=1;i<=Ft;i++)printf("%d ",Fac[i]);
		// puts("");
	}
	tottime3=clock()-beg;
	printf("compare calprim2 %ldms calprim %ldms Rui-cal %ldms\n",tottime1,tottime2,tottime3);
}
/*
664580 0 769237
compare calprim2 780ms calprim 134ms Rui-cal 16964ms
 */