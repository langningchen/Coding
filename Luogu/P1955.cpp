#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, btop, ctop, T, b[N * 2], c[N * 2], fa[N * 2];
struct code
{
    int x, y, z;
} a[N];
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        fa[x] = y;
}
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        btop = 0;
        ctop = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].x >> a[i].y >> a[i].z;
            b[++btop] = a[i].x;
            b[++btop] = a[i].y;
        }
        sort(b + 1, b + btop + 1);
        for (int i = 1; i <= btop; i++)
            if (b[i] != b[i - 1])
                c[++ctop] = b[i];
        for (int i = 1; i <= n; i++)
        {
            a[i].x = lower_bound(c + 1, c + ctop + 1, a[i].x) - c;
            a[i].y = lower_bound(c + 1, c + ctop + 1, a[i].y) - c;
        }
        for (int i = 1; i <= ctop; i++)
            fa[i] = i;
        for (int i = 1; i <= n; i++)
            if (a[i].z)
                merge(a[i].x, a[i].y);
        bool mk = true;
        for (int i = 1; i <= n; i++)
            if (!a[i].z)
                if (find(a[i].x) == find(a[i].y))
                {
                    mk = false;
                    break;
                }
        cout << (mk ? "YES" : "NO") << endl;
    }
    return 0;
}