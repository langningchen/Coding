#include <bits/stdc++.h>
using namespace std;
int a[4][4], ans = 0;
int main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> a[i][j];
    for (int i = 3; i >= 0; i--)
    {
        ans += a[i][3 - i];
    }
    for (int i = 0; i < 4; i++)
    {
        ans += a[i][3 - i];
    }
    cout << ans << endl;
    return 0;
}
