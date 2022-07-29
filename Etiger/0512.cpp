#include <iostream>
using namespace std;
const int N = 15;
int a[N];
int main()
{
    a[0] = 8;
    for (int i = 1; i <= 7; i++)
    {
        int temp;
        cin >> a[i] >> temp;
        a[i] += temp;
    }
    int max = 0;
    for (int i = 1; i <= 7; i++)
    {
        if (a[i] > a[max])
        {
            max = i;
        }
    }
    cout << max << endl;
    return 0;
}