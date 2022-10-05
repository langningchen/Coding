#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct word
{
    string s;
    ll cnt;
    bool operator<(const word &a) const
    {
        if (cnt == a.cnt)
            return s < a.s;
        return cnt > a.cnt;
    }
};
map<string, ll> mp;
set<word> s;
ll m;
int main()
{
    freopen("frequency.in", "r", stdin);
    freopen("frequency.out", "w", stdout);
    char c = 0;
    while (c != '\n')
    {
        string str;
        c = getchar();
        while (c != ' ' && c != '\n')
        {
            str.push_back(c);
            c = getchar();
        }
        mp[str]++;
    }
    cin >> m;
    for (map<string, ll>::iterator it = mp.begin(); it != mp.end(); it++)
        s.insert((word){it->first, it->second});
    set<word>::iterator it = s.begin();
    for (ll i = 0; i < m; i++)
    {
        cout << it->s << endl;
        it++;
    }
    return 0;
}