#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, a[N];
int main()
{
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int mx = *max_element(a + 1, a + n + 1);
    int mn = *min_element(a + 1, a + n + 1);
    cout << mx - mn << endl;
    return 0;
}