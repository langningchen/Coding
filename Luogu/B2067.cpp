#include <bits/stdc++.h>
using namespace std;
int m, n, a, ans;
int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        if (a <= m)
            m -= a;
        else
            ans++;
    }
    cout << ans << endl;
    return 0;
}