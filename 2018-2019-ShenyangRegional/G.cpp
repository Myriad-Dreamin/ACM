#include <cstdio>
#include <utility>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
vector<pair<int,int> > dis[10000005],lst;
void init()
{
	for(int i=0;i<=6000;i++){
		for(int j=i;j<=6000;j++){
			long long t=(long long)i*i+(long long)j*j;
			if(t<=10000000){
				dis[t].push_back({i,j});
			}else break;
		}
	}
}
long long X[6006][6006];
int main(){
	init();
	int T,n,m;long long res;
	scanf("%d",&T);
	for(int ttt=1;ttt<=T;ttt++){
		for(auto P:lst){X[P.first][P.second]=0;}
			lst.clear();
		res=0;
		scanf("%d%d",&n,&m);
		printf("Case #%d:\n",ttt);
		for(int i=1;i<=n;i++){
			int x,y,w;
			scanf("%d%d%d",&x,&y,&w);
			X[x][y]=w;
			lst.push_back({x,y});
		}
		for(int i=1;i<=m;i++){
			int o;
			scanf("%d",&o);
			switch(o){
				case 1:{
					int x,y,w;
					scanf("%d%d%d",&x,&y,&w);
					x=(x+res)%6000+1;
					y=(y+res)%6000+1;
					X[x][y]=w;
					lst.push_back({x,y});
					break;
				}
				case 2:{
					int x,y;
					scanf("%d%d",&x,&y);
					x=(x+res)%6000+1;
					y=(y+res)%6000+1;
					X[x][y]=0;
					break;
				}
				case 3:{
					int x,y,k,w;
					scanf("%d%d%d%d",&x,&y,&k,&w);
					x=(x+res)%6000+1;
					y=(y+res)%6000+1;
					int s,t;
					set<pair<int,int> > S;
					for(auto P:dis[k]){
						for(int u=-1;u<=1;u+=2){
							for(int v=-1;v<=1;v+=2){
								s=x+u*P.first;t=y+v*P.second;
								if(0<=s&&s<=6000&&0<=t&&t<=6000){
									S.insert({s,t});
								}
							}
						}
						swap(P.first,P.second);
						for(int u=-1;u<=1;u+=2){
							for(int v=-1;v<=1;v+=2){
								s=x+u*P.first;t=y+v*P.second;
								if(0<=s&&s<=6000&&0<=t&&t<=6000){
									S.insert({s,t});
								}
							}
						}
					}
					for(auto P:S){
						if(X[P.first][P.second])X[P.first][P.second]+=w;
					}
					break;
				}
				case 4:{
					int x,y,k;
					scanf("%d%d%d",&x,&y,&k);
					x=(x+res)%6000+1;
					y=(y+res)%6000+1;
					int s,t;
					res=0;
					set<pair<int,int> > S;
					for(auto P:dis[k]){
						for(int u=-1;u<=1;u+=2){
							for(int v=-1;v<=1;v+=2){
								s=x+u*P.first;t=y+v*P.second;
								if(0<=s&&s<=6000&&0<=t&&t<=6000){
									S.insert({s,t});
								}
							}
						}
						swap(P.first,P.second);
						for(int u=-1;u<=1;u+=2){
							for(int v=-1;v<=1;v+=2){
								s=x+u*P.first;t=y+v*P.second;
								if(0<=s&&s<=6000&&0<=t&&t<=6000){
									S.insert({s,t});
								}
							}
						}
					}
					for(auto P:S){
						if(X[P.first][P.second])res+=X[P.first][P.second];
					}
					printf("%lld\n",res);
					break;
				}
			}
		}
	}
}