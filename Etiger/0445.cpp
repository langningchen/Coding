#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b;
int main() {
	freopen("kai.in", "r", stdin);
	freopen("kai.out", "w", stdout);
	cin >> a >> b;
    if (a < b) swap(a, b);
	cout << a * b - a - b << endl;
	return 0;
}

