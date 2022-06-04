#include <bits/stdc++.h>
using namespace std;
int k[10000];
int main() {
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    multiset<int> s;
    multiset<int>::iterator it;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        s.insert(0);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < n; i++) {
        it = s.begin();
        int a = *it;
        s.erase(it);
        s.insert(a + k[i]);
    }
    cout << *s.rbegin() << endl;
    return 0;
}
