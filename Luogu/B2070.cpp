#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        ans += (i % 2 ? 1.0 : -1.0) / i;
    cout << fixed << setprecision(4) << ans << endl;
    return 0;
}