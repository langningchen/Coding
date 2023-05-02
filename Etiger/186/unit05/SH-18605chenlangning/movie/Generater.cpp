#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("movie.in", "w", stdout);
    srand(time(NULL));
    cout << 200000 << endl;
    for (int i = 0; i < 200000; i++)
        cout << (rand() % 1000000000 + 1) << " ";
    cout << endl;
    for (int i = 0; i < 200000; i++)
        cout << (rand() % 1000000000 + 1) << " ";
    cout << endl;
    return 0;
}
