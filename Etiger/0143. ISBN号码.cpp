#include<bits/stdc++.h>
using namespace std;
int main() {
    freopen("isbn.in","r",stdin);
    freopen("isbn.out","w",stdout);
    string s;
    getline(cin, s);
    int c = 1, sum = 0;
    for (int i = 0; i < s.size() - 2; i++)
    {
        if (i != 1 && i != 5)
        {
            sum += c*(s[i] - '0');
            c++;
        }
    }
    int id = sum % 11;
    char code = 'X';
    if (id < 10)
    {
        code = id + '0';
    }
    if (s[12] == code)
        cout << "Right";
    else
        cout << s.substr(0, 12) << code;
    return 0;
}

