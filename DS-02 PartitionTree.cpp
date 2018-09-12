//sorted:把数组所有数排序后的数组
//val:lgN层划分数组
//toleft:记录当前前缀有多少数字到了左子树
//sum:记录当前前缀和

//build(
//  int l,int r,int d
//  [l,r]区间,深度
//)

/*
#include <algorithm>
 */
const int N=100010,lgN=22;
int sorted[N],val[lgN][N];
int toleft[lgN][N];
long long sum[lgN][N];

void build(int l,int r,int d){
    if(l==r)return ;
    int m=(l+r)>>1;
    int s=m-l+1;
    for(int i=l;i<=r;i++){
        if(val[d][i]<sorted[m]){
            s--;
        }
    }
    int lp=l,rp=m+1;
    for(int i=l;i<=r;i++){
        if(i==l){
            sum[d][i]=toleft[d][i]=0;
        }else{
            toleft[d][i]=toleft[d][i-1];
            sum[d][i]=sum[d][i-1];
        }
        if(val[d][i]<sorted[m]){
            toleft[d][i]++;
            val[d+1][lp++]=val[d][i];
            sum[d][i]+=val[d][i];
        }else if(val[d][i]>sorted[m]){
            val[d+1][rp++]=val[d][i];
        }else{
            if(s){
                s--;
                toleft[d][i]++;
                val[d+1][lp++]=val[d][i];
                sum[d][i]+=val[d][i];
            }else{
                val[d+1][rp++]=val[d][i];
            }
        }
    }
    build(l  ,m,d+1);
    build(m+1,r,d+1);
}

//使用示例
//求[l,r]中 sum{i=l...r}|a_i-x|的最大值
long long lsum,rsum;
int lnum,rnum;
int query(int a,int b,int k,int l,int r,int d){
    if(a==b)return val[d][a];
    int m=(l+r)>>1;
    int s,ss;long long sss;
    if(a==l){
        s=toleft[d][b];
        ss=0;
        sss=sum[d][b];
    }else{
        s=toleft[d][b]-toleft[d][a-1];
        ss=toleft[d][a-1];
        sss=sum[d][b]-sum[d][a-1];
    }
    if(s>=k){
        a=l+ss;
        b=l+ss+s-1;
        return query(a,b,k,l,m,d+1);
    }else{
        lnum+=s;
        lsum+=sss;
        a=m+1+a-l-ss;
        b=m+1+b-l-toleft[d][b];
        return query(a,b,k-s,m+1,r,d+1);
    }
}
long long s[N];
int main(){
    int T,n,m,x,y;
    scanf("%d",&T);
    for(int ttt=1;ttt<=T;ttt++){
        printf("Case #%d:\n",ttt);
        scanf("%d",&n);
        s[0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&sorted[i]);
            val[0][i]=sorted[i];
            s[i]=s[i-1]+sorted[i];
        }
        sort(sorted+1,sorted+1+n);
        build(1,n,0);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&x,&y);
            x++;y++;
            lsum=lnum=0;
            int ave=query(x,y,(y-x+2)>>1,1,n,0);
            rnum=y-x+1-lnum;
            rsum=s[y]-s[x-1]-lsum;
            printf("%I64d\n",rsum-lsum+(long long)(lnum-rnum)*ave);
        }
        puts("");
    }
}