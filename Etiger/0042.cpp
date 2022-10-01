#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int n, m, sum, p[N], num[N], ans = 0;
bool isPrime(int x)
{
    if (x <= 1)
        return 0;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;
    return 1;
}
void print()
{
    sum = 0;
    for (int i = 1; i <= m; i++)
        sum += num[p[i] - 1];
    if (isPrime(sum))
        ans++;
}
void dfs(int x, int c)
{
    if (c == m)
    {
        print();
        return;
    }
    if (c + n + 1 - x < m)
        return;
    for (int i = x; i <= n; i++)
    {
        p[c + 1] = i;
        dfs(i + 1, c + 1);
    }
}
int main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> num[i];
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
