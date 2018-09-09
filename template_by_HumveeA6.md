# 模板 by HumveeA6

## 基础数学

### SG函数

说是小结，其实我并没有怎么弄懂QAQ，简单写写概念跟板子吧...

#### Sprague-Grundy函数

给定一个有向无环图和一个起始顶点上的一枚棋子，两名选手交替的将这枚棋子沿有向边进行移动，无法移动者判负。事实上，这个游戏可以认为是所有Impartial Combinatorial Games的抽象模型。也就是说，任何一个ICG都可以通过把每个局面看成一个顶点，对每个局面和它的子局面连一条有向边来抽象成这个“有向图游戏”。

**基本概念**

下面我们就在有向无环图的顶点上定义Sprague-Garundy函数。

首先定义$$mex$$(minimal excludant)运算，这是施加于一个集合的运算，表示最小的不属于这个集合的非负整数。例如$$mex[0,1,2,4]=3,mex[2,3,5]=0,mex[]=0$$。

对于一个给定的有向无环图，定义关于图的每个顶点的Sprague-Garundy函数$$g$$如下：$$g(x)=mex[ g(y) | y是x的后继 ]$$。

**SG函数的性质**

首先，所有的terminal position所对应的顶点，也就是没有出边的顶点，其SG值为0，因为它的后继集合是空集。
对于一个g(x)=0的顶点x，它的所有后继y都满足g(y)!=0。 
对于一个g(x)!=0的顶点，必定存在一个后继y满足g(y)=0。  

以上这三句话表明，顶点x所代表的postion是P-position当且仅当g(x)=0（跟P-positioin/N-position的定义的那三句话是完全对应的）。我们通过计算有向无环图的每个顶点的SG值，就可以对每种局面找到必胜策略了。

我们可以定义有向图游戏的和(Sum of Graph Games)：设G1、G2、……、Gn是n个有向图游戏，定义游戏G是G1、G2、……、Gn的和(Sum)，游戏G的移动规则是：任选一个子游戏Gi并移动上面的棋子。Sprague-Grundy Theorem就是：g(G)=g(G1)^g(G2)^...^g(Gn)。也就是说，游戏的和的SG函数值是它的所有子游戏的SG函数值的异或。

再考虑一个性质：任何一个ICG都可以抽象成一个有向图游戏。所以“SG函数”和“游戏的和”的概念就不是局限于有向图游戏。我们给每个ICG的每个position定义SG值，也可以定义n个ICG的和。所以说当我们面对由n个游戏组合成的一个游戏时，只需对于每个游戏找出求它的每个局面的SG值的方法，就可以把这些SG值全部看成Nim的石子堆，然后依照找Nim的必胜策略的方法来找这个游戏的必胜策略了！（Nim其实就是n个从一堆中拿石子的游戏求SG的变型，总SG=n个sg的异或）。

####模板

**1.把原游戏分解成多个独立的子游戏，则原游戏的SG函数值是它的所有子游戏的SG函数值的异或.**

即$$sg(G)=sg(G1)\oplus sg(G2)\oplus ...\oplus sg(Gn)$$。

**2.分别考虑没一个子游戏，计算其SG值。**

(1)可选步数为1~m的连续整数，直接取模即可，$$SG(x) = x \ mod\  (m+1)$$

(2)可选步数为任意步，$$SG(x) = x$$;
(3)可选步数为一系列不连续的数，用模板计算。

**模板1：打表**

```cpp
#include<bits/stdc++.h>
using namespace std;
//f[]：可以取走的石子个数
//sg[]:0~n的SG函数值
//Mex[]:mex{}
int f[N],sg[N],Mex[N];
void getSG(int n) 
{
    int i, j;
    memset(sg, 0, sizeof(sg));
    for (i = 1; i <= n; i++) {
        memset(Mex, 0, sizeof(Mex));
        for (j = 1; f[j] <= i; j++)
            Mex[sg[i - f[j]]] = 1;
        for (j = 0; j <= n; j++)    //求mes{}中未出现的最小的非负整数
        {
            if (Mex[j] == 0) {
                sg[i] = j;
                break;
            }
        }
    }
}

```



**模板2：dfs**

```cpp
//注意 S数组要按从小到大排序 SG函数要初始化为-1 对于每个集合只需初始化1遍
//n是集合s的大小 S[i]是定义的特殊取法规则的数组
int s[110],sg[10010],n;
int SG_dfs(int x)
{
    int i;
    if(sg[x]!=-1)
        return sg[x];
    bool vis[110];//bool数组一定要放在里面
    memset(vis,0,sizeof(vis));
    for(i=0;i<n;i++)
    {
        if(x>=s[i])
        {
            SG_dfs(x-s[i]);
            vis[sg[x-s[i]]]=1;
        }
    }
    int e;
    for(i=0;;i++)
        if(!vis[i])
        {
            e=i;
            break;
        }
    return sg[x]=e;
}
```



一般DFS只在打表解决不了的情况下用，首选打表预处理。

