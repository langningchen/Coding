#include <bits/stdc++.h>
using namespace std;
int a, b, c, mod, cnt;
string ans;
void dfs(int x, int clr, int first_clr)
{
    if (x == 1)
    {
        if (a != 0 && first_clr != 0 && clr != 0)
        {
            // cout << ans << "1" << endl;
            cnt = (cnt + 1) % mod;
        }
        if (b != 0 && first_clr != 1 && clr != 1)
        {
            // cout << ans << "2" << endl;
            cnt = (cnt + 1) % mod;
        }
        if (c != 0 && first_clr != 2 && clr != 2)
        {
            // cout << ans << "3" << endl;
            cnt = (cnt + 1) % mod;
        }
        return;
    }
    // if (a + b < c - 3 || b + c < a - 3 || c + a < b - 3)
    //     return;
    if (clr != 0 && a > 0)
    {
        a--;
        // ans += "1";
        dfs(x - 1, 0, (first_clr == -1) ? 0 : first_clr);
        // ans.erase(ans.size() - 1, 1);
        a++;
    }
    if (clr != 1 && b > 0)
    {
        b--;
        // ans += "2";
        dfs(x - 1, 1, (first_clr == -1) ? 1 : first_clr);
        // ans.erase(ans.size() - 1, 1);
        b++;
    }
    if (clr != 2 && c > 0)
    {
        c--;
        // ans += "3";
        dfs(x - 1, 2, (first_clr == -1) ? 2 : first_clr);
        // ans.erase(ans.size() - 1, 1);
        c++;
    }
}
int main()
{
    // freopen("T296829.in", "r", stdin);
    freopen("T296829.out", "w", stdout);
    cin >> a >> b >> c >> mod;
    mod = 0x7fffffff;
    for (int a = 0; a <= 100; a++)
        for (int b = 0; b <= 100; b++)
            for (int c = 0; c <= 100; c++)
            {
                cnt = 0;
                if (c == 0)
                {
                    cout << a << " " << b << " " << c << " ";
                    if ((a + b) % 2 != 0 || abs(a - b) > 1)
                        cout << 0 << endl;
                    else
                        cout << 2 << endl;
                }
                else
                {
                    dfs(a + b + c, -1, -1);
                    if (cnt != 0)
                    {
                        cout << a << " " << b << " " << c << " ";
                        cout << cnt << endl;
                    }
                }
            }
    return 0;
}
