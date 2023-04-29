#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, q;
set<int> Cards[N];
multiset<int> Box[N];
int main()
{
    cin >> n >> q;
    for (int i = 0; i < q; i++)
    {
        int o, x, y;
        cin >> o >> x;
        if (o == 1)
        {
            cin >> y;
            Cards[x].insert(y);
            Box[y].insert(x);
        }
        else if (o == 2)
        {
            for (auto i : Box[x])
                cout << i << " ";
            cout << endl;
        }
        else if (o == 3)
        {
            for (auto i : Cards[x])
                cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}
