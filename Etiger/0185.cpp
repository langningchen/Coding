#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
struct hero
{
	string name;
	int a, b, rp, sum;
};
int n;
hero h[N];
bool cmp(const hero &x, const hero &y)
{
	if (x.sum > y.sum)
		return 1;
	if (x.sum < y.sum)
		return 0;
	if (x.rp > y.rp)
		return 1;
	if (x.rp < y.rp)
		return 0;
	if (x.a > y.a)
		return 1;
	if (x.a < y.a)
		return 0;
	if (x.name < y.name)
		return 1;
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> h[i].name >> h[i].a >> h[i].b >> h[i].rp;
		h[i].sum = h[i].a + h[i].b + h[i].rp;
	}
	sort(h, h + n, cmp);
	for (int i = 0; i < n; i++)
		cout << h[i].name << endl;
	return 0;
}
