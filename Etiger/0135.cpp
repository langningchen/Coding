#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, c, w, v, s, f[N];
void bb01(int w, int v) {
    for (int j = c; j >= w; j--)
        f[j] = max(f[j], f[j - w] + v);
}
int main() {
    freopen("knapsack.in","r",stdin);
    freopen("knapsack.out","w",stdout);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> w >> v >> s;
        for (int k = 1; k <= s; s -= k, k *= 2) bb01(k * w, k * v);
        if (s) bb01(s * w, s * v);
    }
    cout << f[c] << endl;
    return 0;
}
