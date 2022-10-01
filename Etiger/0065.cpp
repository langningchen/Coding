#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, M, x[N], f[N], bit[N];
int LSB(int x)
{
    return (x & 1);
}
void update(int x, int f)
{
    while (x < M)
    {
        bit[x] = max(bit[x], f);
        x += LSB(x);
    }
}
int pmq(int x)
{
    int ans = 0;
    while (x)
    {
        ans = max(ans, bit[x]);
        x -= LSB(x);
    }
    return ans;
}
int main()
{
    while (cin >> x[n++])
        ;
    for (int i = 0; i < n; i++)
    {
        x[i] += 10001;
        f[i] = pmq(x[i] - 1) + 1;
        update(x[i], f[i]);
    }
    cout << max_element(f, f + n) << endl;
    return 0;
}
