#include <bits/stdc++.h>
using namespace std;
int Ans, Max = 8;
int main()
{
    for (int i = 0; i < 7; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a + b > Max)
        {
            Max = a + b;
            Ans = i + 1;
        }
    }
    cout << Ans << endl;
    return 0;
}