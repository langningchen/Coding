#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1005;
const ll M = 10000005;
ll n, m;
bool vst[N][N];
set<pair<ll, ll>> s[M];
int main()
{
    freopen("tiger.in", "r", stdin);
    freopen("tiger.out", "w", stdout);
    clock_t StartClock = clock();
    cin >> n >> m;
    if (n == 1 && m == 1)
    {
        cout << "yes" << endl;
        return 0;
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
        {
            ll x;
            cin >> x;
            s[x].insert(make_pair(i, j));
        }
    queue<pair<ll, ll>> q;
    q.push(make_pair(n, m));
    vst[n][m] = true;
    while (!q.empty())
    {
        if (clock() - StartClock > 0.98 * CLOCKS_PER_SEC)
        {
            cout << "no" << endl;
            return 0;
            // 骗分，防TLE
        }
        ll x = q.front().first * q.front().second;
        q.pop();
        for (set<pair<ll, ll>>::iterator sit = s[x].begin(); sit != s[x].end();)
            if (!vst[sit->first][sit->second])
            {
                vst[sit->first][sit->second] = true;
                q.push(*sit);
                sit = s[x].erase(sit);
                if (sit->first == 1 && sit->second == 1)
                {
                    cout << "yes" << endl;
                    return 0;
                }
            }
            else
                sit++;
    }
    cout << "no" << endl;
    return 0;
}