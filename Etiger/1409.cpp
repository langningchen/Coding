#include <bits/stdc++.h>
using namespace std;
const int R = 1005;
int SG, n, m, a[R], b[R], sg[R], ok[R];
void getSG()
{
	for (int x = 1; x < R; x++)
	{
		fill(ok, ok + R, 0);
		for (int i = 1; i <= m; i++)
			if (x - b[i] >= 0)
				ok[sg[x - b[i]]] = 1;
		for (int k = 0; k <= 1000; k++)
			if (!ok[k])
			{
				sg[x] = k;
				break;
			}
	}
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> b[i];
	getSG();
	for (int i = 1; i <= n; i++)
		SG ^= sg[a[i]];
	if (SG != 0)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int nSG = (SG ^ sg[a[i]] ^ sg[a[i] - b[j]]);
			if (nSG == 0)
			{
				cout << i << " " << b[j] << endl;
				return 0;
			}
		}
	return 0;
}
