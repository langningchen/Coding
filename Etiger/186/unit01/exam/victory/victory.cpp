#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
multiset<ll, std::greater<ll>> Man;
multiset<ll> Woman;
bool Temp[N];
ll n;
int main()
{
    freopen("victory.in", "r", stdin);
    freopen("victory.out", "w", stdout);
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        string Sex;
        cin >> Sex;
        Temp[i] = (Sex == "man" ? 1 : 0);
    }
    for (ll i = 0; i < n; i++)
    {
        ll Height;
        cin >> Height;
        if (Temp[i])
            Man.insert(Height);
        else
            Woman.insert(Height);
    }
    for (multiset<ll>::iterator sit = Man.begin(); sit != Man.end(); sit++)
        cout << *sit << " ";
    for (multiset<ll>::iterator sit = Woman.begin(); sit != Woman.end(); sit++)
        cout << *sit << " ";
    return 0;
}