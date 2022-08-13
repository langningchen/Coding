#include<iostream> 
using namespace std;
int n,yh[10][10];
int main(){
	cin>>n;
	yh[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++)
			yh[i][j]=yh[i-1][j-1]+yh[i-1][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			cout<<yh[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}


