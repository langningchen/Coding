#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int c, n, w, v, f[N];
int main()
{
    cin >> c >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> w >> v;
        for (int j = c; j >= w; j--)
            f[j] = max(f[j], f[j - w] + v);
    }
    cout << f[c] << endl;
    return 0;
}
