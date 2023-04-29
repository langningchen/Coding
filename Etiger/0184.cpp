#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, x[N][3];
int check(int A[3], int B[3])
{
	if (A[1] > B[1])
		return 1;
	else if (A[1] < B[1])
		return 0;
	else
	{
		if (A[2] > B[2])
			return 0;
		else if (A[2] < B[2])
			return 1;
		else
		{
			if (A[0] > B[0])
				return 0;
			else
				return 1;
		}
	}
}

int Partition(int A[][3], int left, int right)
{
	int temp[3] = {A[left][0], A[left][1], A[left][2]};
	while (left < right)
	{
		while (left < right && check(A[right], temp))
			right--;
		A[left][0] = A[right][0];
		A[left][1] = A[right][1];
		A[left][2] = A[right][2];
		while (left < right && !check(A[left], temp))
			left++;
		A[right][0] = A[left][0];
		A[right][1] = A[left][1];
		A[right][2] = A[left][2];
	}
	A[left][0] = temp[0];
	A[left][1] = temp[1];
	A[left][2] = temp[2];
	return left;
}

void quickSort(int A[][3], int left, int right)
{
	if (left < right)
	{
		int pos = Partition(A, left, right);
		quickSort(A, left, pos - 1);
		quickSort(A, pos + 1, right);
	}
}

int main()
{
	freopen("escape.in", "r", stdin);
	freopen("escape.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> x[i][0] >> x[i][1] >> x[i][2];
	quickSort(x, 0, n - 1);
	for (int i = n - 1; i >= 0; i--)
	{
		cout << x[i][0] << endl;
	}
	return 0;
}
