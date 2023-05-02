#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("chaos.in", "w", stdout);
    srand(time(NULL));
    cout << 100000 << endl;
    for (int i = 0; i < 100000; i++)
        cout << (char)(rand() % 26 + 'a');
    cout << endl;
    return 0;
}
