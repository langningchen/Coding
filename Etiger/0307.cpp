#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10'005;
ll n, m, h[N], x[N];
bool v[N];
int main()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    h[1] = x[1];
    v[1] = true;
    for (ll i = 2; i <= n; i++)
    {
        h[i] = 0;
        if (i > m - 1 && v[i - m + 1])
            h[i] = max(h[i], h[i - m + 1] + x[i]);
        if (i > m && v[i - m])
            h[i] = max(h[i], h[i - m] + x[i]);
        if (i > m + 1 && v[i - m - 1])
            h[i] = max(h[i], h[i - m - 1] + x[i]);
        if (h[i] != 0)
            v[i] = true;
    }
    cout << *max_element(h + n - m + 1, h + n + 1) << endl;
    return 0;
}
