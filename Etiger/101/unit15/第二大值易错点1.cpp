#include<iostream>
#include<set>
using namespace std;
int main() {
	multiset<int> s;
	s.insert(9); s.insert(9);
	s.insert(7); s.insert(6); 
	int x=*(s.rbegin());
	s.erase(x);
	int ans=*(s.rbegin());
	cout<<ans<<endl;
	return 0;
}


