#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int Apples[N], Height, Counter;
int main()
{
    for (int i = 0; i < 10; i++)
        cin >> Apples[i];
    cin >> Height;
    Height += 30;
    for (int i = 0; i < 10; i++)
        if (Apples[i] <= Height)
            Counter++;
    cout << Counter << endl;
    return 0;
}