#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
struct node
{
    string a;
    float b;
};
int m, n;
node ar[N];
int main()
{
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        cin >> ar[i].a >> ar[i].b;
    }
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            if (ar[i].b < ar[j].b)
            {
                node temp;
                temp = ar[i];
                ar[i] = ar[j];
                ar[j] = temp;
            }
    cout << ar[n - 1].a << " " << ar[n - 1].b << endl;
    return 0;
}
