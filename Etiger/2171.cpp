#include <bits/stdc++.h>
using namespace std;
const unsigned int N = 17;
const unsigned int INF = 0xFFFFFFFF;
unsigned int n, nPtn, W, ptn[1 << N], f[N], sW[1 << N], mT[1 << N], w[N], t[N];
\r int main()
{
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	cin >> W >> n;
	nPtn = 1 << n;
	for (unsigned int i = 0; i < n; i++)
	{
		cin >> t[i] >> w[i];
	}
	\r unsigned int nOK = 0;
	for (unsigned int i = 0; i < nPtn; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			if (i & (1 << j))
			{
				sW[i] += w[j];
				mT[i] = max(mT[i], t[j]);
			}
		}
		if (sW[i] > W)
		{
			continue;
		}
		ptn[nOK] = i;
		nOK++;
	}
	\r for (unsigned int i = 1; i < nPtn; i++)
	{
		f[i] = INF;
		for (unsigned int j = 0; j < nOK; j++)
		{
			unsigned int v = ptn[j];
			if ((i | v) != i)
			{
				continue;
			}
			f[i] = min(f[i], f[i - v] + mT[v]);
		}
	}
	\r
			cout
		<< f[nPtn - 1] << endl;
	return 0;
}
