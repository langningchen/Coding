#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    int a[4][4], ans = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> a[i][j];
    for (int i = 3; i >= 0; i--)
    {
        int j = 3 - i;
        ans += a[i][j];
    }
    for (int i = 0; i < 4; i++)
    {
        int j = 3 - i;
        ans += a[i][j];
    }
    cout << ans << endl;
    return 0;
}
