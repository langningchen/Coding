#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
int n, m, top, h[N], l[N], r[N], st[N];
char ch[N][N];
ll ans;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> ch[i][j];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            h[j] = ch[i][j] == '*' ? 0 : h[j] + 1;
        top = 0;
        for (int i = 1; i <= m; i++)
        {
            while (top > 0 && h[i] < h[st[top]])
            {
                r[st[top]] = i;
                top--;
            }
            top++;
            st[top] = i;
        }
        while (top > 0)
        {
            r[st[top]] = m + 1;
            top--;
        }
        for (int i = m; i >= 1; i--)
        {
            while (top > 0 && h[i] <= h[st[top]])
            {
                l[st[top]] = i;
                top--;
            }
            top++;
            st[top] = i;
        }
        while (top > 0)
        {
            l[st[top]] = 0;
            top--;
        }
        for (int i = 1; i <= m; i++)
            ans += (i - l[i]) * (r[i] - i) * h[i];
    }
    cout << ans << endl;
    return 0;
}