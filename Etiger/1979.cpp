#include <iostream>
using namespace std;
const int SIZE = 100;
int a[SIZE], n, p;

void swap2(int p)
{
    int i, j, b[SIZE];
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
