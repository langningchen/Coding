#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, m, q;
map<int, map<int, bool>> ma;
int main()
{
    freopen("seeds.in", "r", stdin);
    freopen("seeds.out", "w", stdout);
    cin >> n >> m >> q;
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        ma[x - 1][y - 1] = true;
    }
    bool flag = false;
    do
    {
        flag = false;
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < m - 1; j++)
                if (ma[i][j] && ma[i + 1][j] && ma[i][j + 1] && !ma[i + 1][j + 1])
                {
                    ma[i + 1][j + 1] = true;
                    flag = true;
                }
        for (int i = 0; i < n - 1; i++)
            for (int j = 1; j < m; j++)
                if (ma[i][j] && ma[i + 1][j] && ma[i][j - 1] && !ma[i + 1][j - 1])
                {
                    ma[i + 1][j - 1] = true;
                    flag = true;
                }
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m - 1; j++)
                if (ma[i][j] && ma[i - 1][j] && ma[i][j + 1] && !ma[i - 1][j + 1])
                {
                    ma[i - 1][j + 1] = true;
                    flag = true;
                }
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (ma[i][j] && ma[i - 1][j] && ma[i][j - 1] && !ma[i - 1][j - 1])
                {
                    ma[i - 1][j - 1] = true;
                    flag = true;
                }
    } while (flag);
    ll Counter = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!ma[i][j])
                Counter++;
    cout << Counter << endl;
    return 0;
}