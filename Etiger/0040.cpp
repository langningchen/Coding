#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 10;
const ll MOD = 100000000;
class Matrix
{
public:
    ll r, c;
    ll data[N][N];
    Matrix(int _r, int _c)
    {
        r = _r;
        c = _c;
        memset(data, 0, sizeof(data));
    }
    void print()
    {
        cout << r << endl;
        cout << c << endl;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }
    Matrix operator*(const Matrix &m) const
    {
        Matrix ans(r, m.c);
        for (ll i = 0; i < r; i++)
            for (ll j = 0; j < m.c; j++)
                for (ll k = 0; k < c; k++)
                    ans.data[i][j] = (ans.data[i][j] + data[i][k] * m.data[k][j]) % MOD;
        return ans;
    }
    Matrix operator^(ll p) const
    {
        Matrix ans(r, c);
        Matrix x = *this;
        for (ll i = 0; i < r; i++)
            ans.data[i][i] = 1;
        while (p)
        {
            if (p & 1)
                ans = ans * x;
            x = x * x;
            p >>= 1;
        }
        return ans;
    }
};
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
ll fib(ll n)
{
    Matrix A(2, 2);
    A.data[0][0] = 1;
    A.data[0][1] = 1;
    A.data[1][0] = 1;
    A.data[1][1] = 0;
    if (n <= 1)
    {
        return 1;
    }
    Matrix f10(2, 1);
    f10.data[0][0] = 1;
    f10.data[1][0] = 1;
    Matrix fnn_1 = (A ^ (n - 1)) * f10;
    return fnn_1.data[0][0] % MOD;
}
int main()
{
    ll n, m;
    cin >> n >> m;
    cout << fib(gcd(n, m) - 1) << endl;
    return 0;
}
