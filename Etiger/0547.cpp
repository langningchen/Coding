#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int id[N], qx[N], qy[N];
int root(int x)
{
    return ((id[x] == x) ? (x) : (id[x] = root(id[x])));
}
void unite(int x, int y)
{
    id[root(x)] = root(y);
}
int main()
{
    int nRelations, m = 0;
    cin >> nRelations;
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
    }
    for (int i = 0; i < nRelations; i++)
    {
        char u, v, x, y;
        cin >> u >> x >> y >> v;
        if (x == '=')
        {
            unite(u - 'a', v - 'a');
        }
        else
        {
            qx[m] = u - 'a';
            qy[m] = v - 'a';
            m++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (root(qx[i]) == root(qy[i]))
        {
            cout << "Impossible" << endl;
            return 0;
        }
    }
    cout << "Possible" << endl;
    return 0;
}
