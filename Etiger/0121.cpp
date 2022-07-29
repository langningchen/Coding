#include <bits/stdc++.h>
using namespace std;
int n;
map<int, int> m;
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		m[num]++;
	}
	for (map<int, int>::iterator mit = m.begin(); mit != m.end(); mit++)
		cout << mit->first << " " << mit->second << endl;
	return 0;
}