#include <bits/stdc++.h>                        //ʹ������ͷ�ļ��� 
using namespace std;                            //ʹ�ñ�׼���ֿռ� 
const int N = 20;                                //�������ֵ 
const int CLR = 4;                                //������ɫ���� 
char colors[CLR] = {'\0', 'B', 'G', 'R'};        //����������ɫ 
int n, p[N];                                    //�������ɫ������ 
void print() {                                    //��� 
    for (int i = 1; i <= n; i++)                //ÿһ�� 
        cout << colors[p[i]];                    //��� 
    cout << endl;                                //���� 
}                                                //������ 
void dfs(int x) {                                //���� 
    if (x == n + 1) {                            //������˽�β 
        print();                                 //��� 
        return;                                    //�˳�
    }                                             //������
    if (p[x] >= 1) {                            //����ѹ̶� 
        dfs(x + 1);                             //��һ�� 
        return;                                    //���� 
    }                                             //������ 
    for (int i = 1; i < CLR; i++)                //ÿһ����ɫ 
        if (x == 1 && p[2] != i ||                //����ǵ�һ�� 
            x == n && p[x - 1] != i ||            //��������һ�� 
            p[x - 1] != i && p[x + 1] != i) {    //������м� 
            p[x] = i;                            //��ɫ������Ϊ����ɫ 
            dfs(x + 1);                            //��һ�� 
            p[x] = 0;                            //�ָ��ֳ� 
        }                                        //������
}                                                //������
int main() {
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    char ch;                                    //��������
    while (cin >> ch) {                            //���� 
        ++n;                                    //��������һ 
        if (ch == 'B')                            //�����B 
            p[n] = 1;                            //��Ϊ1 
        else if (ch == 'G')                        //�����G 
            p[n] = 2;                            //��Ϊ2 
        else if (ch == 'R')                        //�����R 
            p[n] = 3;                            //��Ϊ3 
        else p[n] = 0;                            //δ����Ϊ0 
    }                                            //������
    dfs(1);                                        //���� 
    return 0;                                    //����0 
}                                                //������