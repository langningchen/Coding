#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int INF = 0x7FFF'FFFF;
int n, lis[N], lds[N], x[N], ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (x[i] > x[j])
            {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (x[i] > x[j])
            {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    for (int i = 0; i < n; i++)
        ans = max(ans, lis[i] + lds[i] + 1);
    ans = n - ans;
    cout << ans << endl;
    return 0;
}
