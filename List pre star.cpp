//DS-01

//参数
//Headsize:顶点数
//Edgesize:有向边数

//struct
//nx : 下一条边的下标
//to : 边指向的结点
//w  : 边权
//mal: 分配边所用的编号

//初始化
//init(void):必须调用

//加边
//adddege(
//  int u,int v,int w
//  弧头,弧尾,边权
//);
//
/*遍历方法
for(int i=head[u];i;i=e[i].nx){
	int v=e[i].to;
	//operation...
}
 */
const int Headsize=N,Edgesize=M;
int head[Headsize+5],mal;
struct edge{
	int nx,to,w;
}e[Edgesize+5];
inline void init(){
    mal=1;
    memset(head,0,sizeof(head));
}
inline void addedge(int u,int v,int val){
	e[mal].to=v;e[mal].w=val;e[mal].nx=head[u];head[u]=mal++;
}



//无边权
const int Headsize=N,Edgesize=M;
int head[Headsize+5],mal;
struct edge{
	int nx,to;
}e[Edgesize+5];
inline void init(){
    mal=1;
    memset(head,0,sizeof(head));
}
inline void addedge(int u,int v){
	e[mal].to=v;e[mal].nx=head[u];head[u]=mal++;
}

//网络流链式前向星
//加边特性
//反边必须成对加入
//addedge(u,v,w);addedge(v,u,w);
//e[i]的反边是e[i^1]

/*遍历方法
for(int i=head[u];~i;i=e[i].nx){
	int v=e[i].to;
	//operation...
}
 */
const int Headsize=N,Edgesize=M;
int head[Headsize+5],mal;
struct edge{
	int nx,to;
}e[Edgesize+5];
inline void init(){
    mal=0;
    memset(head,-1,sizeof(head));
}
inline void addedge(int u,int v){
	e[mal].to=v;e[mal].nx=head[u];head[u]=mal++;
}

