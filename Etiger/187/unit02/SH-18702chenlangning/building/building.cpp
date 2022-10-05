#include <bits/stdc++.h>
using namespace std;
const int N = 250005;
const int M = 1000000005;
const int MOD = 1000000009;  
int n, d, w[N], ans;
bool vst[M];
void dfs(int x)
{
	if (x == n)
	{
		ans = (ans + 1) % MOD;
		return;
	}
	vst[x] = true;
	int i = x;
	while (w[i] < w[x] + d && i < n)
		i++;
	for (; i >= 0; i--)
		if (!vst[i])
			dfs(i);
	vst[x] = false;
}
int main()
{
	freopen("building.in", "r", stdin);
	freopen("building.out", "w", stdout);
	cin >> n >> d;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	sort(w, w + n);
	dfs(0);
	cout << ans << endl;
	return 0;
}
