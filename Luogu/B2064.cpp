#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35;
ll n, fib[N];
int main()
{
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i < N; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        cout << fib[a] << endl;
    }
    return 0;
}