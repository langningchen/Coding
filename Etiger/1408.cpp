#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N], sg[N], ok[N];
void getSG()
{
	sg[n] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		fill(ok, ok + n + 1, 0);
		for (int j = i + 1; j < n; j++)
			for (int k = j; k < n; k++)
				ok[sg[j] ^ sg[k]] = 1;
		int x;
		for (x = 0; ok[x]; x++)
			;
		sg[i] = x;
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	getSG();
	int SG = 0, cnt = 0;
	for (int i = 0; i < n; i++)
		if (a[i] & 1)
			SG ^= sg[i];
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j; k < n; k++)
				if ((SG ^ sg[i] ^ sg[j] ^ sg[k]) == 0)
				{
					cnt++;
					if (cnt == 1)
						cout << i << " " << j << " " << k << endl;
				}
	if (!cnt)
		cout << "-1 -1 -1" << endl;
	cout << cnt << endl;
	return 0;
}
