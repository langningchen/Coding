#include <bits/stdc++.h>
using namespace std;
const int N = 21;
long long lm[N][N];
int m, n, a1, b1, a2, b2, a3, b3;
int main() {
    lm[1][1] = 1;
    cin >> n >> m >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
    if ((a1 == 1 && b1 == 1) || (a2 == 1 && b2 == 1) || (a3 == 1 && b3 == 1)) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if(i != 1 || j != 1)
                if ((i == a1 && j == b1) || (i == a2 && j == b2) || (i == a3 && j == b3))
                    lm[i][j] = 0;
                else
                    lm[i][j] = (lm[i][j - 1] + lm[i - 1][j]);
    cout << lm[n][m];
    return 0;
}
