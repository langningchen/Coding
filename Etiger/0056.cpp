#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int L, a, ans, u[N][2];
int max(int x1, int x2, int x3, int x4)
{
    return max(x1, max(x2, max(x3, x4)));
}
int min(int x1, int x2, int x3, int x4)
{
    return min(x1, min(x2, min(x3, x4)));
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> L >> a;
    for (int i = 0; i < a; i++)
    {
        cin >> u[i][0] >> u[i][1];
    }
    for (int i = 0; i < a; i++)
    {
        if (u[i][0] > u[i][1])
        {
            swap(u[i][0], u[i][1]);
        }
    }
    for (int i = a; i > 0; i--)
    {
        for (int k = 0; k < i - 1; k++)
        {
            if (u[k][0] > u[k + 1][0])
            {
                swap(u[k][0], u[k + 1][0]);
                swap(u[k][1], u[k + 1][1]);
            }
        }
    }
    for (int i = 0; i < a - 1; i++)
    {
        if (u[i][1] >= u[i + 1][0])
        {
            u[i + 1][0] = min(u[i][0], u[i][1], u[i + 1][0], u[i + 1][1]);
            u[i + 1][1] = max(u[i][0], u[i][1], u[i + 1][0], u[i + 1][1]);
            u[i][0] = -1;
            u[i][1] = -1;
        }
    }
    for (int i = 0; i < a; i++)
    {
        if (!(u[i][0] == -1 || u[i][1] == -1))
        {
            ans += u[i][1] - u[i][0] + 1;
        }
    }
    ans = L + 1 - ans;
    cout << ans << endl;
    return 0;
}
