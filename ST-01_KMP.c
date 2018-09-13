#include <bits/stdc++.h>
using namespace std;

/*
 * next[] 的含义是: x[i-next[i]...i-1]=x[0...next[i]-1]
 * next[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值（就是 x 的自身匹配）
 */

void kmp_pre(char x[],int m,int next[]){
    int i,j;
    j=next[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j && x[i]!=x[j])j=next[j];
        next[++i]=++j;
    }
}

/* 
 * kmpNext[i] 的意思:next'[i]=next[next[...[nexi[i]]]] (直到next'[i]<0 或者 x[next'[i]]!=x[i])
 * 这样的预处理可以快一些
 */
 
void preKMP(char x[],int m,int kmpNext[]){
    int i,j;
    j=kmpNext[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j && x[i]!=x[j])j=kmpNext[j];
        if(x[++i]==x[++j])kmpNext[i]=kmpNext[j];
        else kmpNext[i]=j;
    }
}

/*
 * 返回 x 在 y 中出现的次数，可以重叠
 */
int next[10010];
int KMP_Counter(char x[],int m,char y[],int n){ //x是模式串，y是主串
    int i,j;
    int ans=0;
    //preKMP(x,m,next);
    kmp_pre(x,m,next);
    i=j=0;
    while(i<n){
        while (-1!=j && y[i]!=x[j])j=next[j];
        ++i;++j;
        if (j>=m){
            ++ans;
            j=next[j];
        }
    }
    return ans;
}


//经典题目: POJ 3167
/*
 * POJ 3167 Cow Patterns
 * 模式串可以浮动的模式匹配问题
 * 给出模式串的相对大小，需要找出模式串匹配次数和位置
 * 比如说模式串：1，4，4，2，3，1 而主串：5,6,2,10,10,7,3,2,9
 * 那么 2,10,10,7,3,2 就是匹配的
 *
 * 统计比当前数小，和于当前数相等的，然后进行 kmp
 */
int main(){
    
}