#include <bits/stdc++.h>
using namespace std;
const int LEN = 4;
const int R = 10;
int T, a[LEN + 1], b[LEN + 1], c[LEN + 1];
bool win(int *x, int *y)
{
    int cnt = 0;
    for (int i = 1; i <= LEN; i++)
        for (int j = 1; j <= LEN; j++)
        {
            if (x[i] > y[j])
                cnt++;
            else if (x[i] < y[j])
                cnt--;
        }
    return cnt > 0;
}
bool dfs(int pos, int val)
{
    if (pos > LEN)
    {
        if (win(b, c) && win(c, a))
            return 1;
        return 0;
    }
    for (int i = val; i <= R; i++)
    {
        c[pos] = i;
        if (dfs(pos + 1, i))
            return 1;
    }
    return 0;
}
int main()
{
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        for (int i = 1; i <= LEN; i++)
            cin >> a[i];
        for (int i = 1; i <= LEN; i++)
            cin >> b[i];
        if (!win(a, b) && !win(b, a))
        {
            cout << "no" << endl;
            continue;
        }
        if (!win(a, b))
            for (int i = 1; i <= LEN; i++)
                swap(a[i], b[i]);
        cout << (dfs(1, 1) ? "yes" : "no") << endl;
    }
    return 0;
}