#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
const ll INF = 0x7FFF'FFFF;
ll T, n1, n2, p, c1, c2, d[N];
struct Cover
{
    ll date, num;
};
ll G(ll m)
{
    ll cost = 0;
    deque<Cover> q1, q2;
    for (ll i = 1; i <= T; i++)
    {
        ll demand = d[i];
        ll cnt = min(demand, m);
        demand -= cnt;
        m -= cnt;
        if (i - n2 > 0)
            q2.push_back((Cover){i - n2, d[i - n2]});
        while (!q2.empty())
        {
            if (q2.front().date + n1 > i)
                break;
            q1.push_back(q2.front());
            q2.pop_front();
        }
        while (!q1.empty() && demand)
        {
            cnt = min(demand, q1.front().num);
            cost += cnt * c1;
            demand -= cnt;
            q1.front().num -= cnt;
            if (!q1.front().num)
                q1.pop_front();
        }
        while (!q2.empty() && demand)
        {
            cnt = min(demand, q2.back().num);
            cost += cnt * c2;
            demand -= cnt;
            q2.back().num -= cnt;
            if (!q2.back().num)
                q2.pop_back();
        }
        if (demand)
            return INF;
    }
    return cost;
}
ll F(ll m)
{
    return G(m) + m * p;
}
int main()
{
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    cin >> T >> n1 >> n2 >> c1 >> c2 >> p;
    for (ll i = 1; i <= T; i++)
        cin >> d[i];
    int l = 0;
    int r = T * 50;
    ll ans = r * p;
    for (int i = l; i <= r; i++)
        ans = min(ans, F(i));
    cout << ans << endl;
    return 0;
}
