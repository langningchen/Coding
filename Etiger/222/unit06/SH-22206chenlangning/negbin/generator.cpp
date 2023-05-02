#include <bits/stdc++.h>
using namespace std;
const int N = 1000000000;
int main()
{
    srand(time(0));
    // freopen("negbin.in", "w", stdout);
    cout << rand() % (N * 2) - N << endl;
    return 0;
}