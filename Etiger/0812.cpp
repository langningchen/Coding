#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m, rt, nSon[N], dfn[N], low[N], timer;
vector<ll> to[N];
vector<ll> son[N];
void tarjan(ll u, ll fa)
{
	dfn[u] = low[u] = ++timer;
	for (ll i = 0; i < to[u].size(); i++)
	{
		ll v = to[u][i];
		if (v == fa)
			continue;
		if (dfn[v])
		{
			low[u] = min(low[u], dfn[v]);
			continue;
		}
		tarjan(v, u);
		low[u] = min(low[u], low[v]);
		son[u].push_back(v);
		++nSon[u];
	}
}
bool isCut(ll u)
{
	if (u == rt)
		return nSon[rt] > 1;
	if (nSon[u] == 0)
		return 0;
	for (ll i = 0; i < son[u].size(); i++)
	{
		ll v = son[u][i];
		if (low[v] >= dfn[u])
			return 1;
	}
	return 0;
}
int main()
{
	cin >> n >> m;
	for (ll i = 1; i <= m; i++)
	{
		ll u, v;
		cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	tarjan(rt = 1, 0);
	ll nCut = 0;
	for (ll u = 1; u <= n; ++u)
	{
		if (isCut(u))
		{
			nCut++;
			cout << u << endl;
		}
	}
	if (!nCut)
	{
		cout << "perfect" << endl;
	}
	return 0;
}
