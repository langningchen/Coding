#include <bits/stdc++.h>
using namespace std;
int n, x, m, ans, x_xianyou;
double n_zhang, n_xian;
int main()
{
	cin >> n >> x >> m;
	x_xianyou = x;
	n_xian = n;
	while (1)
	{
		if (x_xianyou >= n_xian)
		{
			cout << ans << endl;
			break;
		}
		if (n_zhang > m)
		{
			cout << "Mission Impossible" << endl;
			break;
		}
		n_zhang = n_xian * 0.01;
		n_xian += n_zhang;
		x_xianyou += m;
		ans++;
	}
	return 0;
}
