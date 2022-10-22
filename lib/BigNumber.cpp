#include <iostream>
#include <string>
#include <string.h>
using namespace std;
typedef long long ll;
class BigNumber
{
public:
    int Data[100000];
    ll Length;
    BigNumber();
    BigNumber(char x[]);
    BigNumber(const char x[]);
    BigNumber(string x);
    BigNumber(int x);
    BigNumber(ll x);
    string ToString();
};
BigNumber::BigNumber()
{
    memset(Data, 0, sizeof(Data));
    Length = 0;
}
BigNumber::BigNumber(char x[])
{
    Length = strlen(x);
    for (ll i = 0; i < Length; i++)
        Data[i] = x[Length - i - 1] - '0';
}
BigNumber::BigNumber(const char x[])
{
    Length = strlen(x);
    for (ll i = 0; i < Length; i++)
        Data[i] = x[Length - i - 1] - '0';
}
BigNumber::BigNumber(string x)
{
    Length = x.size();
    for (ll i = 0; i < Length; i++)
        Data[i] = x[Length - i - 1] - '0';
}
BigNumber::BigNumber(int x)
{
    int i = 0;
    while (x > 0)
    {
        Data[i++] = x % 10;
        x /= 10;
    }
    Length = i;
}
BigNumber::BigNumber(ll x)
{
    ll i = 0;
    while (x > 0)
    {
        Data[i++] = x % 10;
        x /= 10;
    }
    Length = i;
}
string BigNumber::ToString()
{
    string Output = 0;
    for (int i = Length - 1; i >= 0; i--)
        Output.push_back(Data[i] + '0');
    return Output;
}
BigNumber
operator+(BigNumber x, BigNumber y);
BigNumber operator-(BigNumber x, BigNumber y);
BigNumber operator*(BigNumber x, ll y);
BigNumber operator/(BigNumber x, ll y);
BigNumber operator%(BigNumber x, ll y);
void operator+=(BigNumber &x, BigNumber y);
void operator-=(BigNumber &x, BigNumber y);
void operator*=(BigNumber &x, ll y);
void operator/=(BigNumber &x, ll y);
bool operator<(BigNumber x, BigNumber y);
bool operator>(BigNumber x, BigNumber y);
bool operator==(BigNumber x, BigNumber y);
bool operator!=(BigNumber x, BigNumber y);
BigNumber operator+(BigNumber x, BigNumber y)
{
    BigNumber Output;
    ll carry = 0;
    for (ll i = 0; i < x.Length || i < y.Length; i++)
    {
        ll temp = x.Data[i] + y.Data[i] + carry;
        Output.Data[Output.Length++] = temp % 10;
        carry = temp / 10;
    }
    if (carry != 0)
        Output.Data[Output.Length++] = carry;
    return Output;
}
BigNumber operator-(BigNumber x, BigNumber y)
{
    BigNumber Output;
    for (ll i = 0; i < x.Length || i < y.Length; i++)
    {
        if (x.Data[i] < y.Data[i])
        {
            x.Data[i + 1]--;
            x.Data[i] += 10;
        }
        Output.Data[Output.Length++] = x.Data[i] - y.Data[i];
    }
    while (Output.Length - 1 >= 1 && Output.Data[Output.Length - 1] == 0)
        Output.Length--;
    return Output;
}
BigNumber operator*(BigNumber x, ll y)
{
    BigNumber Output;
    ll carry = 0;
    for (ll i = 0; i < x.Length; i++)
    {
        ll temp = x.Data[i] * y + carry;
        Output.Data[Output.Length++] = temp % (ll)10;
        carry = temp / (ll)10;
    }
    while (carry != 0)
    {
        Output.Data[Output.Length++] = carry % 10;
        carry /= 10;
    }
    return Output;
}
BigNumber operator/(BigNumber x, ll y)
{
    ll r = 0;
    BigNumber Output;
    Output.Length = x.Length;
    for (ll i = x.Length - 1; i >= 0; i--)
    {
        r = r * 10 + x.Data[i];
        if (r < y)
            Output.Data[i] = 0;
        else
        {
            Output.Data[i] = r / y;
            r = r % y;
        }
    }
    while (Output.Length - 1 >= 1 && Output.Data[Output.Length - 1] == 0)
        Output.Length--;
    return Output;
}
BigNumber operator%(BigNumber x, ll y)
{
    return x - x / y;
}
void operator+=(BigNumber &x, BigNumber y)
{
    x = x + y;
}
void operator-=(BigNumber &x, BigNumber y)
{
    x = x - y;
}
void operator*=(BigNumber &x, ll y)
{
    x = x * y;
}
void operator/=(BigNumber &x, ll y)
{
    x = x / y;
}
bool operator<(BigNumber x, BigNumber y)
{
    if (x.Length < y.Length)
        return true;
    else if (x.Length > y.Length)
        return false;
    for (ll i = x.Length - 1; i >= 0; i--)
        if (x.Data[i] < y.Data[i])
            return true;
        else if (x.Data[i] > y.Data[i])
            return false;
    return false;
}
bool operator>(BigNumber x, BigNumber y)
{
    return y > x;
}
bool operator==(BigNumber x, BigNumber y)
{
    return !(x < y) && !(y < x);
}
bool operator!=(BigNumber x, BigNumber y)
{
    return !(x == y);
}
ostream &operator<<(ostream &OutputStream, BigNumber x)
{
    for (ll i = x.Length - 1; i >= 0; i--)
        OutputStream << x.Data[i];
    return OutputStream;
}
istream &operator>>(istream &InputStream, BigNumber &x)
{
    string Data;
    InputStream >> Data;
    x = BigNumber(Data);
    return InputStream;
}
BigNumber PowToBigNumber(ll x, ll y)
{
    BigNumber Output = 1;
    for (int i = 0; i < y; i++)
        Output *= x;
    return Output;
}