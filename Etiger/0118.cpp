#include <iostream>
using namespace std;
long long gcd(long long a, long long b)                //���Լ��
{
    return !b ? a : gcd(b, a % b);    //շת����� 
}
long long lcm(long long a, long long b)            //��С������ 
{
    return a / gcd(a, b) * b;    //a * b = gcd(a, b)
} 
int main() {
    long long a, b;
    cin >> a >> b;
    cout << lcm(a, b) << endl;
    return 0;
}
