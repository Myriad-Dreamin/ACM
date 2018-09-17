
//参数N,M略
//idx:序列编号
//dfn   :tree->array
//revdfn:array->tree
//dep:顶点深度
//lg:lg[0]=-1,lg[x]=floor(log2(x))

//init(){mal=1;idx=0;其他和DS-01一模一样.}

//dfs(
//  int u,int f
//  子树,子树根的父亲
//):dfs(root,虚拟根(必须在dep[]值域内)).

//LCA(
//  int u,int v
//  两个顶点
//):返回u,v的最近公共祖先.
//ST():直接调用

/*
#include <algorithm>
#include <cstring>
 */
const int N=500005,M=1000005,lgN=1;

/*
DS-01
 */

int idx;
int fa[lgN+1][M+5],dfn[M+5],revdfn[N+5],
dep[N+5],lg[M+5],mxlg=0;
inline void init(){
    mal=1;idx=0;
    memset(head,0,sizeof(head));
}
void dfs(int u,int f){
    dfn[++idx]=u;revdfn[u]=idx;
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=e[i].nx){
        int v=e[i].to;
        if(v!=f){
            dfs(v,u);
            dfn[++idx]=u;
        }
    }
}
void ST(){
    lg[0]=-1;
    for(int i=mxlg+1;i<=idx;i++)lg[i]=lg[i>>1]+1;
    if(mxlg<idx)mxlg=idx;
    for(int i=1;i<=idx;i++){
        fa[0][i]=dfn[i];
    }
    int ni=lg[idx],nj,tmp;
    for (int i=1;i<=ni;++i)
    {
        nj=idx+1-(1<<i);
        tmp=1<<(i-1);
        for (int j=1;j<=nj;++j){
            int u=fa[i-1][j],v=fa[i-1][j+tmp];
            fa[i][j]=dep[u]<dep[v]?u:v;
        }
    }
}
int LCA(int l,int r){
    l=revdfn[l];r=revdfn[r];
    if (l>r)swap(l,r);
    int k=lg[r-l+1];
    int u=fa[k][l],v=fa[k][r-(1<<k)+1];
    return dep[u]<dep[v]?u:v;
}
int main(){
    int n,m,s,u,v;
    init();
    n=READ();m=READ();s=READ();
    for(int i=1;i<n;i++){
        u=READ();v=READ();
        addedge(u,v);addedge(v,u);
    }
    dfs(s,0);ST();
    while(m--){
        u=READ();v=READ();
        printf("%d\n",LCA(u,v));
    }
}
