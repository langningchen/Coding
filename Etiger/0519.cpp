#include <bits/stdc++.h>                //����ͷ�ļ� 
#include <algorithm>                    //�㷨��ͷ�ļ� 
#define N 150                            //�������ֵ��120Ҳ���� 
using namespace std;                    //ʹ�ñ�׼���ֿռ� 
string ans[N];                            //�� 
string name[N];                            //���� 
int m, n, p[N], num = 0;                //�����ȱ��� 
bool vst[N];                            //�Ƿ񱻷��ʹ� 
void print() {                            //�������麯�� 
    ans[num] = "";                        //��ǰ����Ϊ�� 
    for (int i = 1; i <= m; i++)        //����ÿһ������ 
        ans[num] += name[p[i]];            //��ӵ�ĩβ 
    ans[num] += " wang";                //��Ӻ�׺ 
    num++;                                //����������һ 
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
    freopen("name1.in","r",stdin);
    freopen("name1.out","w",stdout);
    cin >> n;                            //������� 
    for (int i = 1; i <= n; i++)        //ÿһ������ 
        cin >> name[i];                    //�������� 
    m = n;                                //ѡ���������ܸ���һ�� 
    sort(name, name + n);                //���������� 
    dfs(1);                                //ö�� 
    sort(ans, ans + num);                //�Դ����� 
    for (int i = 0; i < num; i++)        //ÿһ���� 
        cout << ans[i].data() << endl;    //��� 
    return 0;                            //����0 
}                                        //������ 
