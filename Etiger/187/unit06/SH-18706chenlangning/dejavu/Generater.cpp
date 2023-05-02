#include <bits/stdc++.h>
using namespace std;
const int N = 500;
int main()
{
    freopen("dejavu.in", "w", stdout);
    srand(time(NULL));
    cout << N << " " << 1000000 << endl;
    for (int i = 0; i < 1000000; i++)
        cout << (rand() % N + 1) << " " << (rand() % N + 1) << endl;
    return 0;
}