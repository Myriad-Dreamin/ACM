#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <bitset>
using namespace std;
const int N=505;
bitset<N> isa[505],hasa[505];
map<string, int> mp;
int mal=0;
int mpname(const string &str){
	if(mp.count(str)){
		return mp[str];
	}
	else {
		// cout <<str <<" maloc " << mal+1 <<endl;
		return mp[str]=++mal;
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	string uname,r,vname;
	for(int i=1;i<=n;i++){
		cin>>uname>>r>>vname;
		int u=mpname(uname),v=mpname(vname);
		if(r=="has-a")hasa[u][v]=true;
		else if(u!=v) isa[u][v]=true;
	}
	for(int k=1;k<=mal;k++){
		for(int i=1;i<=mal;i++){
			if(isa[i][k])isa[i]|=isa[k];
		}
	}
	for(int i=1;i<=mal;i++){
		isa[i][i]=true;
	}
	for(int k=1;k<=mal;k++){
		for(int i=1;i<=mal;i++){
			if(isa[i][k])hasa[i]|=hasa[k];
		}
	}
	for(int k=1;k<=mal;k++){
		for(int i=1;i<=mal;i++){
			if(hasa[i][k])hasa[i]|=hasa[k]|isa[k];
		}
	}
	// for(int i=1;i<=mal;i++){
	// 	cout << hasa[i] <<endl;
	// }
	for(int i=1;i<=m;i++){
		cin>>uname>>r>>vname;
		int u=mpname(uname),v=mpname(vname);
		if(r=="has-a"){
			printf("Query %d: %s\n",i,hasa[u][v]?"true":"false");
		}else{
			printf("Query %d: %s\n",i,isa[u][v]?"true":"false");

		}
	}
}
/**/