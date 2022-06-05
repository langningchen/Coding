#include <bits/stdc++.h>
const int N = 200005;
int a[N], b[2][N], l[2];
int Father[N];
int n;
int cnt = 0, now = 0;
int Find(int x)
{
    return ((Father[x] == x) ? x : Father[x] = Find(Father[x]));
}
void Union(int x, int y)
{
    Father[Find(x)] = Find(y);
}
int Change(int x) {
    return ((x == 0) ? 1 : 0);
}
void Input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        Father[i + 1] = i + 1;
    }
}
void Output() {
    for (int i = 0; i < l[now] - 1; i++)
        printf("%d ", b[now][i] + 1);
    printf("%d\n", b[now][l[now] - 1] + 1);
}
int main()
{
    freopen("fruit.in", "r", stdin);
    freopen("fruit.out", "w", stdout);
    Input();
    for (int i = 0; i < n; i++)
        if (i == 0 || a[i] != a[i - 1])
            b[0][l[0]++] = i;
    while (cnt < n)
    {
        Output();
        cnt += l[now];
        for (int i = 0; i < l[now]; i++)
            Union(b[now][i], b[now][i] + 1);
        int col = -1;
        l[Change(now)] = 0;
        for (int i = 0; i < l[now]; i++)
        {
            int t = Find(b[now][i] + 1);
            if (t + 1 > n)
                continue;
            if (col != a[t])
                b[Change(now)][l[Change(now)]++] = t;
            col = a[t];
        }
        now = Change(now);
    }
    return 0;
}

