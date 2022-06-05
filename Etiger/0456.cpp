/*
f[i][j]代表将整数n分成k份有多少种不同的分法
    j=0,1,2,3,4,5
i=0   0 0 0 0 0 0
i=1   0 1 0 0 0 0
i=2   0 1 1 0 0 0
i=3   0 1 1 1 0 0
i=4   0 1 1 1 1 0
i=5   0 1 1 1 1 1
*/
#include <bits/stdc++.h>
const int N = 200;
typedef long long ll;
ll n, m, f[N][N];
using namespace std;
int main() {
    freopen("partition.in","r",stdin);
    freopen("partition.out","w",stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) f[i][1] = 1;
    for (int j = 2; j <= m; j++)
        for (int i = j; i <= n; i++)
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
    cout << f[n][m] << endl;
    return 0;
}
