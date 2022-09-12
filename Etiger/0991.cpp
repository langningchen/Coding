#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long n, m, x[N];
int main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    sort(x + 1, x + 1 + n);
    long long ans = 0;
    int i = 1, j = n;
    while (i < j)
    {
        while (i < j && x[i] + x[j] < m)
            ++i;
        ans += j - i;
        --j;
    }
    cout << ans << endl;
    return 0;
}
