#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50005;
ll T, n, c[N];
int LowBit(int x)
{
    return x & (-x);
}
void Add(int x, int d)
{
    while (x <= n)
    {
        c[x] += d;
        x += LowBit(x);
    }
}
int Sum(int x)
{
    int v = 0;
    while (x > 0)
    {
        v += c[x];
        x -= LowBit(x);
    }
    return v;
}
int main()
{
    scanf("%lld", &T);
    for (ll t = 1; t <= T; t++)
    {
        printf("Case %lld:\n", t);
        memset(c, 0, sizeof(c));
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
        {
            ll a = 0;
            scanf("%lld", &a);
            Add(i, a);
        }
        char Operation[6];
        memset(Operation, 0, sizeof(char) * 6);
        while (1)
        {
            int i = 0, j = 0;
            scanf("%s", Operation);
            if (strcmp(Operation, "End") == 0)
                break;
            scanf("%d %d", &i, &j);
            if (strcmp(Operation, "Add") == 0)
                Add(i, j);
            else if (strcmp(Operation, "Sub") == 0)
                Add(i, -j);
            else if (strcmp(Operation, "Query") == 0)
                printf("%d\n", Sum(j) - Sum(i - 1));
        }
    }
    return 0;
}
