#include <iostream>
using namespace std;
int main()
{
    int n, m, a[100];
    cin>>n>>m;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] + a[j] == m && i != j)
            {
                cout<<"Yes";
                return 0;
            }
        }
    }
    cout<<"No";
    return 0;
}

