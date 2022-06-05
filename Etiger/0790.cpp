#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
typedef long long ll;
ll countk(ll x, ll k) {
    ll cnt = 0;
    do {
        if (x % 10 == k) cnt++;
        x /= 10;
    } while(x);
    return cnt;
}
int main() {
//    freopen("gls.in","w",stdout);
    freopen("gls.in","r",stdin);
    freopen("gls.out","w",stdout);
    ll s, ans = 0;
    cin >> s;
    for (ll i = 1; i <= s; i++)
        if(countk(i, 3) == 0 && countk(i, 8) == 0)
            ans++;
    cout << ans << endl;
    return 0;
}
