#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
int n, m, vst[N];
vector<int> to[N];
int deg[N];
bool Do()
{
	queue<int> q;
	for (int i = 1; i <= n * 2; i++)
	{
		deg[i] = to[i].size();
		if (to[i].empty())
		{
			return false;
		}
		else if (to[i].size() == 1)
		{
			vst[i] = true;
			q.push(i);
		}
	}
	int Counter = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		int Next = -1;
		Counter++;
		for (vector<int>::iterator vit = to[cur].begin(); vit != to[cur].end(); vit++)
		{
			if (!vst[*vit])
				Next = *vit;
		}
		if (Next == -1)
			continue;
		vst[Next] = 1;
		Counter++;
		for (vector<int>::iterator vit = to[Next].begin(); vit != to[Next].end(); vit++)
		{
			if (!vst[*vit])
			{
				deg[*vit]--;
				if (deg[*vit] < 2)
				{
					q.push(*vit);
					vst[*vit] = 1;
				}
			}
		}
	}
	return (Counter >= n * 2);
}
void ConsoleInit()
{
	for (int j = 1; j <= n * 2; j++)
		to[j].clear();
	memset(vst, 0, sizeof(vst));
}
int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> n >> m;
		ConsoleInit();
		for (int j = 0; j < m; j++)
		{
			int a, b;
			cin >> a >> b;
			b += n;
			to[a].push_back(b);
			to[b].push_back(a);
		}
		if (Do())
		{
			cout << "Renko" << endl;
		}
		else
		{
			cout << "Merry" << endl;
		}
	}
	return 0;
}
