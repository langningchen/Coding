#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, d[N], s[N];
int main()
{
    freopen("parentheses.in", "r", stdin);
    freopen("parentheses.out", "w", stdout);
    cin >> n;
    string formula;
    getline(cin, formula);
    getline(cin, formula);
    for (int i = 0; i < n; i++)
    {
        if (formula[i] == '(')
            d[i + 1] = 1;
        else if (formula[i] == ')')
            d[i + 1] = -1;
        else
            d[i + 1] = 0;
    }
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + d[i];
    for (int i = 1; i <= n; i++)
        if (formula[i - 1] != '(' && formula[i - 1] != ')')
            cout << s[i] << " ";
    cout << endl;
    return 0;
}
