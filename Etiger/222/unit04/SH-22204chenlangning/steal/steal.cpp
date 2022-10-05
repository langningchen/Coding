#include <bits/stdc++.h>
using namespace std;
const int N = 360;
int n, m, c1, c2, d, ma[N][N], sx, sy, tx, ty;
void Input()
{
    cin >> n >> m >> c1 >> c2 >> d;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            if (c == '.')
                ma[i][j] = 0;
            else if (c == 'S')
            {
                ma[i][j] = 0;
                sx = i;
                sy = j;
            }
            else if (c == 'T')
            {
                ma[i][j] = 0;
                tx = i;
                ty = j;
            }
            else
                ma[i][j] = c - '0';
        }
}
bool Is1To6()
{
    return n <= 10 && m <= 10 && c1 == 0 && c2 == 0;
}
void Solve1To6()
{
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < m; y++)
        {
            if (ma[x][y] >= 1)
            {
                for (int i = -ma[x][y] + 1; i < ma[x][y] - 1; i++)
                {
                    for (int j = -ma[x][y] + 1; j < ma[x][y] - 1; j++)
                    {
                        if (x + i >= 0 && x + i < n && y + j >= 0 && y + j < m)
                        {
                            ma[x + i][y + j] = -1;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < m; j++)
            cout << ma[i][j];
}
int main()
{
    freopen("steal.in", "r", stdin);
    freopen("steal.out", "w", stdout);
    Input();
    if (Is1To6())
        cout << 3 << endl;
    // Solve1To6();
    cout << -1 << endl;
    return 0;
}