还有一种dfs，题目给出的不是移动次数，而是可以移动的操作，类似于给定一幅有向图，知道下一步有哪些操作是可选的（参见HDU1524）

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
vector<int>G[1005];
int sg[1005];
int dfs(int x)
{
    if(sg[x]!=-1)
        return sg[x];
    bool vis[1005]={false};
    for(int i=0;i<G[x].size();i++){
        vis[dfs(G[x][i])]=true;
    }
    for(int i=0;;i++)
        if(!vis[i])
            return sg[x]=i;
}
int main()
{
    int n,i,j,k,x,m;
    while(cin>>n){
        for(i=0;i<=1000;i++)G[i].clear();
        memset(sg,-1,sizeof(sg));
        for(i=0;i<n;i++){
            scanf("%d",&x);
            while(x--){
                scanf("%d",&j);
                G[i].push_back(j);//加边,下一步可以做的操作
            }
        }
        while(scanf("%d",&m)&&m){
            int ans=0;
            for(i=0;i<m;i++){
                scanf("%d",&j);
                if(sg[j]!=-1)
                    ans^=sg[j];
                else ans^=dfs(j);
            }
            if(ans)puts("WIN");
            else puts("LOSE");
        }
    }

    return 0;
}
```



**3.计算$$sg(G)=sg(G1)\oplus sg(G2)\oplus ...\oplus sg(Gn)$$，若$$sg(G)=0$$,即P-Position,即先手比败。



## 数据结构

### 线段树

#### 单点更新单点查询

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 200001;
int m, d, len = 0;
ll array1[maxn], t = 0, sum[maxn << 2];
void buildtree(int node, int begin, int end)
{
    if (begin == end) {
        sum[node] = array1[begin];
        return;
    }
    int m = (begin + end) >> 1;
    buildtree(node << 1, begin, m);
    buildtree(node << 1 | 1, m + 1, end);
    sum[node] = max(sum[node << 1], sum[node << 1 | 1]);
}
void update(int node, int ind, int change, int begin, int end)//node是根节点，一般为1，ind是更新的位置(该点的下标)，change是要将该点更换为的值，begin，end就是当前区间
{
    if (begin == end) {
        sum[node] = change;
        return;
    }
    int m = (begin + end) >> 1;
    if (ind <= m)
        update(node << 1, ind, change, begin, m);
    else
        update(node << 1 | 1, ind, change, m + 1, end);
    sum[node] = max(sum[node << 1], sum[node << 1 | 1]);
}
ll query(int node, int begin, int end, int left, int right)//begin，end是当前区间，left，right是需要查询的区间
{
    if (left <= begin&&right >= end)
        return sum[node];
    int m = (begin + end) >> 1;
    ll p1 = 0, p2 = 0;
    if (left <= m)
        p1 = query(node << 1, begin, m, left, right);
    if (right > m)
        p2 = query(node << 1 | 1, m + 1, end, left, right);
    return max(p1, p2);
}
```

#### 区间更新，区间求和

> 已知一个数列，您需要进行下面两种操作：
>
> 1.将某区间每一个数加上x
>
> 2.求出某区间每一个数的和（参见洛谷P3372)

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
int array1[maxn];
struct node1{
    ll sum,addmark;
}Node[maxn<<2];
void pushup(int node)
{
    Node[node].sum=Node[node<<1].sum+Node[node<<1|1].sum;
}
void buildtree(int node,int left,int right)
{
    Node[node].addmark=0;
    if(left==right){
        Node[node].sum=array1[left];return;
    }
    int m=(left+right)>>1;
    buildtree(node<<1,left,m);
    buildtree(node<<1|1,m+1,right);
    pushup(node);
}
void pushdown(int node,int left,int right)
{
    if(Node[node].addmark){
        int m=(left+right)>>1;
        Node[node<<1].addmark+=Node[node].addmark;
        Node[node<<1|1].addmark+=Node[node].addmark;
        Node[node<<1].sum+=(m-left+1)*Node[node].addmark;
        Node[node<<1|1].sum+=(right-m)*Node[node].addmark;
        Node[node].addmark=0;
    }
}
ll query(int node,int begin,int end,int left,int right)//begin,end当前区间，left，right查询区间
{
    if(left<=begin&&right>=end)
        return Node[node].sum;
    pushdown(node,begin,end);
    int m=(begin+end)>>1;//小心!!
    ll ans=0;
    if(left<=m)
        ans+=query(node<<1,begin,m,left,right);
    if(right>m)
        ans+=query(node<<1|1,m+1,end,left,right);
    return ans;
}
void update(int node,int add,int begin,int end,int left,int right)
{
    if(begin>=left&&end<=right){
        Node[node].sum+=(end-begin+1)*add;
        Node[node].addmark+=add;return;
    }
    int m=(begin+end)>>1;//小心!!
    pushdown(node,begin,end);
    if(left<=m)
        update(node<<1,add,begin,m,left,right);
    if(right>m)
        update(node<<1|1,add,m+1,end,left,right);
    pushup(node);
}
```



#### 区间双重更新，区间求和

> 题目可参见洛谷P3373 
> 已知一个数列，您需要进行下面三种操作：
>
> 1.将某区间每一个数乘上x
>
> 2.将某区间每一个数加上x
>
> 3.求出某区间每一个数的和

要特别注意不同lazytab之间的优先级关系

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn = 100010;
int array1[maxn], n, m, p;
struct node1 {//sum是区间值，add是加的记号，另一个是乘
    ll sum, add, mul;
}Node[maxn<<2];
void pushup(int node)
{
    Node[node].sum = (Node[node << 1].sum + Node[node << 1 | 1].sum)%p;
}
void buildtree(int node, int begin, int end)
{
    Node[node].add = 0; Node[node].mul = 1;
    if (begin == end) {
        Node[node].sum = array1[begin];
        return;
    }
    int m = (begin + end) >> 1;
    buildtree(node * 2, begin, m);
    buildtree(node * 2 + 1, m + 1, end);
    pushup(node);
}
void pushdown(int node,int process, int begin, int end)
{
    if (process == 1) {
        if (Node[node].mul != 1) {//process是1代表乘，是0代表加（下同）
            Node[node << 1].mul = Node[node].mul*Node[node << 1].mul%p;
            Node[node << 1 | 1].mul = Node[node].mul*Node[node << 1 | 1].mul%p;
            Node[node << 1].add = Node[node].mul*Node[node << 1].add%p;
            Node[node << 1 | 1].add = Node[node].mul*Node[node << 1 | 1].add%p;
            Node[node << 1].sum = Node[node].mul*Node[node << 1].sum%p;
            Node[node << 1 | 1].sum = Node[node].mul*Node[node << 1 | 1].sum%p;
            Node[node].mul = 1;
        }
    }
    else {
        if (Node[node].add) {
            int m = (begin + end) >> 1;
            Node[node << 1].add = (Node[node].add + Node[node << 1].add) % p;
            Node[node << 1 | 1].add = (Node[node << 1 | 1].add + Node[node].add) % p;
            Node[node << 1].sum = (Node[node << 1].sum + (m - begin + 1)*Node[node].add%p) % p;
            Node[node << 1 | 1].sum = (Node[node << 1 | 1].sum + (end - m)*Node[node].add%p) % p;
            Node[node].add = 0;
        }
    }
}
ll query(int node, int begin, int end, int left, int right)//begin，end当前区间，left，right查询区间
{
    if (left <= begin&&right >= end) {
        return Node[node].sum%p;
    }
    pushdown(node, 1, begin, end);//（先乘后加）
    pushdown(node, 0, begin, end);
    ll ans = 0;
    int m = (begin + end) >> 1;
    if (left <= m)
        ans = (ans+query(node * 2, begin, m, left, right))%p;
    if (right > m)
        ans = (ans + query(node * 2 + 1, m + 1, end, left, right))%p;
    return ans;
}
void update(int node, int process, int add, int begin, int end, int left, int right)
//begin，end当前区间，left，right为更新区间
{
    if (left <= begin&&right >= end) {
        if (process == 1) {
            Node[node].mul = Node[node].mul*add%p;
            Node[node].add = Node[node].add*add%p;
            Node[node].sum = Node[node].sum*add%p;
        }
        else {
            Node[node].sum = (Node[node].sum + add*(end-begin+1)%p) % p;
            Node[node].add = (Node[node].add + add) % p;

        }
        return;
    }
    int m = (begin + end) >> 1;
    pushdown(node, 1, begin, end);
    pushdown(node, 0, begin, end);
    if (left <= m)
        update(node * 2, process, add, begin, m, left, right);
    if (right > m)
        update(node * 2 + 1, process, add, m + 1, end, left, right);
    pushup(node);
}
```



