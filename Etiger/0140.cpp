#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll G = 19;
const ll N = 39;
const ll MAXV = 209;
ll c, n, g, f[MAXV];
vector<ll> w[G], v[G]; 
int main() {
    cin >> c >> n >> g;
    for (ll i = 1; i <= n; i++) {
        ll ww, vv, p;
        cin >> ww >> vv >> p;
        w[p].push_back(ww);
        v[p].push_back(vv);
    }
    for (ll i = 0; i <= g; i++)
        for (ll j = c; j >= 0; j--)
            for (ll k = 0; k < w[i].size(); k++)
                if (j >= w[i][k])
                   f[j] = max(f[j], f[j - w[i][k]] + v[i][k]);
    cout << f[c] << endl;
    return 0;
}
