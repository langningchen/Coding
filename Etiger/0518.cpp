#include <iostream>                        //��������� 
#define N 30                            //�������ֵ 
using namespace std;                    //ʹ�ñ�׼���ֿռ� 
int m, n, p[N];                            //������� 
bool vst[N];                            //�Ƿ񱻷��ʹ� 
void print() {                            //��� 
    for (int i = 1; i <= m - 1; i++)    //ÿһ���� 
        cout << p[i] << " ";            //��� 
    cout << p[m] << endl;                //��ֹ��ĩ�пո� 
}                                        //������ 
void dfs(int x) {                        //ö�� 
    if (x == m + 1) {                    //���˽�β 
        print();                        //��������� 
        return;                            //ֹͣ���� 
    }                                    //������ 
    for (int i = 1; i <= n; i++)        //��һ�������ÿһ�� 
        if (!vst[i]) {                    //���û�з��ʹ� 
            vst[i] = 1;                    //���÷��ʹ�Ϊ1 
            p[x] = i;                    //������ĵ�ǰ����Ϊ��ǰ���� 
            dfs(x + 1);                    //�ݹ� 
            vst[i] = 0;                    //�����ֳ� 
        }                                //������ 
}                                        //������ 
int main() {                            //������ 
    cin >> n;                            //���� 
    m = n;                                //ѡ���������ܸ���һ�� 
    dfs(1);                                //ö�� 
    return 0;                            //����0 
}                                        //������ 