### 树状数组

#### 单点更新，区间求和

前提是你需要区间和并且需要作出更改，否则直接前缀和即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int bit[maxn],n,m;
typedef long long ll;
ll sum(int i)
{
    ll s=0;
    while(i){
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n){
        bit[i]+=x;
        i+=i&-i;
    }
}
```



#### 区间修改，单点求值

> 引入一个叫做差分数组的东西，感觉思想有点像lazytab。区间[l,r]所有值+k改成”位置l加上k，位置r+1减去k”  查询的时候直接查询sum(x)就行；（参考题目：洛谷P3368）注意最后输出的时候还要加上原数组的值，因为现在树状数组里面保存的其实是各个数的加减情况。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn = 500050;
int a[maxn], c[maxn],n;//a是原始数组，c是差分数组
int sum(int i)//这两个函数与原始版的树状数组是一样的，只不过里面操作的是差分数组
{
    int s = 0;
    while (i) {
        s += c[i];
        i -= i&-i;
    }
    return s;
}
void add(int i, int x)
{
    while (i <= n) {
        c[i] += x;
        i += i&-i;
    }
}
```

### 并查集

最重要的事情是记得**初始化**！！！按秩合并一般没用但有时候数据很大的时候似乎也有些效果。

#### 按秩合并

```cpp
int find(int x)
{
    if (x == par[x])
        return x;
    else
        return par[x] = find(par[x]);//后面这一块不要漏了par[x]!!!否则就是不带路径压缩(有时候有用）
}
void unite(int x, int y)
{
    x = find(x); y = find(y);
    if (x == y)
        return;
    if (rank[x] < rank[y]) {
        par[x] = y;
    }
    else {
        par[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }
}
//一定要加上：
for(i=1;i<=n;i++){
   par[i]=i;
   }!!!!!!
```

#### 简化版

```cpp
int par[maxn];//记得初始化！！！
int find(int x)
{
    return par[x]==x?x:par[x]=find(par[x]);//后面这一块不要漏了par[x]!!!否则就是不带路径压缩
}
bool unite(int x,int y)
{
    x=find(x),y=find(y);
    if(x==y)return false;
    par[x]=y;
    return true;
}
```

### 单调栈（待完善）

> 单调栈是指一个栈内部的元素是具有严格单调性的一种数据结构，分为单调递增栈和单调递减栈。
>
> 单调栈有两个性质
>
> 1.满足从栈顶到栈底的元素具有严格的单调性
>
> 2.满足栈的后进先出特性越靠近栈底的元素越早进栈
>
> 元素进栈过程:
>
> 对于一个单调递增栈来说, 若当前进栈的元素为 a ,如果a < 栈顶元素则直接将a 进栈 ,如果 a >= 当前栈顶元素则不断将栈顶元素出栈直到满足 a < 栈顶元素



> 利用单调栈，可以找到从左/右遍历第一个比它小/大的元素的位置
>
> **总结：一个元素向左遍历的第一个比它小的数的位置就是将它插入单调栈时栈顶元素的值，若栈为空，则说明不存在这么一个数。然后将此元素的下标存入栈，就能类似迭代般地求解后面的元素**

### ST表

ST表就是一个用来解决rmq（区间最值）问题的算法. 
 **ST表不支持在线修改**
预处理时间复杂度$$O(nlogn)$$，查询时间$$O(1)$$

**算法详解（求最小值）：**

用$$mn[i][j]$$表示从$$i$$到$$i+2^j-1$$的最小值（长度显然为$$2^i$$）。 
任意一段的最小值显然等于min（前半段最小值，后半段最小值）。 
那么$$mn[i][j]$$如何用其他状态来继承呢？ 
$$i$$到$$i+2^j-1$$的长度为$$2^j$$，那么一半的长度就等于$$2^{j-1}$$。 
那么前半段的状态表示为$$mn[i][j-1]$$。 
后半段的长度也为$$2^{j-1}$$，起始位置为$$i+2^{(j-1)}$$。 
那么后半段的状态表示为$$mn[i+2^{j-1}][j-1]$$。 
所以： $mn[i][j]=min(mn[i][j-1],mn[i+2^{j-1}][j-1])$。

**模板**

