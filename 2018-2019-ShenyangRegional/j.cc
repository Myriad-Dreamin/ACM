#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
int findlb(string &b){
    for(int i=0;i<b.length();i++){
        if(b[i]=='[')return i;
    }
    return -1;
}
int fbyte(string &b){
    // cout << b<<endl;
    if(b[0]=='b'){
        return 1;
    }
    if(b[0]=='c'){
        return 1;
    }
    if(b[0]=='i'){
        return 4;
    }
    if(b[0]=='_'){
        return 16;
    }
    if(b[0]=='f'){
        return 4;
    }
    if(b[0]=='d'){
        return 8;
    }
    if(b[0]=='l'){
        if(b[5]=='d'){
            return 16;
        }else{
            return 8;
        }
    }
    return -1;
}
int farr(string &b){
    if(b[b.length()-2]!=']')return 1;
    int x=findlb(b) + 1,res=0;
    for(int i=x;i<b.length()-2;i++){
        res=res*10+b[i]-'0';
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    int T,n,gt,arrl;
    cin>>T;
    string l,a,b;
    for(int ttt=1;ttt<=T;ttt++){
        cin>>n;
        int res=0;
        getline(cin,l);
        for(int i=1;i<=n;i++){
            getline(cin,l);
            gt = fbyte(l);
            arrl = farr(l);
            res+=gt*arrl;
            // cout << gt <<" "<<arrl<<endl;
        }
        res = res/1024 + ((res%1024)>0);
        cout<<"Case #"<<ttt<<": " <<res<<endl;
    }
}