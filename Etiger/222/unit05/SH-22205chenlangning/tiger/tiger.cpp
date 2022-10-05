#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 65536;
const int INF = 0x7FFFFFFF;
struct twelve
{
    ll cnt, xs, xe;
} cnt[N];
ll n, k, m, ma, ans;
int main()
{
    freopen("tiger.in", "r", stdin);
    freopen("tiger.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        cnt[x / 12].cnt++;
    }
    for (int i = 0; i < N; i++)
        if (cnt[i].cnt != 0)
        {
            cnt[i].xs = cnt[i].xe = i;
            cnt[m] = cnt[i];
            m++;
        }
    while (m >= k)
    {
        ll mi = INF, miv;
        for (int i = 0; i < m - 1; i++)
            if (cnt[i + 1].xe - cnt[i].xs < mi)
            {
                mi = cnt[i + 1].xe - cnt[i].xs;
                miv = i;
            }
        cnt[miv].cnt += cnt[miv + 1].cnt;
        cnt[miv].xe = cnt[miv + 1].xe;
        for (int j = miv + 1; j < m - 1; j++)
            cnt[j] = cnt[j + 1];
        m--;
    }
    for (int i = 0; i < m; i++)
        ans += cnt[i].xe - cnt[i].xs + 1;
    cout << ans * 12 << endl;
    return 0;
}