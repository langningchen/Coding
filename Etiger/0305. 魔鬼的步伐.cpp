#include <iostream>
using namespace std;
long long n, f[55], a, b, i = 0;
int main() {
    cin >> n >> a >> b; //���� 
    if (a > b)
    {
        int temp = a;a = b;b = temp;
    }
    while (i <= b)
    {
        f[i] = 1;
        i += a;
    }
    f[b]++; 
    for (int j = b + 1; j <= n; j++)
        f[j] = f[j - a] + f[j - b]; //������һ�� 
    cout << f[n]; //��� 
    return 0;
}
