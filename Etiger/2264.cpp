#include <bits/stdc++.h>
using namespace std;
const int N = 1205;
int nC, nW, remain[N], W[N], C[N], sC, sW[N];
bool cmp(int a, int b)
{
	return a > b;
}
bool dfs(int k, int pre)
{
	if (k == 0)
	{
		return 1;
	}
	if (W[k] != W[k + 1])
	{
		pre = 1;
	}
	for (int i = pre; i <= nC; i++)
	{
		if (remain[i] < W[k])
		{
			continue;
		}
		if (remain[i] == remain[i - 1])
		{
			continue;
		}
		remain[i] -= W[k];
		if (dfs(k - 1, i) == 1)
		{
			return 1;
		}
		remain[i] += W[k];
	}
	return 0;
}
bool OK(int k)
{
	if (sC < sW[k])
	{
		return 0;
	}
	for (int i = 1; i <= nC; i++)
	{
		remain[i] = C[i];
	}
	return dfs(k, 1);
}
int main()
{
	freopen("thegreatflood.in", "r", stdin);
	freopen("thegreatflood.out", "w", stdout);
	cin >> nC;
	for (int i = 1; i <= nC; i++)
	{
		cin >> C[i];
	}
	cin >> nW;
	for (int i = 1; i <= nW; i++)
	{
		cin >> W[i];
	}
	sort(C + 1, C + 1 + nC, cmp);
	sort(W + 1, W + 1 + nW);
	for (int i = 1; i <= nC; i++)
	{
		sC += C[i];
	}
	for (int i = 1; i <= nW; i++)
	{
		sW[i] = sW[i - 1] + W[i];
	}
	int ans = 0;
	for (int k = 1; k <= nW; k++)
	{
		if (OK(k))
		{
			ans = k;
		}
		else
		{
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
