#include <iostream>
using namespace std;
const int N = 55;
long long n, f[N], a, b, i = 0;
int main()
{
    cin >> n >> a >> b;
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    while (i <= b)
    {
        f[i] = 1;
        i += a;
    }
    f[b]++;
    for (int j = b + 1; j <= n; j++)
        f[j] = f[j - a] + f[j - b];
    cout << f[n] << endl;
    return 0;
}
