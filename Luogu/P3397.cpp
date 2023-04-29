#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, X1, Y1, X2, Y2;
int a[N][N];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> X1 >> Y1 >> X2 >> Y2;
        a[X1][Y1]++;
        a[X1][Y2 + 1]--;
        a[X2 + 1][Y1]--;
        a[X2 + 1][Y2 + 1]++;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}