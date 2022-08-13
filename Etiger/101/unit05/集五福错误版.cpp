#include<iostream>
#include<algorithm>
using namespace std;
const int R=6;
int main(){
	int cnt[R],n,x;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>x;
		cnt[x]++;
	}
	int ans=*min_element(cnt+1,cnt+R);
	cout<<ans<<endl;
	return 0;
}

