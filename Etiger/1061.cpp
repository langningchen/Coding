#include <bits/stdc++.h>
using namespace std;
int n, m, p;
int main()
{
    freopen("hattrick1.in", "r", stdin);
    freopen("hattrick1.out", "w", stdout);
    cin >> n >> m;
    int ans = 1;
    for (int k = 1; k <= m; k++)
    {
        cin >> p;
        if (p == ans)
            ans = p + 1;
        else if (p + 1 == ans)
            ans = p;
    }
    cout << ans << endl;
    return 0;
}
