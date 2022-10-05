#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20005;
const int INF = 0x7FFFFFFF;
int n, m, a, f[N];
int root(int x)
{
    return ((f[x] == x) ? x : root(f[x]));
}
int main()
{
    freopen("sylvanas.in", "r", stdin);
    freopen("sylvanas.out", "w", stdout);
    cin >> n >> m;
    a = m;
    for (int i = 0; i < n; i++)
        f[i] = i;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
    }
    cout << m << endl;
    return 0;
}