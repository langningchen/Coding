#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, k, m, f[N];
int main()
{
    freopen("asclepius.in", "r", stdin);
    freopen("asclepius.out", "w", stdout);
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    int cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] > k * m)
        {
            cout << "No" << endl;
            return 0;
        }
        if (f[i] <= m)
            continue;
        if (k > 1)
            cnt += ceil(1.0 * (f[i] - m) / (k - 1));
    }
    if (cnt > m)
        cout << "No" << endl;
    else
        cout << "Yes" << endl;
    return 0;
}
