#include <bits/stdc++.h>
using namespace std;
const int SN = 2009;
int n, s[SN][SN], jw[SN];
int main()
{
    freopen("half.in", "r", stdin);
    freopen("half.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
        s[i][1] = i;
    for (int j = 1; true; j++)
    {
        for (int i = 1; i < n; i++)
        {
            s[i][j + 1] = 2 * s[i][j] + jw[i];
            jw[i] = s[i][j + 1] / n;
            s[i][j + 1] %= n;
            if (jw[i] == 0 && s[i][j + 1] == i)
            {
                for (int k = j + 1; k > 1; k--)
                    cout << s[i][k] << " ";
                return 0;
            }
        }
    }
    return 0;
}
