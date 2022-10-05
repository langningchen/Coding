#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
ll q, famax = 1;
pair<ll, pair<ll, ll>> fa[N];
pair<vector<pair<ll, ll>>, ll> v[N];
void add(ll x, ll y)
{
    famax++;
    fa[famax] = make_pair(x, make_pair(fa[x].second.first + 1, y));
    v[x].first.push_back(make_pair(famax, y));
    v[x].second = -1;
}
ll GetPrefix(ll x, ll y)
{
    ll Answer = 0;
    while (fa[x].second.first > fa[y].second.first)
    {
        Answer ^= fa[x].second.second;
        x = fa[x].first;
    }
    while (fa[x].second.first < fa[y].second.first)
    {
        Answer ^= fa[y].second.second;
        y = fa[y].first;
    }
    while (x != y)
    {
        Answer ^= fa[x].second.second;
        x = fa[x].first;
        Answer ^= fa[y].second.second;
        y = fa[y].first;
    }
    return Answer;
}
ll dfs(ll x, ll prefix)
{
    if (v[x].second != -1)
    {
        return v[x].second ^ prefix;
    }
    ll MaxValue = 0;
    for (vector<pair<ll, ll>>::iterator vit = v[x].first.begin(); vit != v[x].first.end(); vit++)
    {
        ll CurrentValue = dfs(vit->first, 0) ^ vit->second ^ prefix;
        if (CurrentValue > MaxValue)
        {
            MaxValue = CurrentValue;
        }
    }
    v[x].second = MaxValue ^ prefix;
    return MaxValue;
}
int main()
{
    freopen("vashj.in", "r", stdin);
    freopen("vashj.out", "w", stdout);
    fa[1] = make_pair(0, make_pair(1, 0));
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        string Type;
        cin >> Type;
        if (Type == "Vashj")
        {
            ll x, y;
            cin >> x >> y;
            add(x, y);
        }
        else if (Type == "Kael")
        {
            ll a, b;
            cin >> a >> b;
            cout << dfs(b, GetPrefix(a, b)) << " ";
        }
    }
    return 0;
}
z