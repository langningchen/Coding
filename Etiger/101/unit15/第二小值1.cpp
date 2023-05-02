#include<iostream>
#include<set>
using namespace std;
int main() {
	multiset<int> s;
	s.insert(9); s.insert(8);
	s.insert(7); s.insert(6); 
	s.erase(s.begin());
	int ans=*(s.begin());
	cout<<ans<<endl;
	return 0;
}

