#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("merge.in","r",stdin);
    freopen("merge.out","w",stdout);
    multiset<int> s;
    multiset<int>::iterator it;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    while(s.size() >= 2) {
        it = s.end();
        it--;
        int a = *it;
        s.erase(it);
        it = s.end();
        it--;
        int b = *it;
        s.erase(it);
        s.insert(a * b + 1);
    }
    cout << *s.begin() << endl;
    return 0;
}
