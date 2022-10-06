#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll b;
vector<ll> v;
set<pair<int, int>> vst;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("half.in", "r", stdin);
    freopen("half.out", "w", stdout);
    cin >> b;
    if (b == 2)
    {
        cout << "1 0" << endl;
        return 0;
    }
    v.push_back(2);
    ll c = 0;
    while (1)
    {
        ll a = v.back() * 2 + c;
        v.push_back(a % b);
        c = a / b;
        if (vst.count(make_pair(v.back(), c)))
        {
            cout << "None" << endl;
            return 0;
        }
        vst.insert(make_pair(v.back(), c));
        if (a % b == 1 && c == 0)
            break;
    }
    for (int i = v.size() - 1; i >= 0; i--)
        cout << v[i] << " ";
    cout << endl;
    return 0;
}