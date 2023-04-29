#include <bits/stdc++.h>
using namespace std;
const int N = 5000005;
const int INF = 0x7FFFFFFF;
int n, m, x, y, z, a[N], b[N];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i] - a[i - 1];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> z;
        b[x] += z;
        b[y + 1] -= z;
    }
    int Min = INF;
    for (int i = 1; i <= n; i++)
    {
        b[i] += b[i - 1];
        if (b[i] < Min)
            Min = b[i];
    }
    cout << Min << endl;
    return 0;
}