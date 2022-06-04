#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 200005;
ll n, x, cbit[N];
ll LSB(ll i) {return i & (-i);}
void add(ll i) {
    while (i <= N) {
        cbit[i]++, i += LSB(i);
    }
}
ll psq(ll i) {
    ll sum = 0;
    while (i)
        sum = sum + cbit[i], i -= LSB(i);
    return sum;
}
int main() {
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> x;
        x++;
        add(x);
        cout << i - psq(x) + 1 << " ";
    }
    return 0;
}
