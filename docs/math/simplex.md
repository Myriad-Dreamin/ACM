```c++
//单纯形:最大松弛
//参数:
//INF:预估最大值
//A:行向量为一组约束


//调用simplex得到答案

//例题用了对偶原理,所以约束按列填写，但是求值确实还是按行的。

/*
#include <cmath>
 */
const double eps=1e-8,INF=1e15;
inline int sgn(double x){if(fabs(x)<eps)return 0;return x<0?-1:1;}
double A[10100][1010];
int que[1010],m,n;
void pivot(int l,int e){
	double b=A[l][e];A[l][e]=1;
	int qtop=0;  for(int j=0;j<=n;j++)if(sgn(A[l][j]/=b))que[++qtop]=j;
	for(int i=0;i<=m;i++){
		if(i!=l&&sgn(A[i][e])){
			b=A[i][e];A[i][e]=0;
			for(int j=1;j<=qtop;j++)A[i][que[j]]-=b*A[l][que[j]];
		}
	}
}
double simplex(){
	for(int l,e;;pivot(l,e)){
		double lim=INF;
		for(e=1;e<=n&&A[0][e]<eps;e++);
		if(e==n+1)return A[0][0];
		for(int i=1;i<=m;i++){
			if(A[i][e]>eps&&A[i][0]/A[i][e]<lim)lim=A[l=i][0]/A[i][e];
		}
		if(sgn(lim-INF)==0)return INF;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);A[0][i]=x;
	}
	int k,u,v;
	for(int i=1;i<=m;i++){
		scanf("%d",&k);
		while(k--){
			scanf("%d%d",&u,&v);
			for(int j=u;j<=v;j++)A[i][j]=1;
		}
		scanf("%d",&x);A[i][0]=x;
	}
	double res=simplex();
	printf("%d\n",int(-res+0.5));
}
```

