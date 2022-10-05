#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, n;
int main()
{
	freopen("snail.in", "r", stdin);
	freopen("snail.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b >> n;
	if (a <= b)
	    cout << "forever" << endl;
	else
	    cout << ceil((n - a) * 1.0 / (a - b)) * 2 + 1 << endl;
	return 0;
}

