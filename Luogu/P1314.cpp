#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
int n, m, x, y, mid, l[N], r[N], w[N], v[N];
ll W, S, sum, sv[N], sw[N];
int main()
{
    cin >> n >> m >> S;
    W = S;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> v[i];
        y = max(y, w[i]);
    }
    x = 1;
    y++;
    for (int i = 1; i <= m; i++)
        cin >> l[i] >> r[i];
    while (x < y)
    {
        memset(sv, 0, sizeof(sv));
        memset(sw, 0, sizeof(sw));
        mid = (x + y) >> 1;
        sum = 0;
        for (int i = 1; i <= n; i++)
            if (w[i] >= mid)
            {
                sw[i] = sw[i - 1] + 1;
                sv[i] = sv[i - 1] + v[i];
            }
            else
            {
                sw[i] = sw[i - 1];
                sv[i] = sv[i - 1];
            }
        for (int i = 1; i <= m; i++)
            sum += (ll)(sw[r[i]] - sw[l[i] - 1]) * (sv[r[i]] - sv[l[i]] - 1);
        if (sum == S)
        {
            W = 0;
            break;
        }
        W = min(W, abs(sum - S));
        if (sum <= S)
            y = mid;
        else if (sum > S)
            x = mid + 1;
    }
    cout << W << endl;
    return 0;
}