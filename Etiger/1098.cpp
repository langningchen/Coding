#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, x[N], f[N][N];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += x[i];
    int half = sum / 2;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= half; j++)
        {
            if (j < x[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = f[i - 1][j] || f[i - 1][j - x[i]];
        }
    for (int j = half; j >= 0; j--)
        if (f[n][j])
        {
            cout << j << " " << sum - j << endl;
            break;
        }
    cout << endl;
    return 0;
}
