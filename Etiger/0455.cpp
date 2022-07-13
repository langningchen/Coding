#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int INF = 0x7FFFFFFF;
int n, d[N], x[N];
int main()
{
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
