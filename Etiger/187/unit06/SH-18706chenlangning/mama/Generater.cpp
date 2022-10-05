#include <bits/stdc++.h>
using namespace std;
const int N = 550;
int main()
{
    freopen("mama.in", "w", stdout);
    srand(time(NULL));
    cout << N << " " << 100000 << endl;
    for (int i = 0; i < N; i++)
        cout << (rand() % 100000 + 1) << " " << (rand() % 100000 + 1) << endl;
    return 0;
}