#include<bits/stdc++.h>
using namespace std;
int prime[100000];                                    //primeΪ�����б�
void Find_Prime()                                    //Ѱ������ 
{
    int pNum = 2;                                    //pNumΪ�������� 
    bool p[100000] = {0};                            //�����Ƿ�Ϊ�����б� 
    for (int i = 2; i < 100000; i++)                //��2��ʼ��i<maxn������ע�ⲻ��д��i<=maxn 
    {
        if (p[i] == false)                            //���i������ 
        {
            prime[pNum] = prime[pNum - 1] + 1;    //������i�浽prime������ 
            pNum++;
            for (int j = i + i; j < 100000; j += i)    //ѡ������i�ı�����ѭ����������д��j<=maxn 
                p[j] = true;                        //ɸȥ 
        }
        else
        {
            prime[pNum] = prime[pNum - 1];        //������i�浽prime������ 
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
