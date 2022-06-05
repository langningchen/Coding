#include <iostream>
using namespace std;
long long gcd(long long a, long long b)                //最大公约数
{
    return !b ? a : gcd(b, a % b);    //辗转相除法 
}
long long lcm(long long a, long long b)            //最小公倍数 
{
    return a / gcd(a, b) * b;    //a * b = gcd(a, b)
} 
int main() {
    long long a, b;
    cin >> a >> b;
    cout << lcm(a, b) << endl;
    return 0;
}
