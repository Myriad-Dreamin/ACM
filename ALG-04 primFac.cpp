#include <cstdio>
/*
#include <cmath>
ALG-03
*/
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
int main(){
	int g=299342;
	calprim2(g);
	sieve();
	calprim(g);
}
