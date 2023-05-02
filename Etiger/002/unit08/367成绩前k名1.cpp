#include<iostream> 
using namespace std;
const int SIZE=10009;
int x[SIZE];
int n,k;
int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>x[i];
	for(int i=n-1;i>=n-k;i--)
		cout<<x[i]<<" ";	
	return 0;
}



