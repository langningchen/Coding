#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("heroes.in","r",stdin);
    freopen("heroes.out","w",stdout);
    int n;
    cin >> n;
    set<string> s;
    for (int i = 0; i < n; i++) {
        char ch;
        string x;
        cin >> ch >> x;
        if (ch == '+')
            s.insert(x);
        else
            s.erase(x);
    }
    set<string>::iterator it;
    for(it = s.begin(); it != s.end(); it++)
        cout << *it << endl;
    return 0;
}
