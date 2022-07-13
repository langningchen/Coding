#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll n, len, x[N];
int main()
{
    freopen("noodle1.in", "r", stdin);
    freopen("noodle1.out", "w", stdout);
    cin >> n >> len;
    for (ll i = 0; i < n; i++)
        cin >> x[i];
    ll cnt = 0;
    for (ll i = 0; i < n; i++)
        cnt += x[i] / len;
    cout << cnt << endl;
    return 0;
}
