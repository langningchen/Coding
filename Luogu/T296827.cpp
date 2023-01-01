#include <bits/stdc++.h>
using namespace std;
int n;
map<string, int> M;
int main()
{
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);
        M[s]++;
        string s2 = s;
        reverse(s2.begin(), s2.end());
        if (s2 != s)
            M[s2]++;
    }
    int ans = 0;
    for (auto i : M)
        ans = max(ans, i.second);
    cout << ans << endl;
    return 0;
}