#include <bits/stdc++.h>
using namespace std;
const long long N = 10000005;
long long n, m, sqrtn, a[N], b[N], bs[N];
long long max2(long long x, long long y)
{
    long long sum = a[x];
    if (b[x] == b[y])
    {
        return (*max_element(a + x, a + y + 1));
    }
    for (long long i = x; b[i] == b[x]; i++)
    {
        sum = max(sum, a[i]);
    }
    for (long long i = b[x] + 1; i <= b[y] - 1; i++)
    {
        sum = max(sum, bs[i]);
    }
    for (long long i = y; b[i] == b[y]; i--)
    {
        sum = max(sum, a[i]);
    }
    return sum;
}
int main()
{
    cin >> n >> m;
    for (long long i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sqrtn = sqrt(n);
    for (long long i = 1; i <= n; i++)
    {
        b[i] = (i - 1) / sqrtn + 1;
    }
    for (long long i = 1; i <= b[n]; i++)
    {
        bs[i] = *max_element(a + i * sqrtn - sqrtn + 1, a + i * sqrtn + 1);
    }
    for (long long i = 0; i < m; i++)
    {
        long long x, y;
        cin >> x >> y;
        cout << max2(x, y) << endl;
    }
    return 0;
}
