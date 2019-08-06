# Matrix

使用注意：

+ MOD修改为需要的大小。
+ MOD2为乘法加速，必须有`2*MOD2<MAXLL`
+ 各个函数的参数维度默认以第一个参数为准
+ `?:`比`if`快


```c++
const int MOD = 998244353;
const long long MOD2 = 1ll * MOD * MOD;

// 向量
typedef vector<int> vec;

// 矩阵
typedef vector<vec> mat;
```
基础板子：
```c++
// mat(n * n) + mat(n * n) = mat(n * n)
mat operator +(const mat &a,const mat &b){
    int n=a.size();
    mat c(n,vec(n));
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            int x=a[i][j]+b[i][j];
            x>=MOD?x-=MOD:0;
            c[i][j]=x;
        }
    }
    return c;
}

// mat(n * n) * mat(n * n) = mat(n * n)
mat operator *(const mat &a,const mat &b){
    int n=a.size();
    mat c(n,vec(n));
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            long long x=0;
            for(int k=0;k<n;++k){
                x+=1ll*a[i][k]*b[k][j];
                x>=MOD2?x-=MOD2:0;
            }
            c[i][j]=x%MOD;
        }
    }
    return c;
}

// mat(n * n) * vec(n * 1) = vec(n * 1)
vec operator *(const mat &a,const vec &b){
    int n=a.size();
    vec c(n);
    for(int i=0;i<n;++i){
        long long x=0;
        for(int j=0;j<n;++j){
            x+=1ll*a[i][j]*b[j];
            x>=MOD2?x-=MOD2:0;
        }
        c[i]=x%MOD;
    }
    return c;
} 
```
快速幂
```c++
mat qp(mat a, int d) {
	int n = a.size();
	mat c = mat(n, vec(n, 0));
	for (int i = 0; i < n; i++)
		c[i][i] = 1;
	while (d > 0) {
		if (d % 2 == 1)
			c = mul(c, a);
		a = mul(a, a);
		d /= 2;
	}
	return c;
}
```
预处理快速幂
```c++
const int LogN = 30;
mat pre[LogN + 5];
void init(mat &xxx) {
	pre[0]=xxx;
	for(int i=1;i<=LogN;i++) {
		pre[i]=pre[i-1]*pre[i-1];
	}
}
void prepow(int d, vec &b)
{
	for(int i = 0; i <= LogN; i++)
	{
		if(d & 1) 
			b = pre[i] * b;
		d>>=1;
	}
	return ;
}
```

