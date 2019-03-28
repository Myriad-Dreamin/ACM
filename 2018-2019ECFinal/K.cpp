#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
	int T,n;
	scanf("%d",&T);
	int S,B;
	for(int ttt=1;ttt<=T;ttt++){
		scanf("%d",&n);
		int res=0,mxB=0;
		for(int i=0;i<=n;i++)scanf("%d",&S),res+=S;
		for(int i=0;i<n;i++){
			scanf("%d%d",&S,&B);
			mxB=max(mxB,B);
		}
		printf("Case #%d: %d\n",ttt,res+mxB);
	}
}