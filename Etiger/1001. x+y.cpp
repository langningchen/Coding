#include <bits/stdc++.h>
using namespace std;
struct longlonglong							//����������ṹ��
{
	unsigned long long d[1000];				//����1000000000λ������
	int len;								//����������ĳ���
	longlonglong()							//�á����캯�����������ṹ��
	{
		memset(d, 0, sizeof(d));	//�����е����ֶ���Ϊ0
		len = 0;					//������Ϊ0
	}
};
ostream &operator << (ostream &out, longlonglong a) {
	for (int i = a.len - 1; i >= 0; i--) {	//����
		out << a.d[i];						//���
	}
	out << endl;
	return out;
}
istream &operator << (istream &in, longlonglong a) {
	char c = '\0';
	while (c)
	return out;
}
longlonglong operator + (longlonglong a, longlonglong b)					//�߾���a+b
{
	longlonglong c;											//c�����
	int carry = 0;									//carry�ǽ�λ
	for (int i = 0; i < a.len || i < b.len; i++)	//�Խϳ���Ϊ����
	{
		int temp = a.d[i] + b.d[i] + carry;			//������Ӧλ���λ���
		c.d[c.len++] = temp % 10;					//��λ��Ϊ��Ϊ���
		carry = temp / 10;							//ʮλ��Ϊ�µĽ�λ
	}
	if (carry != 0)									//������Ľ�λ��Ϊ0
		c.d[c.len++] = carry;						//��ֱ�Ӹ�����������λ
	return c;										//���ش�����
}
int main() {
	longlonglong a;
	longlonglong b;
	a.d[0] = a.len = b.d[0] = b.len = 1;
	while (1) {
		longlonglong c;
		c = a + b;
		cout << c;
		a = b;
		b = c;
	}
	return 0;
}
