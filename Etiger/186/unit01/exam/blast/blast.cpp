#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, ans, tempans;
multiset<ll> x;
map<int, bool> vst;
struct node
{
    ll Pos, Counter;
};
void bfs(ll s)
{
    vst.clear();
    tempans = x.count(s);
    queue<node> q;
    q.push((node){s, 1});
    vst[s] = true;
    while (!q.empty())
    {
        node temp = q.front();
        q.pop();
        for (ll i = -temp.Counter; i <= temp.Counter; i++)
        {
            ll nx = temp.Pos + i;
            if (nx > 0 && !vst[nx] && x.count(nx) != 0)
            {
                vst[nx] = true;
                tempans += x.count(nx);
                q.push((node){nx, temp.Counter + 1});
            }
        }
    }
}
int main()
{
    freopen("blast.in", "r", stdin);
    freopen("blast.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        x.insert(temp);
    }
    for (multiset<ll>::iterator sit = x.begin(); sit != x.end(); sit++)
    {
        bfs(*sit);
        ans = max(ans, tempans);
    }
    cout << ans << endl;
    return 0;
}