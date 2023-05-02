#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
const int INF = 0x7FFFFFFF;
ll m, n, x[N], q[N], ans;
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    freopen("fix.in", "r", stdin);
    freopen("fix.out", "w", stdout);
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    if (m == 1 || m > n)
    {
        for (int i = 0; i < n; i++)
            ans += x[i];
    }
    else if (m < 2000)
    {
        int c = n;
        while (c >= m)
        {
            sort(x, x + n, cmp);
            ans += x[m - 1];
            for (int i = 0; i < m; i++)
                x[i] -= x[m - 1];
            c--;
        }
        for (int i = 0; i < c; i++)
            ans += x[i];
    }
    else if (1)
    {
        int c = n;
        sort(x, x + n, cmp);
        while (c >= m)
        {
            ans += x[m - 1];
            for (int i = 0; i < m; i++)
                x[i] -= x[m - 1];
            for (int i = m - 1; i >= 0; i--)
                for (int j = i + 1; j < n; j++)
                    if (x[j - 1] < x[j])
                        swap(x[j], x[j - 1]);
            c--;
        }
        for (int i = 0; i < c; i++)
            ans += x[i];
    }
    else
    {
        sort(x, x + n);
        q[0] = x[0];
        for (int i = 1; i < n; i++)
            q[i] = x[i] - x[i - 1];
        int c = n;
        while (c >= m)
        {
            int t = c - m;
            q[t] -= x[t];
            q[t + 1] += q[t];
            for (int i = t; i < c - 1; i++)
                q[i] = q[i + 1];
            while (q[t] < 0)
            {
                swap(q[t - 1], q[t]);
                t--;
                q[t] += q[t + 1];
            }
            c--;
        }
    }
    cout << ans << ".000" << endl;
    return 0;
}