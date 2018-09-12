//参数
//N:主动匹配数(第一维)
//M:受动匹配数(第二维)
//KMtype:边权数据类型
//INF:根据边权改变INF..

//初始化
//init(
//      int n,int m
//      第一维,第二维
//)

//调用
//KMtomin(
//      int n,int m
//      第一维,第二维
//)

//加边
//注意有重边时：
//love[u][v]=min(love[u][v],w)


/*
#include <algorithm>
 */
typedef int KMtype;
const int N=,M=;
const int INF=0x3f3f3f3f;
//const long long INF=0x3f3f3f3f3f3f3f3fLL;
KMtype love[N][M];
KMtype EB[N],EG[M];
KMtype match[M],maymatch[M];
KMtype slave[M];bool used[M];
inline void init(int n,int m){
    fill(match,match+1+m,0);
    fill(EB,EB+1+n,0);fill(EG,EG+1+m,0);
    fill(used,used+1+m,0);
    for(int i=0;i<=n;i++)fill(love[i],love[i]+1+m,INF);
}
KMtype KMtomin(int n,int m){
    for(int i=1;i<=n;i++){
        match[0]=i;
        int j0=0,j1;
        fill(slave,slave+1+m,INF);
        fill(used,used+1+m,0);
        do{
            used[j0]=1;
            int i0=match[j0];KMtype dgap=INF;
            for(int j=1;j<=m;j++){
                if(!used[j]){
                    KMtype gap=love[i0][j]-EB[i0]-EG[j];
                    if(gap<slave[j])slave[j]=gap,maymatch[j]=j0;
                    if(slave[j]<dgap)dgap=slave[j],j1=j;
                }
            }
            for(int j=0;j<=m;j++){
                if(used[j])EB[match[j]]+=dgap,EG[j]-=dgap;
                else slave[j]-=dgap;
            }
            j0=j1;
            if(-EG[0]>=INF)return -1;
        }while(match[j0]);
        do{match[j0]=match[j1=maymatch[j0]];}while((j0=j1));
    }
    return EG[0];
}