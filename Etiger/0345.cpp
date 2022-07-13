#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int m, pNum = 2, prime[N];
bool p[N];
void Find_Prime()
{
    for (int i = 2; i < N; i++)
    {
        if (p[i] == false)
        {
            prime[pNum] = prime[pNum - 1] + 1;
            pNum++;
            for (int j = i + i; j < N; j += i)
                p[j] = true;
        }
        else
        {
            prime[pNum] = prime[pNum - 1];
            pNum++;
        }
    }
}
int main()
{
    Find_Prime();
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << prime[b] - prime[a - 1] << " ";
    }
    return 0;
}
