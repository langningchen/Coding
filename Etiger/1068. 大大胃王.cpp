#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int n, a, b, c, h[1001];
int main() {
    freopen("stomach.in","r",stdin);
    freopen("stomach.out","w",stdout);
    cin >> n >> a >> b >> c;
    h[0] = 0;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1];
        if (i >= a) h[i] = max(h[i], h[i - a] + a);
        if (i >= b) h[i] = max(h[i], h[i - b] + b);
        if (i >= c) h[i] = max(h[i], h[i - c] + c);
    }
    cout << h[n] << endl;
    return 0;
}
