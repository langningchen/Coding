#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
ll n, ans, t, len;
vector<pair<int, pll>> ren;
set<pll> waiting;
int main()
{
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t >> len;
        ren.push_back(make_pair(t, make_pair(i, len)));
    }
    ll cur_end;
    int next_id = 1;
    sort(ren.begin(), ren.end());
    cur_end = ren[0].first + ren[0].second.second;
    while (next_id < n || waiting.size() > 0)
    {
        while (next_id < n && ren[next_id].first <= cur_end)
        {
            waiting.insert(make_pair(ren[next_id].second.first, next_id));
            next_id++;
        }
        if (waiting.size() == 0 && next_id < n)
        {
            cur_end = ren[next_id].first + ren[next_id].second.second;
            next_id++;
        }
        else if (waiting.size() > 0)
        {
            set<pll>::iterator it = waiting.begin();
            ans = max(ans, cur_end - ren[it->second].first);
            cur_end += ren[it->second].second.second;
            waiting.erase(it);
        }
    }
    cout << ans << endl;
    return 0;
}