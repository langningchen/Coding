#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
map<string, int> cnt;
map<string, bool> flag;
int ans1, ans2, n, m, l;
string s[N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string t;
        cin >> t;
        flag[t] = 1;
    }
    cin >> m;
    l = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> s[i];
        if (flag[s[i]])
            cnt[s[i]]++;
        if (cnt[s[i]] == 1)
        {
            ans1++;
            ans2 = i - l + 1;
        }
        while (l <= i)
        {
            if (!flag[s[l]])
            {
                l++;
                continue;
            }
            if (cnt[s[l]] >= 2)
            {
                cnt[s[l]]--;
                l++;
                continue;
            }
            break;
        }
        ans2 = min(ans2, i - l + 1);
    }
    cout << ans1 << endl;
    cout << ans2 << endl;
    return 0;
}
