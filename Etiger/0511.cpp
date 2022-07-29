#include <bits/stdc++.h>
using namespace std;
const int N = 205;
string s;
int k, i, n[N], new_X[N], X[N], result[N], product[N], temp2[N];
void multi_low(int x[], int yy, int z[])
{
    int up = 0;
    for (int ii = 1; ii <= k; ii++)
    {
        z[ii] = (x[ii] * yy + up) % 10;
        up = (x[ii] * yy + up) / 10;
    }
}
void multi_high(int x[], int y[], int z[])
{
    int up = 0;
    int j;
    for (int ii = 1; ii <= k; ii++)
    {
        for (j = 1; j <= k; j++)
        {
            z[ii + j - 1] += (x[j] * y[ii] + up) % 10;
            up = (x[j] * y[ii] + up) / 10;
        }
        up = 0;
    }
    for (int ii = 1; ii <= k; ii++)
    {
        z[ii + 1] += z[ii] / 10;
        z[ii] %= 10;
    }
}
void printB(int *buf, int length)
{
    for (i = length; i >= 1; i--)
        cout << *(buf + i) << " ";
    cout << endl;
}
void copyAtoB(int *A, int *B, int k)
{
    for (int i = 1; i <= k; i++)
        *(B + i) = *(A + i);
}
void A_AxB(int *A, int *B, int len)
{
    memset(temp2, 0, sizeof temp2);
    multi_high(A, B, temp2);
    copyAtoB(temp2, A, len);
}
int main()
{
    cin >> s;
    cin >> k;

    int temp = 0, len = s.size();
    for (i = len - 1; i >= len - k; i--)
        n[++temp] = s[i] - '0';

    copyAtoB(n, X, k);

    int pos = 1;

    while (pos <= k)
    {
        copyAtoB(n, product, k);
        copyAtoB(X, new_X, k);

        int tmp = 0;
        while (tmp < 11)
        {
            tmp++;
            A_AxB(product, X, k);
            if (product[pos] == n[pos])
                break;
            A_AxB(new_X, X, k);
        }
        if (tmp >= 11)
        {
            cout << -1;
            return 0;
        }
        copyAtoB(new_X, X, k);

        if (pos == 1)
        {
            result[1] = tmp;
        }
        else
        {
            int temp[N];
            memset(temp, 0, sizeof temp);
            multi_low(result, tmp, temp);
            for (int i = 1; i <= 100; i++)
                result[i] = temp[i];
        }
        pos++;
    }
    int i = N;
    while (result[i] == 0)
        i--;
    for (int k = i; k >= 1; k--)
    {
        cout << result[k];
    }
    cout << endl;
    return 0;
}
