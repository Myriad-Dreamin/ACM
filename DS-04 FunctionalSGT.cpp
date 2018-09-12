//参数
//N:主席树节点数
//M:值域[1,M]

//命名
//root[]:历史根编号
//rnk[k]:第k个数是rnk[k]
//rnkcnt:有k个不同的数(离散化)
//rtcnt:最新根编号
//sz:最新未利用结点编号

//node{
//  int l,int r,int sum
//  左子树编号,右子树编号,子树规模
//}

//build,update,query,kth:不会的问纸夜,这个太多变了,需要当场编= =!!
/*
#include <algorithm>
 */
const int N=100005,lgN=20,M=220000;
struct Que{int t;int l,r,x;}Q[M];
int root[N],rnk[M],rnkcnt,sz,rtcnt;
struct node{int l,r,sum;}sgt[N*lgN];
void build(int &rt,int l,int r){
    rt=++sz;
    sgt[rt].l=sgt[rt].r=sgt[rt].sum=0;
    if(l==r)return ;
    int m=(l+r)>>1;
    build(sgt[rt].l,l,m);build(sgt[rt].r,m+1,r);
}
void update(int &rt,int l,int r,int x,int last){
    rt=++sz;sgt[rt]=sgt[last];sgt[rt].sum++;
    if(l==r)return ;
    int m=(l+r)>>1;
    if(x<=m)update(sgt[rt].l,l,m,x,sgt[last].l);
    else  update(sgt[rt].r,m+1,r,x,sgt[last].r);
}
int query(int l,int r,int lrt,int rrt,int k){
    if(l==r)return l;
    int lnum=sgt[sgt[rrt].l].sum-sgt[sgt[lrt].l].sum;
    int m=(l+r)>>1;
    if(k<=lnum)return query(l,m,sgt[lrt].l,sgt[rrt].l,k);
    return query(m+1,r,sgt[lrt].r,sgt[rrt].r,k-lnum);
}
int kth(int l,int r,int rt,int x){
    if(l==r)return 0;
    int m=(l+r)>>1;
    if(m<=x)return sgt[sgt[rt].l].sum+kth(m+1,r,sgt[rt].r,x);
    return kth(l,m,sgt[rt].l,x);
}
char cr[10];
int main(){
    int n,cas=0;long long res1,res2,res3;
    while(~scanf("%d",&n)){res1=res2=res3=0;
        rnkcnt=0;rtcnt=0;
        for(int i=1;i<=n;i++){
            scanf("%s",cr);Q[i].t=cr[6]-'0';
            switch(Q[i].t){
                case 1:{
                    scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].x);
                    break;
                }
                default:{
                    scanf("%d",&Q[i].x);
                    if(Q[i].t==-48)rnk[++rnkcnt]=Q[i].x;
                    break;
                }
            }
        }
        sort(rnk+1,rnk+1+rnkcnt);
        rnkcnt=unique(rnk+1,rnk+1+rnkcnt)-rnk-1;
        sz=0;root[0]=0;
        build(root[0],1,rnkcnt);
        for(int i=1;i<=n;i++){
            switch(Q[i].t){
                case -48:{
                    rtcnt++;
                    update(root[rtcnt],1,rnkcnt,lower_bound(rnk+1,rnk+1+rnkcnt,Q[i].x)-rnk,root[rtcnt-1]);
                    break;
                }
                case 1:{
                    res1+=rnk[query(1,rnkcnt,root[Q[i].l-1],root[Q[i].r],Q[i].x)];
                    break;
                }
                case 2:{
                    res2+=kth(1,rnkcnt,root[rtcnt],lower_bound(rnk+1,rnk+1+rnkcnt,Q[i].x)-rnk);
                    break;
                }
                case 3:{
                    res3+=rnk[query(1,rnkcnt,root[0],root[rtcnt],Q[i].x)];
                    break;
                }
            }
        }
        printf("Case %d:\n%I64d\n%I64d\n%I64d\n",++cas,res1,res2,res3);
    }
}
/*
10
Insert 1
Insert 4
Insert 2
Insert 5
Insert 6
Query_1 1 5 1
Query_1 1 5 2
Query_1 1 5 3
Query_1 1 5 4
Query_1 1 5 5
 */