注意修改数组大小！
(洛谷P3865)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int a[MAXN],dp[MAXN][50];//第二个括号内要根据最大数据范围改成2的幂次能大于最大的数据
//int Min(int x,int y)//有时候可以用于自定义一些特殊类型的比较
//{
//    return a[x]<=a[y]?x:y;
//}
void st_init(int n)//n为原始数组的长度
{
    for (int i = 1; i <= n; i++) dp[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            //dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int query(int l,int r)
{
    int k = log2(r - l + 1);
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
    //return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}
int main()
{
    int n,m,i,j,k;
    cin>>n>>m;
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    st_init(n);
    int l,r;
    while(m--){
        scanf("%d%d",&l,&r);
        printf("%dn",query(l,r));
    }

    return 0;
}
```



### 单调队列（待完善）

> 单调队列是指一个队列内部的元素具有严格单调性的一种数据结构，分为单调递增队列和单调递减队列。
>
> 单调队列满足两个性质
>
> 1.单调队列必须满足从队头到队尾的严格单调性。
>
> 2.排在队列前面的比排在队列后面的要先进队。
>
> 元素进队列的过程对于单调递增队列，对于一个元素a ，如果 a > 队尾元素， 那么直接将a扔进队列。 如果 a <= 队尾元素 ，则将队尾元素出队列 ，直到满足 a 大于队尾元素即可；



## 图论

### Floyd

> 因为每次是拿一个点出来考虑能否把别的路变短，所以k一定是最外层循环。以及要记得初始化为无穷大或无穷小。  可以通过检查是否有dis[i][i]<0来判定是否有负环存在

```cpp
int dis[105][105];
    memset(dis,0x7f,sizeof(dis));
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>dis[i][j];
    for(k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
```



### Dijkstra

#### 自定义结构体

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e5+5;
struct edge{
    int to,cost;
};
vector<edge>G[maxn];
struct d{//记录各种被松弛后的点
    int num,dis;
};
bool operator <(d a,d b)
{
    return a.dis>b.dis;
}
int main()
{
    int n,m,s,i,j,k;
    cin>>n>>m>>s;
    for(i=1;i<=m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        G[a].push_back(edge{b,c});
    }
    int dis[maxn];memset(dis,0x7f,sizeof(dis));dis[s]=0;
    priority_queue<d>que;
    que.push(d{s,0});
    while(!que.empty()){
        d e=que.top();que.pop();
        if(e.dis>dis[e.num])continue;//这里也可以利用一个额外的数组来保证每个点只被访
        //问一次，或者说最短距离已经确定的点不再被更改
        for(int i=0;i<G[e.num].size();i++){
            edge eg=G[e.num][i];
            if(dis[eg.to]>dis[e.num]+eg.cost){
                dis[eg.to]=dis[e.num]+eg.cost;
                que.push(d{eg.to,dis[eg.to]});
            }
        }
    }
    
    return 0;
}
```



#### using pair

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>
using namespace std;
const int maxn=1e5+5;
typedef struct {
    int to, cost;
}Edge;
vector<Edge>edge[maxn];
typedef pair<int, int>P;
priority_queue<P, vector<P>, greater<P> >q;//从小到大的优先队列
int book[maxn], dis[maxn];
int main(void)
{
    int n, m, s, i, j;

    scanf("%d %d %d", &n, &m, &s);
    fill(dis, dis + n+1, 2147483647); dis[s] = 0;
    for (i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Edge temp;
        temp.to = b; temp.cost = c;
        edge[a].push_back(temp);
    }
    P p; p.first = 0; p.second = s; q.push(p);
    while (!q.empty()) {
        P p = q.top(); q.pop();
        if (book[p.second] == 1) continue;
        book[p.second] = 1;
        for (i = 0; i < edge[p.second].size(); i++) {
            Edge temp = edge[p.second][i];
            if (dis[temp.to] > dis[p.second] + temp.cost) {
                dis[temp.to] = dis[p.second] + temp.cost;
                P p1; p1.first = dis[temp.to]; p1.second = temp.to;
                q.push(p1);
            }
        }
    }

    return 0;
}
```





### SPFA

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
struct edge{
    int to,cost;
};
vector<edge>G[maxn];
bool inque[maxn];
int main()
{
    int n,m,s,i,j,k;
    cin>>n>>m>>s;
    int dis[maxn];
    for(i=1;i<=n;i++)dis[i]=(1<<31)-1;
    dis[s]=0;
    for(i=1;i<=m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        G[a].push_back(edge{b,c});
    }
    queue<int>que;que.push(s);//inque[s]=true;
    while(!que.empty()){
        int t=que.front();que.pop();inque[t]=false;
        for(i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(dis[e.to]>dis[t]+e.cost){
                dis[e.to]=dis[t]+e.cost;
                if(!inque[e.to]){
                    que.push(e.to);inque[e.to]=true;
                }
            }
        }
    }

    return 0;
}
```



### Prim

> 算法跟Dijkstra很像 ，但是要特别注意两点：
>
> 1.最好使用一个额外的数组来保证每个点只被访问一次，否则的话应该保证在35行处使用e.dis>=dis[e.num]而不仅是>，否则会造成一些相等的额外相加。 
>
>  2.40行的地方要注意与Dijkstra的区别！！不是加而是直接换！！！



```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e5+5;
struct edge{
    int to,cost;
};
vector<edge>G[maxn];
struct d{
    int num,dis;
};
bool operator <(d a,d b)
{
    return a.dis>b.dis;
}
bool vis[maxn];
int main()
{
    int n,m,i,j,k;
    cin>>n>>m;
    for(i=1;i<=m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        G[a].push_back(edge{b,c});
        G[b].push_back(edge{a,c});
    }
    int dis[maxn];memset(dis,0x7f,sizeof(dis));dis[1]=0;
    priority_queue<d>que;que.push(d{1,0});
    int ans=0;
    while(!que.empty()){
        d t=que.top();que.pop();
        if(vis[t.num])continue;//如果不用额外数组这里要注意
        ans+=t.dis;vis[t.num]=true;
        for(i=0;i<G[t.num].size();i++){
            edge e=G[t.num][i];
            if(dis[e.to]>e.cost){
                dis[e.to]=e.cost;//注意这里与Dijkstra的区别
                que.push(d{e.to,dis[e.to]});
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}
```



### Kruskal

最重要的还是记得并查集要初始化！！

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct edge{
    int from,to,cost;
}G[200005];//这里是边数
int par[5005],rank1[5005];//这里是顶点数
bool cmp(edge a,edge b)
{
    return a.cost<b.cost;
}
int find(int x)
{
    return par[x]==x?x:find(par[x]);
}
bool unite(int x, int y)
{
    x = find(x); y = find(y);
    if (x == y)
        return false;
    if (rank1[x] < rank1[y]) {
        par[x] = y;
    }
    else {
        par[y] = x;
        if (rank1[x] == rank1[y])
            rank1[x]++;
    }
    return true;
}
int main()
{
    int n,m,i,j,k;
    cin>>n>>m;
    for(i=1;i<=n;i++)
        par[i]=i;
    for(i=1;i<=m;i++){
        scanf("%d %d %d",&G[i].from,&G[i].to,&G[i].cost);
    }
    sort(G+1,G+1+m,cmp);int cnt=0,ans=0;
    for(i=1;;i++){
        if(unite(G[i].from,G[i].to))cnt++,ans+=G[i].cost;
        if(cnt==n-1)break;
    }

    cout<<ans<<endl;

    return 0;
}
```





### Tarjan

要注意的就是那些单独的点每个点都会被当做自身一个强联通分量，也就是有不少的强连通分量里面可能只有一个元素……

```cpp
const int maxn=1e5+5;
int dfn[maxn],low[maxn],scccnt=0,sccindex=0,belong[maxn];//连通分量的cnt，连通分量的索引，代表这个点属于哪个连通分量
bool instack[maxn];
stack<int>sta;
vector<int>G[105];
void tarjan(int v)
{
    dfn[v]=low[v]=++sccindex;
    sta.push(v);instack[v]=true;int j;
    for(auto i=G[v].begin();i!=G[v].end();i++){
        int j=*i;//理论上用c++11的特性会比G[v].size()快一些;
        if(!dfn[j]){
            tarjan(j);
            low[v]=min(low[v],low[j]);
        }
        else if(instack[j]&&dfn[j]<low[v])
            low[v]=dfn[j];
    }
    if(low[v]==dfn[v]){
        scccnt++;
        do{
            j=sta.top();instack[j]=false;
            sta.pop();belong[j]=scccnt;
        }while(j!=v);//一定要注意这里并不是要把整个栈清空,只是要把属于当前联通分量的元素全部清空
    }
}
```



### 拓扑排序

搞一个队列然后维护一下入度，把队首元素出队，入度--，入度为0的就入队，直到队列为空即可。如果队列为空而有的元素还没有入过队，就无法拓扑排序。

### 匈牙利算法

二分图匹配的问题基本上都能转换为最大流的问题…只有极少的情况下才一定要用匈牙利算法去解决（如洛谷P1640 [SCOI2010]连续攻击游戏），注意匈牙利算法加边的时候addedge函数里面加单向边即可。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=1e5+5; 
vector<int>G[maxn];
int match[maxn], n, m, e;
bool used[maxn];
void addedge(int a, int b)
{
    G[a].push_back(b);
    //G[b].push_back(a);
}
bool dfs(int v)
{
    for (int i = 0; i < G[v].size(); i++) {
        int t = G[v][i], u = match[t];
        if (!used[t]) {
            used[t] = true;
            if (u < 0 || dfs(u)) {
                //match[v] = t;
                match[t] = v;
                return true;
            }
        }
    }
    return false;
}
int hungarian(void)
{
    memset(match, -1, sizeof(match));
    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(used, 0, sizeof(used));
        if (dfs(i))
            res++;
    }
    return res;
}
int main()
{
    cin >> n >> m >> e;
    int i;
    for (i = 1; i <= e; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (b > m)continue;//模板题中需要判断是不是合法点
        addedge(a, b);
    }
    int ans = hungarian();
    cout << ans << endl;

    return 0;
}
```



### 网络流最大流（Dinic）

**结论：图的最小割=图的最大流（最大流最小割定理）**（图是有源汇的）

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
struct edge{
    int to,cap,rev;
};
vector<edge>G[maxn];
int level[maxn],iter[maxn];
void addedge(int from,int to,int cap)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
int maxflow(int s,int t){
    int flow=0;//小心爆int
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while(f=dfs(s,t,0x7f7f7f7f))//注意如果爆int这里初始最大值要更改最大值
            flow+=f;
    }
}
int main()
{
    return 0;
}#include<bits/stdc++.h>
const int maxn=1e5+5;
struct edge{
    int to,cap,rev;
};
vector<edge>G[maxn];
int level[maxn],iter[maxn];
void addedge(int from,int to,int cap)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
int maxflow(int s,int t){
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while(f=dfs(s,t,0x7f7f7f7f))
            flow+=f;
    }
}
```



### 最小费用流

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
struct edge{
    int to,cap,cost,rev;//终点,容量,费用,反向边
};
vector<edge>G[maxn];
int dis[maxn],prevv[maxn],preve[maxn],n,m,s,t,flow=0,cost=0;//最短路中前驱节点和前驱边
bool inque[maxn];
void add(int from,int to,int cap,int cost)
{
    G[from].push_back(edge{to,cap,cost,(int)G[to].size()});
    G[to].push_back(edge{from,0,-cost,(int)G[from].size()-1});//注意反向边的加法!!-cost和cap=0!!
}
bool spfa(int s,int t)
{
    memset(dis,0x3f, sizeof(dis));memset(inque,0,sizeof(inque));
    queue<int>que;que.push(s);dis[s]=0;
    while(!que.empty()){
        int t=que.front();que.pop();inque[t]=false;
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap&&dis[e.to]>dis[t]+e.cost){
                dis[e.to]=dis[t]+e.cost;
                prevv[e.to]=t;preve[e.to]=i;
                if(!inque[e.to]){
                    que.push(e.to);inque[e.to]=true;
                }
            }
        }
    }
    if(dis[t]==0x3f3f3f3f)
        return false;
    int d=0x7f7f7f7f;
    for(int v=t;v!=s;v=prevv[v])
        d=min(d,G[prevv[v]][preve[v]].cap);//全最短路中的最小流量限制就是本次总的流量限制
    flow+=d;cost+=d*dis[t];
    for(int v=t;v!=s;v=prevv[v]){
        edge&e=G[prevv[v]][preve[v]];//更新路径信息
        e.cap-=d;
        G[e.to][e.rev].cap+=d;
    }
    return true;
}
void mincostmaxflow(int s,int t)
{
    while(spfa(s,t));
}
```

### 最大流与二分图的一些结论

### 匹配，边覆盖，独立集合顶点覆盖

#### **概念：**

$V$：**全集**
**匹配——在图中两两没有公共顶点的边的集合**
注意，图中的匹配有很多，一条边也可以算一个匹配。但是最大匹配却是可以确定的。最大匹配也就是要让选出尽可能多的边使得它们两两之间都没有交点（端点）。
**边覆盖——图中的任意顶点都至少是集合$F$中某条边的的端点，满足这样条件的集合的最少的边的集合$F$称为最小边覆盖**
**独立集——在图中两两不相连的顶点集合**
比如一条边S的顶点是$S_a,S_b$,那么这两个点就不能同时在一个独立集中。事实上，独立集中的任意两个点之间都不存在有边之间相连。
**顶点覆盖——图中的任意边都至少有一个端点属于集合$S$的集合叫做顶点覆盖**

#### **结论**

  **(a)对于不存在孤立点的图，|最大匹配|+|最小边覆盖|=|$V$|（边的全集）**（即任意一个顶点都至少在某条边中）

**（b）|最大独立集|+|最小顶点覆盖|=|$V$|（点的全集）**
**（c）在二分图中，有：|最大匹配|=|最小顶点覆盖|**（可用于求解二分图的最大独立集和最小顶点覆盖）
**（d）|图的最大流|=|图的最小割|（图有源汇）**

### 最大权闭合图

所谓闭合图，指的是图中每个点的后续都在图中。

**最大权闭合图，指的是点的权值之和最大的闭合图。**

#####**最大权闭合图的求解方法**

**1.先构造网络流N，添加源点s，从s到正权值点做一条边，容量为点的权值。**

**2.添加汇点t，从负权值点到t做一条边，容量为点的权值的绝对值。**

**3.原来的边的容量统统设为无穷大**

**4.求解最小割，最大权=正权值之和-最小割权值**

**5.最小割所产生的两个集合中，其源点S所在集合(除去S)为最大权闭合图。**（也就是POJ2987所求的裁员）

EX:POJ2987

> 公司官僚成风，盘根错节，办实事的码农没几个。老板决定大裁员，每开除一个人，同时要将其下属一并开除，如果该下属还有下属，照斩不误。给出每个人的贡献值（可为负）和从属关系，求最小裁员数及最大贡献值和。

模板题，记得开long long即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=5e3+5;
struct edge{
    int to,cap,rev;
};
vector<edge>G[maxn];
int level[maxn],iter[maxn];
void addedge(int from,int to,int cap)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
long long  maxflow(int s,int t){
    long long flow=0;//小心爆int
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        long long f;
        while(f=dfs(s,t,0x7f7f7f7f))//注意如果爆int这里初始最大值要更改最大值
            flow+=f;
    }
}
bool vis[maxn];int cnt=0;
void dfs(int x)
{
    vis[x]=true;cnt++;
    for(int i=0;i<G[x].size();i++){
        if(G[x][i].cap>0&&!vis[G[x][i].to])
            dfs(G[x][i].to);
    }
}
int main()
{
    int n,m,i,j,k;
    cin>>n>>m;
    long long sum=0;
    for(i=1;i<=n;i++){
        scanf("%d",&j);
        if(j>=0){
            addedge(0,i,j);sum+=j;
        }
        else{
            addedge(i,5001,-j);
        }
    }
    for(i=1;i<=m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        addedge(a,b,1<<30);
    }
    sum-=maxflow(0,5001);
    dfs(0);
    cout<<cnt-1<<' '<<sum<<endl;

    return 0;
}

```



### 最小路径覆盖

**对于一个给定的有向无环图（DAG），求其最小路径覆盖。**

题目可参见洛谷P2764。
**【问题分析】**
有向无环图最小路径覆盖，可以转化成二分图最大匹配问题，从而用最大流解决。
**【建模方法】**
构造二分图，把原图每个顶点i拆分成二分图X，Y集合中的两个顶点$X_i$和$Y_i$。对于原图中存在的每条边$(i,j)$，在二分图中连接边$(X_i,Y_j)$。然后把二分图最大匹配模型转化为网络流模型，求网络最大流。
最小路径覆盖的条数，就是原图顶点数，减去二分图最大匹配数。沿着匹配边查找，就是一个路径上的点，输出所有路径即可。
**【建模分析】**
对于一个路径覆盖，有如下性质：
1、每个顶点属于且只属于一个路径。
2、路径上除终点外，从每个顶点出发只有一条边指向路径上的另一顶点。所以我们可以把每个顶点理解成两个顶点，一个是出发，一个是目标，建立二分图模型。该二分图的任何一个匹配方案，都对应了一个路径覆盖方案。如果匹配数为0，那么显然路径数=顶点数。每增加一条匹配边，那么路径覆盖数就减少一个，所以路径数=顶点数 – 匹配数。要想使路径数最少，则应最大化匹配数，所以要求二分图的最大匹配。注意，此建模方法求最小路径覆盖仅适用于有向无环图，如果有环或是无向图，那么有可能求出的一些环覆盖，而不是路径覆盖。

###有上下界的网络流

####无源汇可行流

#####建图方法

将有上下界的网络流图转化成普通的网络流图

首先建立附加源点ss和附加汇点tt
对于原图中的边x->y，若限制为[b,c]，那么连边x->y，流量为c-b
对于原图中的某一个点i，记d(i)为流入这个点的所有边的下界和减去流出这个点的所有边的下界和 （上面在连每一条边的时候建一个cur数组记一下输入输出即可）
若d(i)>0，那么连边ss->i，流量为d(i) ，同时期望的流量值sum+=d（i)
若d(i)<0，那么连边i->tt，流量为-d(i)
求解方法
在新图上跑ss到tt的最大流
若新图满流（流量等于sum），那么一定存在一种可行流
此时，原图中每一条边的流量应为新图中对应的边的流量+这条边的流量下界

#####EX：LOJ115

> 这是一道模板题。 n个点，m条边，每条边 e有一个流量下界 $lower(e) $和流量上界$ upper(e)$，求一种可行方案使得在所有点满足流量平衡条件的前提下，所有边满足流量限制。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
struct edge{
    int to,cap,rev,id;
};
vector<edge>G[310];
int level[305],iter[305],cur[305],lower[30500];
void addedge(int from,int to,int cap)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
int maxflow(int s,int t){
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while(f=dfs(s,t,0x7f7f7f7f))
            flow+=f;
    }
}
struct ans{
    int id,flow;
    bool operator<(const ans&a)const{
        return id<a.id;
    }
};
int main()
{
    int n,m,i,j,k;
    cin>>n>>m;
    for(i=1;i<=m;i++){
        int s,t,l,u;
        scanf("%d%d%d%d",&s,&t,&lower[i],&u);
        cur[s]-=lower[i];cur[t]+=lower[i];
        addedge(s,t,u-lower[i]);G[s].back().id=i;
    }
    int sum=0;
    for(i=1;i<=n;i++){
        if(cur[i]>0){
            addedge(0,i,cur[i]);
            sum+=cur[i];
        }
        else if(cur[i]<0){
            addedge(i,250,-cur[i]);
        }
    }
    int flow=maxflow(0,250);
    if(flow!=sum){
        cout<<"NO"<<endl;return 0;
    }
    vector<ans>as;
    for(i=1;i<=n;i++){
        for(auto a:G[i]){
            if(!a.id)continue;
            as.push_back(ans{a.id,lower[a.id]+G[a.to][a.rev].cap});
        }
    }
    sort(as.begin(),as.end());
    cout<<"YES"<<endl;
    for(auto a:as){
        cout<<a.flow<<endl;
    }

    return 0;
}
```

####有源汇可行流

#####建图方法

在原图中添加一条边t->s，流量为$inf$
即让源点和汇点也满足流量平衡条件
这样就改造成了无源汇的网络流图，其余建图方法与无源汇可行流相同。

####有源汇有上下界最大流

#####建图方法

将有上下界的网络流图转化成普通的网络流图

首先建立附加源点ss和附加汇点tt
对于原图中的边x->y，若限制为[b,c]，那么连边x->y，流量为c-b
对于原图中的某一个点i，记d(i)为流入这个点的所有边的下界和减去流出这个点的所有边的下界和
若d(i)>0，那么连边ss->i，流量为d(i)
若d(i)<0，那么连边i->tt，流量为-d(i)
**（以上与无源汇可行流相同）**
在原图中添加一条边t->s，流量为inf
即让源点和汇点也满足流量平衡条件
这样就改造成了无源汇的网络流图
**（以上与有源汇可行流相同）**
在新图上跑ss到tt的最大流
若新图满流，那么一定存在一种可行流
记此时$∑f(s,i)=sum1$ ，即此时t->s的最大流，也就是求反向边s->t的流量
将t->s这条边拆掉，在新图上跑s到t的最大流
记此时$∑f(s,i)=sum2$，即$maxflow（s，t）$
最终答案即为$sum1+sum2$

##### EX:LOJ116

> 这是一道模板题。 n个点，m条边，每条边 e有一个流量下界$lower(e)$和流量上界$ upper(e)$，给定源点 s与汇点 t，求源点到汇点的最大流.

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
struct edge{
    int to,cap,rev;
    bool tag;
};
vector<edge>G[410];
int level[405],iter[405],cur[405],lower[10005];
void addedge(int from,int to,int cap,int s)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
    if(from==s)G[from].back().tag=true;
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
int maxflow(int s,int t){
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while(f=dfs(s,t,0x7f7f7f7f))
            flow+=f;
    }
}
int main()
{
    int n,m,s,t,i,j,k;
    cin>>n>>m>>s>>t;
    for(i=1;i<=m;i++){
        int from,t,up;
        scanf("%d%d%d%d",&from,&t,&lower[i],&up);
        addedge(from,t,up-lower[i],s);cur[from]-=lower[i];cur[t]+=lower[i];
    }
    int sum=0;
    for(i=1;i<=n;i++){
        if(cur[i]>0){
            addedge(0,i,cur[i],s);sum+=cur[i];
        }
        else{
            addedge(i,250,-cur[i],s);
        }
    }
    addedge(t,s,(1<<31)-1,s);
    int flow=maxflow(0,250);
    if(sum!=flow){
        cout<<"please go home to sleep"<<endl;return 0;
    }
    int ans=G[s].back().cap;
    G[s].pop_back();G[t].pop_back();
    ans+=maxflow(s,t);
    cout<<ans<<endl;

    return 0;
}
```

####有源汇有上下界最小流

#####建图方法

将有上下界的网络流图转化成普通的网络流图
首先建立附加源点ss和附加汇点tt
对于原图中的边x->y，若限制为[b,c]，那么连边x->y，流量为c-b
对于原图中的某一个点i，记d(i)为流入这个点的所有边的下界和减去流出这个点的所有边的下界和
若d(i)>0，那么连边ss->i，流量为d(i)
若d(i)<0，那么连边i->tt，流量为-d(i)
**（以上与无源汇可行流相同)**
求res=ss->tt最大流
连边t->s,inf
求res+=ss->tt最大流
如果res！=sum也就是期望中的满流，那么就没有可行解。
**需要格外注意最小流判断是否有可行解的位置与时机与另外几种上下界网络流的不同！！！否则，输出G[s].back().cap也就是从t到s inf边的实际流量，即为所求。**

#####EX:LOJ117

> n 个点，m条边，每条边 e有一个流量下界 $lower(e)$和流量上界 $upper(e)$，给定源点 s与汇点 t，求源点到汇点的最小流。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
struct edge{
    int to;ll cap;int rev;
};
vector<edge>G[50210];
int level[50205],iter[50205],low[125050];ll cur[50205];
void addedge(int from,int to,ll cap)
{
    G[from].push_back(edge{to,cap,(int)G[to].size()});
    G[to].push_back(edge{from,0,(int)G[from].size()-1});//反向容量为0!!
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;que.push(s);
    while(!que.empty()){
        int t=que.front();que.pop();
        for(int i=0;i<G[t].size();i++){
            edge e=G[t][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[t]+1;
                que.push(e.to);
            }
        }
    }
}
ll dfs(int v,int t,ll f)
{
    if(v==t)return f;
    for(int&i=iter[v];i<G[v].size();i++){//注意传引用!
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            ll d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;//不要漏了这个,很多时候可能是无法增广的
}
ll maxflow(int s,int t){
    ll flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        ll f;
        while(f=dfs(s,t,0x7f7f7f7f7f7f7f7f))
            flow+=f;
    }
}
int main()
{
    int n,m,s,t,i,j,k;
    cin>>n>>m>>s>>t;
    for(i=1;i<=m;i++){
        int from,to,up;scanf("%d%d%d%d",&from,&to,&low[i],&up);
        cur[from]-=low[i];cur[to]+=low[i];addedge(from,to,up-low[i]);
    }
    ll sum=0;
    for(i=1;i<=n;i++){
        if(cur[i]>0){
            addedge(0,i,cur[i]);sum+=cur[i];
        }
        else if(cur[i]<0){
            addedge(i,50050,-cur[i]);
        }
    }
    ll flow=maxflow(0,50050);
    addedge(t,s,(1LL<<63)-1);
    flow+=maxflow(0,50050);
    if(flow!=sum){
        cout<<"please go home to sleep"<<endl;return 0;
    }
    cout<<G[s].back().cap<<endl;

    return 0;
}
```



