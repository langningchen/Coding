#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, timer, nGroup, nC;
int dfn[N], iGrp[N], x[N], minCircleID[N];
void move(int u)
{
	dfn[u] = ++timer;
	iGrp[u] = nGroup;
	int v = x[u];
	if (!dfn[v])
	{
		move(v);
		return;
	}
	if (iGrp[v] < iGrp[u])
	{
		return;
	}
	nC++;
	minCircleID[nC] = u;
	for (; v != u; v = x[v])
	{
		minCircleID[nC] = min(minCircleID[nC], v);
	}
}
void print(int u)
{
	cout << u;
	for (int v = x[u]; v != u; v = x[v])
	{
		cout << " " << v;
	}
	cout << endl;
}
int main()
{
	freopen("base.in", "r", stdin);
	freopen("base.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> x[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i])
		{
			++nGroup;
			move(i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i])
		{
			++nGroup;
			move(i);
		}
	}
	cout << nC << endl;
	sort(minCircleID + 1, minCircleID + nC + 1);
	for (int k = 1; k <= nC; k++)
	{
		print(minCircleID[k]);
	}
	return 0;
}
