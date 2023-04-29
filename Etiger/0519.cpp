#include <bits/stdc++.h>
using namespace std;
const int N = 155;
string ans[N];
string name[N];
int m, n, p[N], num = 0;
bool vst[N];
void print()
{
    ans[num] = "";
    for (int i = 1; i <= m; i++)
        ans[num] += name[p[i]];
    ans[num] += " wang";
    num++;
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
    freopen("name1.in", "r", stdin);
    freopen("name1.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> name[i];
    m = n;
    sort(name, name + n);
    dfs(1);
    sort(ans, ans + num);
    for (int i = 0; i < num; i++)
        cout << ans[i].data() << endl;
    return 0;
}
