#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("contagion.in","r",stdin);
    freopen("contagion.out","w",stdout);
    set<string> s;
    s.insert("zombie");
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;
        if (s.count(a))
            s.insert(b);
        else if(s.count(b))
            s.insert(a);
    }
    cout << s.size() << endl;
    return 0;
}
