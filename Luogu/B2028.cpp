#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    cin >> s;
    for (int i = s.size() - 1; i >= 0; i--)
        cout << s[i];
    cout << endl;
    return 0;
}