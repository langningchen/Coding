#include <bits/stdc++.h>
using namespace std;
string s, rp1, rp2;
int main()
{
    int p;
    getline(cin, s);
    getline(cin, rp1);
    getline(cin, rp2);
    s = " " + s + " ";
    while (1)
    {
        p = s.find(" " + rp1 + " ");
        if (p == -1)
            break;
        s.erase(p + 1, rp1.size());
        s.insert(p + 1, rp2);
    }
    s.erase(0, 1);
    s.erase(s.size() - 1);
    cout << s << endl;
    return 0;
}
