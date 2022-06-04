#include <bits/stdc++.h>
#define N 100005
#define INF 2e9
using namespace std;
int n, d[N], x[N];
int main() {
    while (cin >> x[n])
        n++;
    reverse(x, x + n);
    fill(d, d + n, INF);
    for (int i = 0; i < n; i++)
        *lower_bound(d, d + n, x[i]) = x[i];
    int cnt = lower_bound(d, d + n, INF) - d;
    cout << cnt << endl;
    return 0;
}
