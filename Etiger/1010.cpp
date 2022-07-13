#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, x[2 * N];
int main()
{
    freopen("premiere3.in", "r", stdin);
    freopen("premiere3.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> x[i];
    int rank = x[m];
    for (int i = m - 1; i >= 1; i--)
        if (rank == n)
            rank = x[i];
        else if (x[i] <= rank)
            rank++;
    cout << rank << endl;
    return 0;
}
