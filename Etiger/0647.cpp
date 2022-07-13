#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int n, m, OK = 0, cnt[N];
bool in[N];
long double d[N], r;
vector<int> to[N];
vector<long double> w[N];
map<string, int> id;
int spfa()
{
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		q.push(i);
		d[i] = in[i] = cnt[i] = 1;
	}
	while (!q.empty())
	{
		int v, u = q.front();
		q.pop();
		in[u] = 0;
		for (int i = 0; i < to[u].size(); i++)
		{
			if (d[v = to[u][i]] < d[u] * w[u][i])
			{
				d[v] = d[u] * w[u][i];
				if (!in[v])
				{
					in[v] = 1;
					cnt[v]++;
					q.push(v);
					if (cnt[v] > n)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
int main()
{
	freopen("arbitrage.in", "r", stdin);
	freopen("arbitrage.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		id[s] = i;
	}
	for (int i = 0; i < m; i++)
	{
		string a, c;
		double b;
		cin >> a >> b >> c;
		to[id[a]].push_back(id[c]);
		w[id[a]].push_back(b);
	}
	if (spfa())
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	return 0;
}
