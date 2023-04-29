#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const int INF = 0x7FFF'FFFF;
ll n, ans = -INF, x[N];
ll reach(int start, bool goleft)
{
    ll last = start;
    ll r = 1;
    ll dir = 0;
    while (last > 0 && last < n - 1)
    {
        if (goleft)
            dir = -1;
        else
            dir = 1;
        ll next = last;
        while (next + dir >= 0 && next + dir < n && abs(x[next + dir] - x[last]) <= r)
            next += dir;
        if (next == last)
            break;
        last = next;
        r++;
    }
    return last;
}
int main()
{
    freopen("blast.in", "r", stdin);
    freopen("blast.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
    {
        ll left = reach(i, true);
        ll right = reach(i, false);
        ll len = right - left + 1;
        if (len > ans)
            ans = len;
    }
    cout << ans << endl;
    return 0;
}
