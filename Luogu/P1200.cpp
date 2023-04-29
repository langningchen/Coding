#include <bits/stdc++.h>
using namespace std;
string a, b;
int Hash(string Data)
{
    int Ans = 1;
    for (int i = 0; i < Data.size(); i++)
        Ans *= Data[i] - 'A' + 1;
    return Ans;
}
int main()
{
    cin >> a >> b;
    if (Hash(a) % 47 == Hash(b) % 47)
        cout << "GO" << endl;
    else
        cout << "STAY" << endl;
    return 0;
}