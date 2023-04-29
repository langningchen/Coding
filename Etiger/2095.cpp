#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    freopen("longlife.in", "r", stdin);
    freopen("longlife.out", "w", stdout);
    ll n, i;
    cin >> n;
    string ans = "", name = "", seq = "";
    ll maxx = -1;
    while (n--)
    {
        cin >> name >> seq;
        ll cnt = 0;
        for (i = 0; i < (ll)seq.size() - 2; i++)
            if (seq[i] == 'T' && seq[i + 1] == 'A' && seq[i + 2] == 'T')
                cnt++;
        if (cnt > maxx)
            ans = name, maxx = cnt;
        else if (cnt == maxx)
            ans += (" " + name);
    }
    cout << ans << endl
         << maxx << endl;
    return 0;
}