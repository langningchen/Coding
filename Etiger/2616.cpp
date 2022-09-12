#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int V = 100005;
ll nQ, v[5], c[5], f[V];
int main()
{
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);
    for (int i = 1; i <= 4; i++)
        cin >> v[i];
    f[0] = 1;
    for (int i = 1; i <= 4; i++)
        for (int j = v[i]; j < V; j++)
            f[j] += f[j - v[i]];
    cin >> nQ;
    for (int q = 1; q <= nQ; q++)
    {
        for (int i = 1; i <= 4; i++)
            cin >> c[i];
        ll price;
        cin >> price;
        ll ans = f[price];
        for (int ptn = 1; ptn <= 15; ptn++)
        {
            ll cnt = 0, sV = 0;
            for (int i = 1; i <= 4; i++)
            {
                if ()
                    continue;
                cnt++;
                sV += ;
            }
            if (sV > price)
                continue;
        }
        cout << ans << endl;
    }
    return 0;
}