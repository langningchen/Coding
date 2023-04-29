#include <bits/stdc++.h>
using namespace std;
double ans, x;
int n;
int main()
{
    cin >> x >> n;
    for (int i = 0; i <= n; i++)
        ans += pow(x, i);
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}