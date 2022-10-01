#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll T;
    cin >> T;
    for (ll i = 0; i < T; i++) {
        ll x, y, z;
        cin >> x >> y >> z;
        if (x > z) cout << "Merry" << endl;
        else if ((2ll * z - x - 1) * x / 2ll + z - x >= y) cout << "Renko" << endl;
        else cout << "Merry" << endl;
    }
    return 0;
}
