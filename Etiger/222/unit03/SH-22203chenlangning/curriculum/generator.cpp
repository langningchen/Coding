#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100000;
const ll M = 1000;
ll n, k;
int main()
{
    freopen("curriculum.in", "w", stdout);
    srand(time(0));
    n = rand() % N + 1;
    k = rand() % n + 1;
    cout << n << " " << k << endl;
    for (int i = 0; i < n; i++)
    {
        ll a = rand() % M + 1, b = rand() % M + 1;
        cout << a << " " << b << endl;
    }
    return 0;
}