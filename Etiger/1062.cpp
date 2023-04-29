#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, p, x[N], y[N];
int main()
{
    freopen("hattrick2.in", "r", stdin);
    freopen("hattrick2.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        y[i] = x[i] = i;
    for (int k = 1; k <= m; k++)
    {
        cin >> p;
        swap(x[p], x[p + 1]);
        swap(y[x[p]], y[x[p + 1]]);
    }
    for (int i = 1; i <= n; i++)
    {
        cout << y[i] << " ";
    }
    return 0;
}
