#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n, a[N], ans;
list<pair<int, int>> l;
int main()
{
    freopen("anubarak.in", "r", stdin);
    freopen("anubarak.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if (l.back().first == t)
            l.back().second++;
        else
            l.push_back(make_pair(t, 1));
    }
    while (!l.empty())
    {
        int MaxValue = 0;
        int MaxId = 0;
        int Counter = 0;
        list<pair<int, int>>::iterator t;
        for (list<pair<int, int>>::iterator lit = l.begin(); lit != l.end(); lit++)
        {
            if (lit->second > MaxValue)
            {
                MaxId = lit->first;
                MaxValue = lit->second;
                t = lit;
            }
            Counter++;
        }
        ans += MaxValue * MaxValue;
        l.erase(t);
        list<pair<int, int>>::iterator t1 = t;
        list<pair<int, int>>::iterator t2 = t;
        t1--;
        t2++;
        if (t1->first == t2->first)
        {
            t1->second += t2->second;
            l.erase(t2);
        }
    }
    cout << ans << endl;
    return 0;
}