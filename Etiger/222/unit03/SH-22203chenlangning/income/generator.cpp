#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 18000;
const ll M = 1000000000;
const ll D = 100;
int main()
{
    freopen("income.in", "w", stdout);
    srand(time(0));
    ll a = rand() % M + 1;
    cout << N << " " << a << endl;
    for (int i = 0; i < N; i++)
        cout << rand() % D - D / 2 + a << " ";
    cout << endl;
    return 0;
}