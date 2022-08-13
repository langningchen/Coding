#include<bits/stdc++.h>
using namespace std;
const int N=1000009;
int n,x[N];
int partition(int a,int b){
	int pivot=x[a];
	int i=a+1;
	for(int j=a+1;j<=b;j++)
		if(x[j]<pivot) 
			swap(x[i++],x[j]);
	swap(x[a],x[i-1]);	
	return i-1;
}
void qsort(int a,int b){
	if(a>=b)return;
	int p=partition(a,b); 
	qsort(a,p);
	qsort(p+1,b);
}
int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&x[i]);
    qsort(0,n-1);
	for(int i=0;i<n;i++)printf("%d ",x[i]);
    return 0;
}
