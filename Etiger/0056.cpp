#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int u[N][2];
int max(int x1, int x2, int x3, int x4)
{
    int ans = x1;
    if (x2 > ans)
        ans = x2;
    if (x3 > ans)
        ans = x3;
    if (x4 > ans)
        ans = x4;
    return ans;
}
int min(int x1, int x2, int x3, int x4)
{
    int ans = x1;
    if (x2 < ans)
        ans = x2;
    if (x3 < ans)
        ans = x3;
    if (x4 < ans)
        ans = x4;
    return ans;
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    int L = 0, a = 0, ans = 0;
    cin >> L >> a;
    for (int i = 0; i < a; i++)
    {
        cin >> u[i][0] >> u[i][1];
    }
    for (int i = 0; i < a; i++)
    {
        if (u[i][0] > u[i][1])
        {
            int temp;
            temp = u[i][0];
            u[i][0] = u[i][1];
            u[i][1] = temp;
        }
    }
    for (int i = a; i > 0; i--)
    {
        for (int k = 0; k < i - 1; k++)
        {
            if (u[k][0] > u[k + 1][0])
            {
                int temp;
                temp = u[k][0];
                u[k][0] = u[k + 1][0];
                u[k + 1][0] = temp;
                temp = u[k][1];
                u[k][1] = u[k + 1][1];
                u[k + 1][1] = temp;
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
