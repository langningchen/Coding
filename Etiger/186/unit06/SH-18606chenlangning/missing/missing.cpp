#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2005;
const int INF = 0x7FFFFFFF;
const int MOD = 2020;
ll n, m, v[N];
map<ll, set<set<ll>>> Data;
set<ll> Temp1;
ll Temp2;
void dfs(ll x)
{
    if (x == n)
    {
        if (Temp2 <= m)
            Data[Temp2].insert(Temp1);
        return;
    }
    Temp1.insert(x);
    Temp2 += v[x];
    if (Temp2 <= m)
        dfs(x + 1);
    Temp2 -= v[x];
    Temp1.erase(x);
    dfs(x + 1);
}
int main()
{
    freopen("missing.in", "r", stdin);
    freopen("missing.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    dfs(0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ll Counter = 0;
            for (set<set<ll>>::iterator sit = Data[j].begin(); sit != Data[j].end(); sit++)
                if (sit->count(i) == 0)
                    Counter = (Counter + 1) % MOD;
            cout << Counter;
            if (j == m)
                cout << endl;
            else
                cout << " ";
        }
    }
    return 0;
}