#include <bits/stdc++.h>
using namespace std;
const int N = 305;
struct people
{
	int yw, sx, yy, zf, bh;
};
people p[N];
bool cmp(const people &x, const people &y)
{
	if (x.zf > y.zf)
		return 1;
	if (x.zf < y.zf)
		return 0;
	if (x.yw > y.yw)
		return 1;
	if (x.yw < y.yw)
		return 0;
	if (x.bh < y.bh)
		return 1;
	if (x.bh > y.bh)
		return 0;
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].yw >> p[i].sx >> p[i].yy;
		p[i].bh = i;
		p[i].zf = p[i].yw + p[i].sx + p[i].yy;
	}
	sort(p, p + n, cmp);
	for (int i = 0; i < 5; i++)
		cout << p[i].bh + 1 << ' ' << p[i].zf << endl;
	return 0;
}
