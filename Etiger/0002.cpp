#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7FFF'FFFF;
int n, a[N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    *(max_element(a, a + n)) = INF;
    *(min_element(a, a + n)) = INF;
    for (int i = 0; i < n; i++)
        if (a[i] != INF)
            cout << a[i] << " ";
    cout << endl;
    return 0;
}
