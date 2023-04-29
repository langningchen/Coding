#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int l, m, a[N], c;
int main()
{
    cin >> l >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        for (int j = u; j <= v; j++)
        {
            a[j] = true;
        }
    }
    for (int i = 0; i <= l; i++)
        if (!a[i])
            c++;
    cout << c << endl;
    return 0;
}