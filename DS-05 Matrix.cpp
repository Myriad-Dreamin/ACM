#include <cstdio>
#include <cstring>

//方阵
//Dim:最大维
//a[0][0]:维数
//a[1]~a[a[0][0]]:矩阵

//pow(
//  int b,matrix &res
//  res=*this^b
//)


//premat(
//  int n,matrix &Mat=X[0]
//  X[i]=X[i-1]^2,1~logn
//)

//prepow(
//  int b<2*n,matrix &res
//  同pow
//)
typedef long long Matrixtype;
const int Dim=101;
//const Matrixtype mod=1e9+7;
struct Matrix{
    Matrixtype a[Dim][Dim];
    inline Matrixtype* const operator[](const int _i){return a[_i];}
    void setsiz(int siz){a[0][0]=siz;}
    void empty(int siz=0){
        if(siz){a[0][0]=siz;for(int i=a[0][0];i;i--)for(int j=a[0][0];j;j--)a[i][j]=0;}
        else memset(a,0,sizeof(a));
    }
    void I(int siz){a[0][0]=siz;for(int i=siz;i;i--)for(int j=siz;j;j--)a[i][j]=(i==j);}
    void J(int siz){a[0][0]=siz;for(int i=siz;i;i--)for(int j=siz;j;j--)a[i][j]=1;}
    void copy(Matrix &b){
        a[0][0]=b[0][0];
        for(int i=a[0][0];i;i--){
            for(int j=a[0][0];j;j--)a[i][j]=b[i][j];
        }
    }
    void prt(){
        puts("--------------");
        for(int i=1;i<=a[0][0];i++,puts("")){
            for(int j=1;j<=a[0][0];j++)
                //printf("%d ",a[i][j]);
                printf("%I64d ",a[i][j]);
        }
    }
    Matrix operator*(Matrix &b)const{
        Matrix res;
        res[0][0]=a[0][0];
        for(int i=a[0][0];i;i--){
            for(int j=a[0][0];j;j--){
                res[i][j]=0;
                for(int k=a[0][0];k;k--){
                    res[i][j]+=a[i][k]*b[k][j];
                    //res[i][j]%=mod;
                }
            }
        }
        // for(int i=a[0][0];i;i--){
        //     for(int j=a[0][0];j;j--){
        //         res[i][j]%=mod;
        //     }
        // }
        return res;
    }
    void pow(Matrixtype n,Matrix &res){
        Matrix x;
        res.I(a[0][0]);
        x.copy(*this);
        while(n){
            if(n&1)res=res*x;
            x=x*x; n>>=1;
        }
    }
};
Matrix X[(16<<sizeof(Matrixtype))+1];
void premat(Matrixtype n,Matrix &Mat){
    int k=1;X[0].copy(Mat);
    while(n>>k){
        X[k]=X[k-1]*X[k-1];k++;
    }
}
void prepow(Matrixtype n,Matrix &res){
    res.I(X[0][0][0]);
    for(int bit=0;n>>bit;bit++){
        if((n>>bit)&1)res=res*X[bit];
    }
}
int main(){
    return 0;
}
