#include <bits/stdc++.h>
#define N 1005
#define INF 2e9
using namespace std;
int n, d[N], x[N], cnt;
int main() {
    while (cin >> x[n])
        n++;
    fill(d, d + n, INF);
    for (int i = 0; i < n; i++)
        *upper_bound(d, d + n, -x[i]) = -x[i];
    cnt = lower_bound(d, d + n, INF) - d;
    cout << cnt << endl;
    fill(d, d + n, INF);
    for (int i = 0; i < n; i++)
        *lower_bound(d, d + n, x[i]) = x[i];
    cnt = lower_bound(d, d + n, INF) - d;
    cout << cnt << endl;
    return 0;
}
