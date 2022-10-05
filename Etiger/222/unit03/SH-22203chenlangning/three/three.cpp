#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m, z[N];
vector<ll> to[N];
map<ll, map<ll, pair<ll, vector<ll>>>> table;
bool Is3()
{
    return n == 3;
}
void Solve3()
{
    if (m == 3)
        cout << 1 << endl;
    else
        cout << 0 << endl;
}
bool Is200()
{
    return n <= 200;
}
void Solve200()
{
    for (int i = 1; i <= m; i++)
    {
        ll x, y;
        cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (size_t j = 0; j < to[i].size(); j++)
        {
            if (to[i][j] < i)
                continue;
            for (size_t k = 0; k < to[to[i][j]].size(); k++)
            {
                if (to[to[i][j]][k] < to[i][j])
                    continue;
                for (size_t l = 0; l < to[to[to[i][j]][k]].size(); l++)
                {
                    if (to[to[to[i][j]][k]][l] == i)
                    {
                        cout << i << " " << to[i][j] << " " << to[to[i][j]][k] << " " << to[to[to[i][j]][k]][l] << endl;
                        ans += max(z[i], max(z[to[i][j]], z[to[to[i][j]][k]]));
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
void Solve()
{
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        table[x][y].first = 1;
        table[y][x].first = 1;
        for (size_t i = 0; i < to[x].size(); i++)
        {
            table[y][to[x][i]].second.push_back(x);
            table[to[x][i]][y].second.push_back(x);
        }
        for (size_t i = 0; i < to[y].size(); i++)
        {
            table[x][to[y][i]].second.push_back(y);
            table[to[y][i]][x].second.push_back(y);
        }
        to[x].push_back(y);
        to[y].push_back(x);
    }
    set<pair<pair<ll, ll>, ll>> s;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (table[i][j].first == 0 || table[i][j].second.size() == 0)
                continue;
            for (size_t k = 0; k < table[i][j].second.size(); k++)
            {
                ll tmp[3] = {i, j, table[i][j].second[k]};
                sort(tmp, tmp + 3);
                s.insert(make_pair(make_pair(tmp[0], tmp[1]), tmp[2]));
            }
        }
    }
    ll ans = 0;
    for (set<pair<pair<ll, ll>, ll>>::iterator it = s.begin(); it != s.end(); it++)
    {
        ans += max(max(z[it->first.first], z[it->first.second]), z[it->second]);
    }
    cout << ans << endl;
}
int main()
{
    freopen("three.in", "r", stdin);
    freopen("three.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    if (Is3())
        Solve3();
    else if (Is200())
        Solve200();
    else
        Solve();
    return 0;
}