#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
int n, m, x[N], i, j;
int main()
{
    cin >> n >> m >> x[i];
    for (int k = 1; k < n; k++)
    {
        cin >> x[k];
        x[k] = x[k - 1] + x[k];
    }
    for (int k = 0; k < m; k++)
    {
        cin >> i >> j;
        cout << x[j - 1] - x[i - 2] << " ";
    }
    return 0;
}
