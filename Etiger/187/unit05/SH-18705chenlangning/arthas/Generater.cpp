#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int main()
{
    freopen("arthas.in", "w", stdout);
    srand(time(NULL));
    cout << N << endl;
    for (int i = 0; i < N; i++)
        cout << (char)(rand() % 26 + 'a');
    cout << endl;
    return 0;
}