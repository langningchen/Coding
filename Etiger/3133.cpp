#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<string, int> cnt;
bool cmp(string x, string y)
{
    return cnt[x] > cnt[y] || cnt[x] == cnt[y] && x < y;
}
int main()
{
    freopen("frequency.in", "r", stdin);
    freopen("frequency.out", "w", stdout);
    int k = 0;
    string s;
    while (cin >> s)
    {
        if ('0' <= s[0] && s[0] <= '9')
        {
            for (int i = 0; i < s.size(); i++)
                k = k * 10 + s[i] - '0';
            break;
        }
        cnt[s]++;
    }
    vector<string> v;
    for (map<string, int>::iterator it = cnt.begin(); it != cnt.end(); it++)
        v.push_back(it->first);
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < k; i++)
        cout << v[i] << endl;
    return 0;
}