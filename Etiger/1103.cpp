#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 1029;
short mp[N], n, m, cntBit[M], f[8][M][M];
bool OK(int i, int x)
{
	return !(mp[i] & x) && !(x & (x >> 1)) && !(x & (x >> 2));
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char ch;
			cin >> ch;
			mp[i] = (mp[i] << 1) + (ch == 'H');
		}
	}
	int nPtn = (1 << m);
	for (int a = 1; a < nPtn; a++)
	{
		cntBit[a] = 1 + cntBit[a & (a - 1)];
	}
	for (int a = 0; a < nPtn; a++)
	{
		if (OK(1, a))
		{
			f[1][a][0] = cntBit[a];
		}
	}
	for (int a = 0; a < nPtn; a++)
	{
		if (OK(2, a))
		{
			for (int b = 0; b < nPtn; b++)
			{
				if (OK(1, b))
				{
					if (a & b)
					{
						continue;
					}
					f[2][a][b] = cntBit[a] + f[1][b][0];
				}
			}
		}
	}
	for (int i = 3; i <= n; i++)
	{
		for (int a = 0; a < nPtn; a++)
		{
			if (OK(i, a))
			{
				for (int b = 0; b < nPtn; b++)
				{
					if (OK(i - 1, b))
					{
						if (a & b)
						{
							continue;
						}
						for (int c = 0; c < nPtn; c++)
						{
							if (OK(i - 2, c))
							{
								if ((a & c) || (b & c))
								{
									continue;
								}
								f[i % 3][a][b] = max(
									f[i % 3][a][b],
									(short)(f[(i - 1) % 3][b][c] + cntBit[a]));
							}
						}
					}
				}
			}
		}
	}
	short ans = 0;
	for (int a = 0; a < nPtn; a++)
	{
		for (int b = 0; b < nPtn; b++)
		{
			ans = max(ans, f[n % 3][a][b]);
		}
	}
	cout << ans << endl;
	return 0;
}
