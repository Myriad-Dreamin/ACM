添加模板
模板要有编号
例如
栈：DS-01
所有模板依赖前注明依赖的编号


下面写编程风格的规范，可以增加意见

数组规范：
栈
int st[];
//stack<T> st;

队列
int Q[];
//queue<T> Q;

代码规范：

死循环
for(;;)
{
  //;
}
不要用：
while(1){}
理由：
while(1)的效率比for(;;)低

小范围引用
for(){
  edge &e;
}
不要用
for(){
  edge e;
}



命名冲突：
以tarjan等为例子
void Tarjan_st[],Tarjan_top;
void Tarjan_vis[];
void Tarjan_init(){
  //init...
}

void Tarjan_dfs(){
  //dfs...
}
事实上，如果有非常少见或者专有的命名，可以不用下划线保证命名不冲突
如：
int dfn[],low[],mat[],mob[],prim[],phi[];
但是要保证任何时候它们的意义相同，具体见数组规范。
