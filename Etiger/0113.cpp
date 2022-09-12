#include <bits/stdc++.h>
using namespace std;
multiset<int> s;
multiset<int>::iterator it;
int n, ans = 0;
int main()
{
    freopen("merge.in", "r", stdin);
    freopen("merge.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        s.insert(x);
    }
    while (s.size() >= 2)
    {
        it = s.begin();
        int a = *it;
        s.erase(it);
        it = s.begin();
        int b = *it;
        s.erase(it);
        s.insert(a + b);
        ans += a + b;
    }
    cout << ans << endl;
    return 0;
}
