#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
string s;
ll Ans;
int main()
{
    // freopen("e.in", "r", stdin);
    // freopen("e.out", "w", stdout);
    cin >> s;
    int aCount = 0, cCount = 0;
    for (int i = 0; i < s.length(); i++)
        if (s[i] == 'C' || s[i] == '?')
            cCount++;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'A')
            aCount++;
        else if (s[i] == 'B')
            Ans = (Ans + aCount * cCount) % MOD;
        else if (s[i] == 'C')
            cCount--;
        else
        {
            cCount--;
            Ans = (Ans + aCount * cCount) % MOD;
            aCount++;
        }
    }
    cout << Ans << endl;
    return 0;
}
