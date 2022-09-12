#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N], n, p;
int i, j, b[N];
void swap2(int p)
{
    for (i = 1; i <= p; i++)
        b[n - p + i] = a[i];
    for (i = p + 1; i <= n; i++)
        b[i - p] = a[i];
    for (i = 1; i <= n; i++)
        a[i] = b[i];
}
int main()
{
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    swap2(p);
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}
