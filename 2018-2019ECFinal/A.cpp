#include <cstdio>
const long long mod=1e9+7;
long long qp(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1)res=res*a%mod;
		b>>=1; a=a*a%mod;
	}
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	for(int ttt=1;ttt<=T;ttt++){
		long long n,k;
		scanf("%lld%lld",&n,&k);
		if(k>n){
			printf("Case #%d: 0\n",ttt);
			continue ;
		}
		long long res=qp(2, n),res2=1,res3=1;
		for(int i=1;i<k;i++){
			res3=(res3*(n-i+1)%mod)*qp(i,mod-2)%mod;
			res2+=res3;
			res2%=mod;
		}
		printf("Case #%d: %lld\n",ttt, (res-res2+mod)%mod);
	}
}
/*
31 1
30 1
29 1
28 1
16 1
 */