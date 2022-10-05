#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m, z[N], ans;
set<ll> t[N];
void Input()
{

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> z[i];
    }
    for (int i = 0; i < m; i++)
    {
        ll a, b;
        cin >> a >> b;
        t[a].insert(b);
        t[b].insert(a);
    }
}
bool Is1()
{
    return (n == 3);
}
void Solve1()
{
    if (m == 3)
    {
        cout << max(z[0], max(z[1], z[2])) << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}
bool Is2()
{
    return 1;
    // return (n <= 200);
}
void Solve2()
{
    ll Answer = 0;
    for (ll a = 0; a < n; a++)
    {
        for (set<ll>::iterator b = t[a].begin(); b != t[a].end(); b++)
        {
            if (a < *b)
            {
                for (set<ll>::iterator c = t[*b].begin(); c != t[*b].end(); c++)
                {
                    if (*b < *c)
                    {
                        for (set<ll>::iterator i = t[*c].begin(); i != t[*c].end(); i++)
                        {
                            if (*i == a)
                            {
                                //                                cout << a << " " << *b << " " << *c << endl;
                                Answer += max(z[a - 1], max(z[*b - 1], z[*c - 1]));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << Answer << endl;
}
void Solve3()
{
}
int main()
{
    freopen("three.in", "r", stdin);
    freopen("three.out", "w", stdout);
    Input();
    if (Is1())
    {
        Solve1();
    }
    else if (Is2())
    {
        Solve2();
    }
    else
    {
        Solve3();
    }
    return 0;
}
