#include <bits/stdc++.h>
using namespace std;
const int R = 35;
int cnt[R];
char ch;
int main()
{
    freopen("love.in", "r", stdin);
    freopen("love.out", "w", stdout);
    while (cin >> ch)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            int i = ch - 'a';
            cnt[i]++;
        }
    }
    int cl = cnt['l' - 'a'];
    int co = cnt['o' - 'a'];
    int cv = cnt['v' - 'a'] + cnt['w' - 'a'] * 2;
    int ce = cnt['e' - 'a'];
    int ans = min(min(cl, co), min(cv, ce));
    cout << ans << endl;
    return 0;
}
