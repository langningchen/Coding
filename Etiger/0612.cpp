#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n, x[N];
int partition(int a, int b)
{
    int pivot = x[a];
    int i = a + 1;
    for (int j = a + 1; j <= b; j++)
        if (x[j] < pivot)
            swap(x[i++], x[j]);
    swap(x[a], x[i - 1]);
    return i - 1;
}
void qsort(int a, int b)
{
    if (a >= b)
        return;
    int p = partition(a, b);
    qsort(a, p);
    qsort(p + 1, b);
}
int main()
{
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    qsort(1, n);
    cout << x[(n + 1) / 2] << endl;
    return 0;
}
