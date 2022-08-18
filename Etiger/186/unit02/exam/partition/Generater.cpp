#include <bits/stdc++.h>
using namespace std;
const int N = 30;
int main()
{
    freopen("partition.in", "w", stdout);
    srand(time(NULL));
    cout << N << endl;
    int nX = rand() % N;
    cout << nX << " " << N - nX << endl;
    for (int i = 0; i < N; i++)
        cout << (rand() % 1000 + 1) << " ";
    cout << endl;
    for (int i = 0; i < N; i++)
        cout << (rand() % 1000 + 1) << " ";
    cout << endl;
    return 0;
}
