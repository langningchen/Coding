#include <bits/stdc++.h>
using namespace std;
struct longlonglong							//定义大整数结构体
{
	unsigned long long d[1000];				//定义1000000000位的整数
	int len;								//定义大整数的长度
	longlonglong()							//用“构造函数”初数化结构体
	{
		memset(d, 0, sizeof(d));	//把所有的数字都设为0
		len = 0;					//长度设为0
	}
};
ostream &operator << (ostream &out, longlonglong a) {
	for (int i = a.len - 1; i >= 0; i--) {	//倒序
		out << a.d[i];						//输出
	}
	out << endl;
	return out;
}
istream &operator << (istream &in, longlonglong a) {
	char c = '\0';
	while (c)
	return out;
}
longlonglong operator + (longlonglong a, longlonglong b)					//高精度a+b
{
	longlonglong c;											//c储存答案
	int carry = 0;									//carry是进位
	for (int i = 0; i < a.len || i < b.len; i++)	//以较长的为界限
	{
		int temp = a.d[i] + b.d[i] + carry;			//两个对应位与进位相加
		c.d[c.len++] = temp % 10;					//个位数为该为结果
		carry = temp / 10;							//十位数为新的进位
	}
	if (carry != 0)									//如果最后的进位不为0
		c.d[c.len++] = carry;						//则直接赋给结果的最高位
	return c;										//返回大整数
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
