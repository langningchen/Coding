#include <bits/stdc++.h>
using namespace std;
const int N = 2000;
int main()
{
    freopen("fix.in", "w", stdout);
    srand(time(NULL));
    cout << (rand() % N + 1) << " " << N << endl;
    for (int i = 0; i < N; i++)
        cout << (rand() % N + 1) << " ";
    cout << endl;
    return 0;
}
