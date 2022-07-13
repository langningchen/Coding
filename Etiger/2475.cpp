#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, nE, nC, hd[N], p[N], dfn[N], timer;
vector<int> circle[N];
struct edge
{
	int to, nxt;
};
edge e[N * 2];
void add(int u, int v)
{
	e[++nE] = (edge){v, hd[u]};
	hd[u] = nE;
}
void dfs(int u, int fa)
{
	p[u] = fa;
	dfn[u] = ++timer;
	for (int i = hd[u]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (!dfn[v])
		{
			dfs(v, u);
			continue;
		}
		if (dfn[v] < dfn[u])
		{
			continue;
		}
		nC++;
		circle[nC].push_back(u);
		for (; v != u; v = p[v])
		{
			circle[nC].push_back(v);
		}
	}
}
void print(vector<int> &C)
{
	int len = C.size();
	int ID = 0;
	for (int i = 0; i < len; i++)
	{
		if (C[i] < C[ID])
		{
			ID = i;
		}
	}
	cout << C[ID];
	int LID = (ID == 0 ? len : ID) - 1;
	int RID = (ID == len - 1 ? -1 : ID) + 1;
	int delta;
	delta = (C[LID] < C[RID] ? -1 : 1);
	for (int i = 1; i < len; i++)
	{
		ID += delta;
		if (ID == -1)
		{
			ID = len - 1;
		}
		else if (ID == len)
		{
			ID = 0;
		}
		cout << " " << C[ID];
	}
	cout << endl;
}
int main()
{
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		add(i, x);
		add(x, i);
	}
	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i])
		{
			dfs(i, 0);
		}
	}
	cout << nC << endl;
	sort(circle + 1, circle + nC + 1);
	for (int k = 1; k <= nC; k++)
	{
		print(circle[k]);
	}
	return 0;
}
