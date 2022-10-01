#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int m, n, p[N];
bool vst[N];
void print()
{
    for (int i = 1; i <= m - 1; i++)
        cout << p[i] << " ";
    cout << p[m] << endl;
}
void dfs(int x)
{
    if (x == m + 1)
    {
        print();
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!vst[i])
        {
            vst[i] = 1;
            p[x] = i;
            dfs(x + 1);
            vst[i] = 0;
        }
}
int main()
{
    cin >> n;
    m = n;
    dfs(1);
    return 0;
}