## 字符串

### 后缀数组

#####定义

字符串$$s$$连续的一段字符组成的串叫做字符串，更广义地，任何一个由可比较大小的元素组成的数组都可称为字符串。字符串的下标从 1开始，长度为$$length(s)$$ 。

**后缀**： $$suffix(i)$$表示字符串$$s$$从第$$i$$个位置开始的后缀，即由 $$s[i]-s[n] $$组成的子串。

**字符串的比较**： 两个字符串大小的比较，从首位开始，一位一位地按照 ASCII 码比较，如果从某位置开始不相同，则认为该位置处字符 ASCII 码小的字符串小； 如果一个字符串比较完了最后一位，而另一个没有，则认为前者（长度小的）小； 如果两个字符串长度相同并且所有位置上的字符均相同，则认为两个字符串相等。
**注意，同一个字符串的两个后缀是不可能相等的，因为无法满足相等的必要条件长度相同。**

**后缀数组**： $$sa$$是一个一维数组，保存了对字符串$$s$$的所有后缀排序后的结果。 表示第$$i$$小的后缀在原串中的起始位置。

**名次数组**： $$rank$$是一个一维数组，按起始位置保存了每个后缀在 $$sa$$中的排名。 表示$$suffix(i)$$的排名，即 $$rank[sa[i]]=i$$（第$$i$$小的后缀的排名为$$i$$）。

