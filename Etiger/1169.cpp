#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 501;
typedef long long ll;
ll c, n, W, V, w[N], v[N], f[N][N], p[N], vi, pi, wi;
int main() {
    cin >> n >> V >> W;
    for(ll i = 1; i <= n; i++)
        cin >> v[i];
    for(ll i = 1; i <= n; i++)
        cin >> p[i];
    for(ll i = 1; i <= n; i++)
        cin >> w[i];
    for(ll i = 1; i <= n; i++)
        for(ll j = v[i]; j <= V; j++)
            for(ll k = w[i]; k <= W; k++)
                f[j][k] = max(f[j][k], f[j - v[i]][k - w[i]] + p[i]);
//    for(ll i = 0; i <= V; i++) {
//        for(ll j = 0; j <= W; j++)
//            cout << f[i][j] << " ";
//        cout << endl;
//    }
//    for(ll i = 0; i <= n; i++)
//        cout << w[i] << " ";
//    cout << endl;
//    for(ll i = 0; i <= n; i++)
//        cout << v[i] << " ";
//    cout << endl;
//    for(ll i = 0; i <= n; i++)
//        cout << p[i] << " ";
//    cout << endl;
    cout << f[V][W] << endl;
    return 0;
}
