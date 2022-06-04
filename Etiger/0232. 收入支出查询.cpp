#include <iostream>
using namespace std;
int n, m, x[10000], i, j;
int main() {
    cin >> n >> m >> x[i];
    for (int k = 1; k < n; k++)
    {
        cin >> x[k];
        x[k] = x[k - 1] + x[k];
    }
    for (int k = 0; k < m; k++)
    {
        cin >> i >> j;
        cout << x[j - 1] - x[i - 2] << ' ';
    }
    return 0;
}
