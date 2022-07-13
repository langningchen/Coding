#include <bits/stdc++.h>
using namespace std;
const int N = 25;
const int CLR = 4;
char colors[CLR] = {'\0', 'B', 'G', 'R'};
int n, p[N];
void print()
{
    for (int i = 1; i <= n; i++)
        cout << colors[p[i]];
    cout << endl;
}
void dfs(int x)
{
    if (x == n + 1)
    {
        print();
        return;
    }
    if (p[x] >= 1)
    {
        dfs(x + 1);
        return;
    }
    for (int i = 1; i < CLR; i++)
        if (x == 1 && p[2] != i ||
            x == n && p[x - 1] != i ||
            p[x - 1] != i && p[x + 1] != i)
        {
            p[x] = i;
            dfs(x + 1);
            p[x] = 0;
        }
}
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    char ch;
    while (cin >> ch)
    {
        ++n;
        if (ch == 'B')
            p[n] = 1;
        else if (ch == 'G')
            p[n] = 2;
        else if (ch == 'R')
            p[n] = 3;
        else
            p[n] = 0;
    }
    dfs(1);
    return 0;
}
