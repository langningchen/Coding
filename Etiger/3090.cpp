#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll T, n, diff, h[N];
ll solve()
{
    ll cnt = 0;
    if (n == 1)
        return 0;
    if (n == 2)
    {
        if (h[1] == h[2])
            return 0;
        else
            return -1;
    }
    if (h[1] > h[2])
        return -1;
    for (ll i = 1; i <= n - 2; i++)
    {
        diff = h[i + 1] - h[i];
        if (diff < 0)
            continue;
        h[i + 1] -= diff;
        h[i + 2] -= diff;
        if (h[i + 2] < 0)
            return -1;
        cnt += 2 * diff;
    }
    if (h[n - 1] < h[n])
        return -1;
    for (ll i = n; i >= 3; i--)
    {
        diff = h[i - 1] - h[i];
        if (!diff)
            continue;
        h[i - 1] -= diff;
        h[i - 2] -= diff;
        cnt += 2 * diff;
    }
    if (h[1] > h[2])
        return -1;
    return cnt;
}
int main()
{
    freopen("zoo.in", "r", stdin);
    freopen("zoo.out", "w", stdout);
    cin >> T;
    while (T-- > 0)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> h[i];
        cout << solve() << endl;
    }
    return 0;
}