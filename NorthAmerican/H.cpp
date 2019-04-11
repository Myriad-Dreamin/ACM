#include <cstdio>
char mp[105][105];
int mmp[105][105];
int vecx[]={
	1,1,1,-1,-1,-1,0,0
};
int vecy[]={
	1,0,-1,1,0,-1,1,-1
};
int vexx[]={
	1,-1,0,0
};
int vexy[]={
	0,0,1,-1
};
void clrs(int x,int y){
	if(mp[x][y]!='.')return ;
	mp[x][y]=' ';
	for(int i=0;i<4;i++){
		int nx=x+vexx[i],ny=y+vexy[i];
		clrs(nx,ny);
	}
}
void clrs(int x,int y,int d){
	if(mmp[x][y]!='.')return ;
	mmp[x][y]=d;
	for(int i=0;i<4;i++){
		int nx=x+vexx[i],ny=y+vexy[i];
		clrs(nx,ny,d);
	}
}
int col[10005];
int main(){
	int m,n;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			// ##
			// #
			if(mp[i][j]=='#'&&mp[i][j+1]=='#'&&mp[i+1][j]=='#'){
				cnt++;
				mp[i][j]=mp[i][j+1]=mp[i+1][j]=' ';
			}
			// ##
			//  #
			if(mp[i][j]=='#'&&mp[i][j-1]=='#'&&mp[i+1][j]=='#'){
				cnt++;
				mp[i][j]=mp[i][j-1]=mp[i+1][j]=' ';
			}

			// #
			// ##
			if(mp[i][j]=='#'&&mp[i][j+1]=='#'&&mp[i-1][j]=='#'){
				cnt++;
				mp[i][j]=mp[i][j+1]=mp[i-1][j]=' ';
			}

			//  #
			// ##
			if(mp[i][j]=='#'&&mp[i][j-1]=='#'&&mp[i-1][j]=='#'){
				cnt++;
				mp[i][j]=mp[i][j-1]=mp[i-1][j]=' ';
			}
		}
	}
	for(int i=1;i<=n;i++){
		clrs(1,i);
		clrs(i,1);
		clrs(n,i);
		clrs(i,m);
		for(int j=1;j<=m;j++)mmp[i][j]=mp[i][j];
	}
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=m;j++){
	// 		printf("%d ",mmp[i][j]);
	// 	}
	// 	puts("");
	// }
	int t=199;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			clrs(i,j,++t);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!col[mmp[i][j]]){
				col[mmp[i][j]]++;
				if(mmp[i][j]>150){
					cnt++;
				}
			}
		}
	}
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=m;j++){
	// 		printf("%d ",mmp[i][j]);
	// 	}
	// 	puts("");
	// }
	printf("%d\n",cnt);
}

/*
12 12
.##########.
#..........#
#..#...##..#
#.##..#..#.#
#......#.#.#
#....#..#..#
#...#.#....#
#..#...#...#
.#..#.#....#
#....#.....#
#.........#.
.#########..

4 6
.#....
#.#.#.
.#.#.#
....#.
 */