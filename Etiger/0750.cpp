#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int v, x[N], j, k;
int main()
{
    freopen("fuli.in", "r", stdin);
    freopen("fuli.out", "w", stdout);
    cin >> j >> k;
    for (int i = 0; i < j; i++)
    {
        cin >> x[i];
    }
    sort(x, x + j);
    for (int i = 0; i < k; i++)
    {
        cin >> v;
        int ub = upper_bound(x, x + j, v) - x;
        cout << ub << endl;
    }
    return 0;
}
