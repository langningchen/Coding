#include <bits/stdc++.h>
using namespace std;
const int N = 1000001;
int ans[N + 5];
int a[N + 5];
int main() {
	a[1] = a[2] = 1;
	ans[1] = 1;
	ans[2] = 2;
	for (int i = 3; i <= N; i++) {
		a[i] = (a[i - 1] + a[i - 2]) % 9;
		ans[i] = (ans[i - 1] + a[i]) % 9;
		cout << ans[i] << " ";
	}
    int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << ans[n] << endl;
	}
	return 0;
}

/*
·¨2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 24;
int ans[N] = {0, 1, 2, 4, 7, 3, 2, 6, 0, 7, 8, 7, 7, 6, 5, 3, 0, 4, 5, 1, 7, 0, 8, 0};
ll a[1000005];
int main() {
	ll T;
	cin >> T;
	while (T--) {
		ll n;
		cin >> n;
		cout << ans[n % N] << endl;
	}
	return 0;
}
*/
