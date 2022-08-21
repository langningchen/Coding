#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n, d[N];
int countDiff()
{
    set<int> s;
    for (int i = 1; i <= n; i++)
        s.insert(d[i]);
    return s.size();
}
int solve(int C)
{
    int l = 1, r = 1;
    int cDiff = 0;
    int ret = 1;
    int cnt[30] = {0};
    while (1)
    {
        while (r <= n && cDiff <= C)
        {
            if (cnt[d[r]] == 0)
                ++cDiff;
            ++cnt[d[r]];
            ++r;
        }
        if (cDiff <= C)
            ret = max(ret, r - l);
        else
            ret = max(ret, r - l - 1);
        if (r > n)
            return ret;
        if (cnt[d[l]] == 1)
            --cDiff;
        --cnt[d[l]];
        ++l;
    }
    return -1;
}
int main()
{
    freopen("chaos.in", "r", stdin);
    freopen("chaos.out", "w", stdout);
    string s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
        d[i] = s[i - 1] - 'a';
    int nDiff = countDiff();
    int fenzi = 1, fenmu = 1;
    for (int x = 1; x <= nDiff; x++)
    {
        int len = solve(x);
        if (fenzi * len > fenmu * x || fenzi * len == fenmu * x && len > fenmu)
            fenzi = x, fenmu = len;
    }
    cout << fenzi << "/" << fenmu << endl;
    return 0;
}