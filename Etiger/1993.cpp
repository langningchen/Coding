#include <bits/stdc++.h>
using namespace std;
int n, a[10];
long Counter = 0;
void perm(int k)
{
    int j, p, t;
    if (k == n)
    {
        Counter++;
        for (p = 1; p <= n; p++)
            cout << setw(1) << a[p];
        cout << "  ";
        if (Counter % 5 == 0)
            cout << endl;
        return;
    }
    for (j = k; j <= n; j++)
    {
        t = a[k];
        a[k] = a[j];
        a[j] = t;
        perm(k + 1);
        t = a[k];
        a[k] = a[j];
        a[j] = t;
    }
}
int main()
{
    int i;
    cin >> n;
    for (i = 1; i <= n; i++)
        a[i] = i;
    perm(1);
    return 0;
}
