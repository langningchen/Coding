#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '(')
            n++;
        else if (s[i] == ')')
            n--;
    if (n == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}