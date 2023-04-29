#include <bits/stdc++.h>
using namespace std;
int m, k;
int main()
{
    freopen("blindbox3.in", "r", stdin);
    freopen("blindbox3.out", "w", stdout);
    cin >> m >> k;
    cout << fixed << setprecision(6) << (pow(m, k) - 1) * 1.0 / (m - 1) << endl;
    return 0;
}
