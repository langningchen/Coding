#include<iostream>
using namespace std;
char p[3][3];
int main(){
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			cin>>p[i][j];
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			if(p[i][j]=='W'||p[i][j]=='B')
				cout<<i<<' '<<j<<' '<<p[i][j]<<endl; 
	return 0;
} 


