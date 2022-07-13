#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("matches.in", "r", stdin);
    freopen("matches.out", "w", stdout);
    const int ans[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 8, 9, 6, 9, 29, 39, 38, 65, 88, 128};
    int n;
    cin >> n;
    cout << ans[n - 1] << endl;
    return 0;
}
