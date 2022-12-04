#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
ll k, n, e, d;
ld p, q;
int main()
{
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        cin >> n >> e >> d;
        p = (n + 2 - e * d - (ll)sqrt((e * d - n - 2) * (e * d - n - 2) - 4 * n)) / 2.0;
        q = n / p;
        if (p != (int)p || q != (int)q || p == 0 || q == 0 || p * q != n || (p - 1) * (q - 1) + 1 != e * d)
        {
            cout << "NO" << endl;
            continue;
        }
        cout << (ll)p << " " << (ll)q << endl;
    }
    return 0;
}

/*
    pq=n ed=(p-1)(q-1)+1
    p=n/q ed=pq-p-q+1+1
    ed=n-n/q-q+2
    n-n/q-q+2-ed=0
    nq-n-q^2+2q-edq=0
    -nq+n+q^2-2q+edq=0
    q^2+edq-nq-2q+n=0
    q^2+(ed-n-2)q+n=0
    a=1 b=ed-n-2 c=n
    Δ=(ed-n-2)^2-4n
    p=(n+2-ed+√((ed-n-2)^2-4n))/2
    q=n/p;
*/
