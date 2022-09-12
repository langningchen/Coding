#include <bits/stdc++.h>
using namespace std;
const int N = 19;
long long n, cnt, W, sW[1 << N], w[N];
bool cmp(int a, int b)
{
	return a > b;
}
bool dfs(int id)
{
	if (id == n + 1)
	{
		return 1;
	}
	for (int p = 1; p <= cnt; p++)
	{
		if (sW[p] + w[id] > W)
		{
			continue;
		}
		sW[p] += w[id];
		if (dfs(id + 1))
		{
			return 1;
		}
		sW[p] -= w[id];
	}
	return 0;
}
int main()
{
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	cin >> n >> W;
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i];
	}
	sort(w + 1, w + 1 + n, cmp);
	int tot = 0;
	for (int i = 1; i <= n; i++)
	{
		tot += w[i];
	}
	for (cnt = 1; cnt <= n; cnt++)
	{
		if (cnt * W < tot)
		{
			continue;
		}
		for (int p = 1; p <= cnt; p++)
		{
			sW[p] = 0;
		}
		if (dfs(1))
		{
			break;
		}
	}
	cout << cnt << endl;
	return 0;
}
