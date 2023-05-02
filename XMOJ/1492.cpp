#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
const int INF = 0x7FFF'FFFF;
int n, d[N], x[N];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    fill(d, d + n, INF);
    for (int i = 0; i < n; i++)
        *upper_bound(d, d + n, -x[i]) = -x[i];
    printf("%d\n", lower_bound(d, d + n, INF) - d);
    return 0;
}
