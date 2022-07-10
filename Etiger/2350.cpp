#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e7 + 5;
char suan[N][7];
char xian[N][7];
unsigned short num[N];
unsigned short numn = 0;
unsigned short s = 0, n = 0, q = 0, x[1005];
int atoi_my(char *Input)
{
	int ans = 0;
	for (int i = 0; i < strlen(Input); i++)
	{
		if (Input[i] < '0' || Input[i] > '9')
		{
			cout << "ERROR" << endl;
			return -1;
		}
		ans = ans * 10 + (Input[i] - '0');
	}
	return ans;
}
void itoa_my(unsigned int Input, char *Output, int Radix)
{
	unsigned int n = 0;
	do
	{
		Output[n++] = Input % 10 + '0';
		Input /= 10;
	} while (Input);
	Output[n] = '\0';
}
int main()
{
	//	freopen("expr.in", "r", stdin);
	//	freopen("expr.out", "w", stdout);
	do
	{
		scanf("%s", suan[s++]);
	} while ((suan[s - 1][0] == '&') || (suan[s - 1][0] == '|') || (suan[s - 1][0] == '!') || (suan[s - 1][0] == 'x'));
	n = atoi_my(suan[--s]);
	for (unsigned int i = 1; i <= n; i++)
	{
		cin >> x[i];
	}
	cin >> q;
	for (unsigned int i = 0; i < q; i++)
	{
		int now = 0;
		cin >> now;
		memset(xian, 0, sizeof(xian));
		for (unsigned int j = 0; j < s; j++)
		{
			if (suan[j][0] == 'x')
			{
				char temp[10];
				char temp2[10];
				memset(temp, 0, sizeof(temp));
				memset(temp2, 0, sizeof(temp2));
				for (unsigned int k = 0; k < 9; k++)
				{
					temp[k] = suan[j][k + 1];
				}
				itoa_my(now, temp2, 10);
				if (strcmp(temp, temp2) == 0)
				{
					itoa_my((x[atoi_my(temp)] == 0 ? 1 : 0), xian[j], 10);
				}
				else
				{
					itoa_my(x[atoi_my(temp)], xian[j], 10);
				}
			}
			else
			{
				strcpy(xian[j], suan[j]);
			}
		}
		memset(num, 0, sizeof(num));
		numn = 0;
		for (unsigned int i = 0; i < s; i++)
		{
			if (xian[i][0] == '&')
			{
				unsigned int num1 = num[--numn];
				unsigned int num2 = num[--numn];
				num[numn++] = num1 & num2;
			}
			else if (xian[i][0] == '|')
			{
				unsigned int num1 = num[--numn];
				unsigned int num2 = num[--numn];
				num[numn++] = num1 | num2;
			}
			else if (xian[i][0] == '!')
			{
				unsigned int num1 = num[--numn];
				num[numn++] = (num1 ? 0 : 1);
			}
			else
			{
				num[numn++] = atoi_my(xian[i]);
			}
		}
		//		cout << (numn == 1) << endl;
		cout << num[0] << endl;
	}
	//	cout << endl;
	//	for (unsigned int i = 0; i < s; i++) {
	//		cout << suan[i] << " ";
	//	}
	//	cout << endl;
	return 0;
}
