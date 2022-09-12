#include <bits/stdc++.h>
using namespace std;
string s;
bool flag = false;
int main()
{
    cin >> s;
    if (s[0] == '-')
    {
        flag = true;
        s.erase(0, 1);
    }
    for (int i = 0; i < s.size() / 2; i++)
        swap(s[i], s[s.size() - 1 - i]);
    while (s[0] == '0' && s.size() != 1)
        s.erase(0, 1);
    if (flag)
        cout << "-";
    cout << s << endl;
    return 0;
}