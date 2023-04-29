#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
int x[N], k, n;
multiset<int> s;
int main()
{
	freopen("xjj.in", "r", stdin);
	freopen("xjj.out", "w", stdout);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> x[i];
	}
	for (int i = 0; i < k; i++)
		s.insert(x[i]);
	for (int i = k; i < n + 1; i++)
	{
		cout << *s.begin() << " ";
		multiset<int>::iterator pos = s.find(x[i - k]);
		s.erase(pos);
		s.insert(x[i]);
	}
	cout << endl;
	return 0;
}
