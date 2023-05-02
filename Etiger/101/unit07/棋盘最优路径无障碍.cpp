#include<iostream>
using namespace std;
int d[6][6],g[6][6];
int main(){
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++){
			char ch; cin>>ch;
			d[i][j]=ch-'0';
		}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			if(i==1&&j==1) g[1][1]=d[1][1];
			else g[i][j]=max(g[i-1][j],g[i][j-1])+d[i][j];
	cout<<g[5][5]<<endl;	
	return 0;
}


