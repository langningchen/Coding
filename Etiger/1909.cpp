#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
const int M = 1005;
const int INF = 0x7FFF'FFFF;
ll n, a[N], b[N], s[M], ans;
int main()
{
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        s[a[i]]++;
        s[b[i]]--;
    }
    for (int i = 0; i < n; i++)
    {
        s[a[i]]--;
        s[b[i]]++;
        ll temp = 0;
        ll now = 0;
        for (int j = 0; j < M; j++)
        {
            temp += s[j];
            if (temp > 0)
                now++;
        }
        if (now > ans)
            ans = now;
        s[a[i]]++;
        s[b[i]]--;
    }
    cout << ans << endl;
    return 0;
}
