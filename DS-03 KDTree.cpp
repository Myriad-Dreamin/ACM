#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//N:预估总结点数
//Dim:维数
//Point.x[]:各维的值
//dis(
//  Point &x,Point &y
//  两点x,y
//):求两点间的距离(我写了曼哈顿距离..)

//eva(
//  int rt,Point &b
//  子树rt,点b
//):求b在子树rt上的估价:(到边界曼哈顿距离..)

//insert(
//  int &rt,Point &b,int d
//  子树rt,点b,深度d
//):插入点b,注意入口的d需要保持一致,因为D划分是依赖d参数的

//build(
//  int &rt,int l,int r,int d
//  子树rt,区间[l,r],深度d
//):递归构造kd树,注意入口的d需要保持一致,因为D划分是依赖d参数的

//query(
//  int &rt,Point &b,int d
//  子树rt,点b,深度d
//):询问点b,注意入口的d需要保持一致,因为D划分是依赖d参数的

/*
#include <algorithm>
 */
const int N=,Dim=;
const int INF=0x7fffffff;
const long long LNF=0x7fffffffffffffffLL;
struct Point{
    int x[Dim];
    bool operator==(const Point &b)const{
        //Dim=2这样快一点
        //return b.x[0]==x[0]&&b.x[1]==x[1];
        for(int i=0;i<Dim;i++){
            if(x[i]!=b.x[i])return 0;
        }
        return 1;
    }
}P[N],chs;
inline int dis(Point &x,Point &y){
    return abs(x.x[0]-y.x[0])+abs(x.x[1]-y.x[1]);
}
struct node{
    int l,r,ch[Dim],mx[Dim],mi[Dim];Point p;
}kdt[N<<1];

inline int eva(int rt,Point &b){
    if(!rt)return INF;
    int res=0;
    for(int i=0;i<Dim;i++){
        if(b.x[i]>kdt[rt].mx[i])res+=b.x[i]-kdt[rt].mx[i];
        if(b.x[i]<kdt[rt].mi[i])res+=kdt[rt].mi[i]-b.x[i];
    }
    return res;
}
int mal=0,cur;
inline bool cmp(Point x,Point y){
    return x.x[cur]<y.x[cur];
}
inline int newnode(Point &b){
    mal++;
    kdt[mal].l=kdt[mal].r=kdt[mal].ch[0]=kdt[mal].ch[1]=0;
    kdt[mal].mx[0]=kdt[mal].mi[0]=b.x[0];
    kdt[mal].mx[1]=kdt[mal].mi[1]=b.x[1];
    kdt[mal].p=b;
    return mal;
}
inline void pushup(int rt){
    if(kdt[rt].l){
        int l=kdt[rt].l;
        for(int i=0;i<Dim;i++){
            if(kdt[rt].mx[i]<kdt[l].mx[i])kdt[rt].mx[i]=kdt[l].mx[i];
            if(kdt[rt].mi[i]>kdt[l].mi[i])kdt[rt].mi[i]=kdt[l].mi[i];
        }
    }
    if(kdt[rt].r){
        int r=kdt[rt].r;
        for(int i=0;i<Dim;i++){
            if(kdt[rt].mx[i]<kdt[r].mx[i])kdt[rt].mx[i]=kdt[r].mx[i];
            if(kdt[rt].mi[i]>kdt[r].mi[i])kdt[rt].mi[i]=kdt[r].mi[i];
        }
    }
}
void insert(int &rt,Point &b,int d){
    if(!rt){
        rt=newnode(b);
        return ;
    }
    if(kdt[rt].p==b)return ;
    if(b.x[d]<kdt[rt].p.x[d]){
        if(++d>=Dim)d-=Dim;
        insert(kdt[rt].l,b,d);
    }else{
        if(++d>=Dim)d-=Dim;
        insert(kdt[rt].r,b,d);
    }
    pushup(rt);
}
void build(int &rt,int l,int r,int d){
    //printf("~~%d %d\n",l,r);
    if(l>=r){
        if(l==r)rt=newnode(P[l]);
        return ;
    }
    int m=(l+r)>>1;  cur=d;
    nth_element(P+l,P+m,P+r+1,cmp);
    rt=newnode(P[m]);
    if(++d>=Dim)d-=Dim;
    build(kdt[rt].l,l,m-1,d);
    build(kdt[rt].r,m+1,r,d);
    pushup(rt);
}
int res;
void query(int rt,Point &b,int d){
    if(!rt)return ;
    res=min(res,dis(kdt[rt].p,b));
    if(!kdt[rt].l&&!kdt[rt].r)return ;
    int evaa=eva(kdt[rt].l,b),evab=eva(kdt[rt].r,b);

    if(++d>=Dim)d-=Dim;
    if(evaa<evab){
        if(res>evaa)query(kdt[rt].l,b,d);
        if(res>evab)query(kdt[rt].r,b,d);
    }else{
        if(res>evab)query(kdt[rt].r,b,d);
        if(res>evaa)query(kdt[rt].l,b,d);
    }
}
int main(){
    int n,m,root=0,wit;mal=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&P[i].x[0],&P[i].x[1]);
    }
    build(root,1,n,1);
    while(m--){
        scanf("%d%d%d",&wit,&chs.x[0],&chs.x[1]);wit--;
        if(wit){
            res=INF;query(root,chs,1);
            printf("%d\n",res);
        }else {
            insert(root,chs,1);
        }
    }
}