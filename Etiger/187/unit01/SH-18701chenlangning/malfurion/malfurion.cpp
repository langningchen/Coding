#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, h[N];
bool stop;
vector<ll> m, t;
void dfs(int x)
{
    if (x == 3 && m.size() < 2)
        return;
    if (x == n)
    {
        if (m.size() > 1 && t.size() > 1)
        {
            cout << m.size() << endl;
            for (vector<ll>::iterator sit = m.begin(); sit != m.end(); sit++)
                cout << *sit << " ";
            cout << endl;
            cout << t.size() << endl;
            for (vector<ll>::iterator sit = t.begin(); sit != t.end(); sit++)
                cout << *sit << " ";
            cout << endl;
            stop = true;
        }
        return;
    }
    m.push_back(h[x]);
    if ((m.size() < 3 || m[m.size() - 1] - m[m.size() - 2] == m[m.size() - 2] - m[m.size() - 3]))
        dfs(x + 1);
    m.pop_back();
    if (stop)
        return;

    t.push_back(h[x]);
    if ((t.size() < 3 || t[t.size() - 1] - t[t.size() - 2] == t[t.size() - 2] - t[t.size() - 3]))
        dfs(x + 1);
    t.pop_back();
}
int main()
{
    freopen("malfurion.in", "r", stdin);
    freopen("malfurion.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> h[i];
    sort(h, h + n);
    dfs(0);
    if (stop == false)
        cout << -1 << endl;
    return 0;
}