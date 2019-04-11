#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int head[10005],mal=1;
struct edge{
	int nx,to;
}e[40005];
void addedge(int u,int v){
	e[mal].to=v;e[mal].nx=head[u];head[u]=mal++;
}
int siz[10005],res,ress,n,m;
void dfs(int u,int f){
	siz[u]++;
	vector<int> af;
	int ans=0,sov=n-1;
	for(int i=head[u];i;i=e[i].nx){
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		sov-=siz[v];
		ans+=siz[v]*sov;
		af.push_back(siz[v]);
	}
	//printf("[%d]=%d, %d, %d\nsiz:\n",u,siz[u], n,ans);
	af.push_back(n-siz[u]);
	sort(af.begin(),af.end());
	// for(auto xx:af){
	// 	printf("%d ",xx);
	// }
	// puts("");
	if(ans>res){
		res=ans;
		ress=0;
		int tmp=af.back();
		af.pop_back();
		af.back()+=tmp;
		sov=n-1;
		for(auto xx:af){
			//printf("%d ", xx);
			sov-=xx;
			ress+=xx*sov;
		}
		//puts("");
	}
}
int main(){
	scanf("%d",&m);n=m+1;
	int u,v;res=0;ress=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		addedge(u+1,v+1);
		addedge(v+1,u+1);
	}
	dfs(1,0);
	printf("%d %d\n",res,ress);
}
/*
3
0 1
0 2
0 3
 */