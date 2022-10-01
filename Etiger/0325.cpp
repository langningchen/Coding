#include <bits/stdc++.h>
using namespace std;
string a, b;
int main()
{
    freopen("encryption.in", "r", stdin);
    freopen("encryption.out", "w", stdout);
    getline(cin, a);
    getline(cin, b);
    map<char, char> code;
    int len = b.size();
    code[b[len - 1]] = b[0];
    for (int i = 0; i <= len - 2; i++)
        code[b[i]] = b[i + 1];
    for (int i = 0; i < a.size(); i++)
        if (code.count(a[i]))
            cout << code[a[i]];
        else
            cout << a[i];
    return 0;
}
