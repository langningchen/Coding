#include<bits/stdc++.h>
using namespace std;
int prime[100000];                                    //prime为素数列表
void Find_Prime()                                    //寻找素数 
{
    int pNum = 2;                                    //pNum为素数个数 
    bool p[100000] = {0};                            //定义是否为素数列表 
    for (int i = 2; i < 100000; i++)                //从2开始，i<maxn结束，注意不能写成i<=maxn 
    {
        if (p[i] == false)                            //如果i是素数 
        {
            prime[pNum] = prime[pNum - 1] + 1;    //把素数i存到prime数组中 
            pNum++;
            for (int j = i + i; j < 100000; j += i)    //选择所有i的倍数，循环条件不能写成j<=maxn 
                p[j] = true;                        //筛去 
        }
        else
        {
            prime[pNum] = prime[pNum - 1];        //把素数i存到prime数组中 
            pNum++;
        }
    }
}
int main() {
    Find_Prime();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << prime[b] - prime[a - 1] << ' ';
    }
    return 0;
}
