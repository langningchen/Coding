#include <bits/stdc++.h>
using namespace std;
const int dayNum[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int m, offset, i;
int main()
{
    cin >> m;
    cout << "S\tM\tT\tW\tT\tF\tS" << endl;
    offset = 4;
    for (i = 1; i < m; i++)
        offset = (offset + dayNum[i]) % 7;
    for (i = 0; i < offset; i++)
        cout << '\t';
    for (i = 1; i <= dayNum[m]; i++)
    {
        cout << i;
        if (i == dayNum[m] || (i + offset) % 7 == 0)
            cout << endl;
        else
            cout << '\t';
    }
    return 0;
}
