#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, m, k[N];
int main()
{
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    multiset<int> s;
    multiset<int>::iterator it;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        s.insert(0);
    for (int i = 0; i < n; i++)
    {
        cin >> k[i];
    }
    for (int i = 0; i < n; i++)
    {
        it = s.begin();
        s.erase(it);
        s.insert(*it + k[i]);
    }
    cout << *s.rbegin() << endl;
    return 0;
}
