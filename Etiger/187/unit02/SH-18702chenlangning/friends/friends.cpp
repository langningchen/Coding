#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int m, n, x[N];
int main()
{
	freopen("friends.in", "r", stdin);
	freopen("friends.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> x[i];
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		if (a > b)
			swap(a, b);
		int Start = a, End = a, Answer = 0;
		set<int> Haved;
		while (End != b + 1)
		{
			if (Haved.count(x[End]))
			{
				do
				{
					Start++;
				} while (x[Start - 1] != x[End]);
			}
			Haved.insert(x[End]);
			End++;
			Answer = max(Answer, End - Start);
			//			cout << Start << " " << End << " " << End - Start << endl;
		}
		cout << Answer << endl;
	}
	return 0;
}
