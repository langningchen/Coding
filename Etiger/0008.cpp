#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int m, n, a[N];
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += a[i];
        for (int i2 = i; i2 < n; i2++)
        {
            ans += a[i2];
            for (int i3 = i2; i3 < n; i3++)
            {
                ans += a[i3];
                if (ans == m)
                {
                    cout << "Yes" << endl;
                    return 0;
                }
                ans -= a[i3];
            }
            ans -= a[i2];
        }
        ans -= a[i];
    }
    cout << "No" << endl;
    return 0;
}