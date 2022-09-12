#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("capitalization.in", "r", stdin);
    freopen("capitalization.out", "w", stdout);
    string s;
    getline(cin, s);
    for (int i = 0; i < s.size(); i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 'a' + 'A';
    cout << s << endl;
    return 0;
}
