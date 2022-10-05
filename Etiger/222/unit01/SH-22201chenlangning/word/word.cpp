#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2005;
int n, m;
string ans = "";
char a[N][N], t;
set<string> s;
void dfs(int i, int j)
{
#ifdef DEBUG
	cout << i << " " << j << endl;
#endif
	ans.push_back(a[i][j]);
	if (i == n - 1 && j == m - 1)
		s.insert(ans);
	else if (i + 1 < n && j + 1 < m)
	{
		if (a[i + 1][j] == a[i][j + 1])
		{
			dfs(i + 1, j);
			dfs(i, j + 1);
		}
		else if (a[i + 1][j] > a[i][j + 1])
			dfs(i, j + 1);
		else
			dfs(i + 1, j);
	}
	else if (i + 1 < n)
		dfs(i + 1, j);
	else if (j + 1 < m)
		dfs(i, j + 1);
	ans.erase(ans.size() - 1, 1);
}
int main()
{
#ifndef LOCAL
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	scanf("%c", &t);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%c", &a[i][j]);
		scanf("%c", &t);
	}
#ifdef DEBUG
	cout << "INPUT END" << endl;
#endif
	dfs(0, 0);
#ifdef LOCAL
	for (auto i : s)
		cout << i << endl;
	cout << endl;
#endif
	cout << *s.begin() << endl;
	return 0;
	cout << "100%AC" << endl;
}
