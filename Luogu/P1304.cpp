#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
int n;
bool IsPrime[N];
vector<int> Primes;
int main()
{
    fill(IsPrime, IsPrime + N, true);
    IsPrime[0] = IsPrime[1] = false;
    for (int i = 2; i < N; i++)
        if (IsPrime[i])
        {
            Primes.push_back(i);
            for (int j = i; j * i < N; j++)
                IsPrime[j * i] = false;
        }
    cin >> n;
    for (int i = 4; i <= n; i += 2)
    {
        for (vector<int>::iterator vit = Primes.begin(); vit != Primes.end(); vit++)
        {
            if (IsPrime[i - *vit])
            {
                cout << i << "=" << *vit << "+" << i - *vit << endl;
                break;
            }
        }
    }
    return 0;
}