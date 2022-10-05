#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
const int M = 1000000000;
int main()
{
    srand(time(NULL));
    freopen("garithos.in", "w", stdout);
    cout << N << endl;
    for (int i = 0; i < N; i++)
        cout << rand() % (M * 2) + M << " " << rand() % (M * 2) + M << endl;
    return 0;
}