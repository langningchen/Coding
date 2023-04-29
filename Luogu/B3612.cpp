#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, a[N], s[N];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << s[y] - s[x - 1] << endl;
    }
    return 0;
}
