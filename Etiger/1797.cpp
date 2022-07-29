#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int k, x[N];
int main()
{
	freopen("idol.in", "r", stdin);
	freopen("idol.out", "w", stdout);
	cin >> k;
	for (int i = 0; i < k; i++)
		cin >> x[i];
	cout << min_element(x, x + k) - x + 1 << ' ' << *min_element(x, x + k) << endl;
	return 0;
}
