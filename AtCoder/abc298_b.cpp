#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], b[N][N];
bool flag;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> b[i][j];
    for (int t = 0; t < 4; t++)
    {
        int c[N][N];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c[i][j] = a[n - 1 - j][i];
        memcpy(a, c, sizeof(c));
        flag = true;
        for (int i = 0; i < n && flag; i++)
            for (int j = 0; j < n && flag; j++)
                if (a[i][j] && !b[i][j])
                    flag = false;
        if (flag)
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << endl;
    }
    cout << "No" << endl;
    return 0;
}