**高度数组**： 是一个一维数组，保存了相邻两个后缀的最长公共前缀（**Longest Common Prefix，LCP**）长度。

$$height[i]=LCP(suffix(sa[i]),suffix[sa[i-1]))$$**(i>0)

即$$height[i]$$表示在位置$$i$$存在最大的$$x$$,满足$$\forall k \in [0,x)$$有$$s[sa[i]+k]=s[sa[i-1]+k]$$

#####最长公共前缀

通过高度数组$$height$$ ，我们可以得到排名相邻的两个后缀的最长公共前缀。

对于排名不相邻的两个后缀，它们的前缀的相似性比相邻后缀要差。显然排名不相邻的两个后缀的最长公共前缀长度**一定不会**比这两个后缀在后缀数组中确定的一段**区间中任意两个**相邻后缀的最长公共前缀长度更长。

所以，求出这段区间内最小的$$height$$值即为这两个不相邻后缀的最长公共前缀长度。

问题转化为区间最值查询**（Range Minimum/Maximum Query，RMQ）**问题，可以使用稀疏表**（Sparse Table，ST）**算法解决。该算法在$$O(n\ logn)$$ 的时间内预处理，并在 $$O(1) $$的时间内完成每个询问。

#####代码

字符串/数组保存在**s**数组中，**maxn**是字符串/数组的最大长度，**rk**是$rank$数组，**sa**就是$sa$数组，**ht**是$height$数组。（按照洛谷P3809的要求）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
char s[maxn];
int rk[maxn],sa[maxn],ht[maxn];
inline void suffixArray()
{
    int n=strlen(s+1);
    static int set[maxn + 1], a[maxn + 1];
    std::copy(s + 1, s + n + 1, set + 1);
    std::sort(set + 1, set + n + 1);
    int *end = std::unique(set + 1, set + n + 1);
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(set + 1, end, s[i]) - set;

    static int fir[maxn + 1], sec[maxn + 1], tmp[maxn + 1], buc[maxn + 1];
    for (int i = 1; i <= n; i++) buc[a[i]]++;
    for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
    for (int i = 1; i <= n; i++) rk[i] = buc[a[i] - 1] + 1;

    for (int t = 1; t <= n; t *= 2)
    {
        for (int i = 1; i <= n; i++) fir[i] = rk[i];
        for (int i = 1; i <= n; i++) sec[i] = i + t > n ? 0 : rk[i + t];

        std::fill(buc, buc + n + 1, 0);
        for (int i = 1; i <= n; i++) buc[sec[i]]++;
        for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
        for (int i = 1; i <= n; i++) tmp[n - --buc[sec[i]]] = i;

        std::fill(buc, buc + n + 1, 0);
        for (int i = 1; i <= n; i++) buc[fir[i]]++;
        for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
        for (int j = 1, i; j <= n; j++) i = tmp[j], sa[buc[fir[i]]--] = i;

        bool unique = true;
        for (int j = 1, i, last = 0; j <= n; j++)
        {
            i = sa[j];
            if (!last) rk[i] = 1;
            else if (fir[i] == fir[last] && sec[i] == sec[last]) rk[i] = rk[last], unique = false;
            else rk[i] = rk[last] + 1;

            last = i;
        }

        if (unique) break;
    }

    for (int i = 1, k = 0; i <= n; i++)
    {
        if (rk[i] == 1) k = 0;
        else
        {
            if (k > 0) k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && a[i + k] == a[j + k]) k++;
        }
        ht[rk[i]] = k;
    }
}
int main()
{
    scanf("%s",s+1);int n=strlen(s+1);
    suffixArray();
    for(int i=1;i<=n;i++)
        printf("%d%c",sa[i],i==n?'\n':' ');

    return 0;
}

```



## 其他

### 快速读入

与cin，scanf冲突（输出没问题），可返回EOF

```cpp
const int BufferSize=1<<16;
char buffer[BufferSize],*fronthead,*fronttail;
inline char GET_CHAR(){
    if(fronthead==fronttail){
        int l=fread(buffer,1,BufferSize,stdin);
        fronttail=(fronthead=buffer)+l;
        if(fronthead==fronttail)return EOF;
    }
    return *fronthead++;
}
inline int READ(){
    int x=0,f=1;char c=GET_CHAR();
    for(;!isdigit(c);c=GET_CHAR()){
        if(c==EOF)return EOF;
        if(c=='-')f=-1;
    }
    for(;isdigit(c);c=GET_CHAR())x=(((x<<2)+x)<<1)+c-'0';
    return x*f;
}
```



