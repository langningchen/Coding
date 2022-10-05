#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const short OKSet[7] = {1, 4, 9, 16, 25, 36, 49};
ll n;
bool founded = false;
void dfs(ll x, ll y)
{
	//	cout << x << " " << y << endl;
	if (x == 0)
	{
		founded = true;
		cout << y << endl;
		return;
	}
	const short *t = upper_bound(OKSet, OKSet + 7, x);
	//	cout << *t << endl;
	while (t != OKSet)
	{
		t--;
		dfs(x - *t, y + 1);
		if (founded == true)
			break;
	}
}
int main()
{
	freopen("collection.in", "r", stdin);
	freopen("collection-BF.out", "w", stdout);
	cin >> n;
	dfs(n, 0);
	return 0;
}
