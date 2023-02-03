#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 205;
const int M = 5;
bool dp[N][N][M];
bool CanTransfer[M][M][M];
int q[M], Length = 0;
char TransferredString[N];
int CharToInt(char i)
{
    if (i == 'W')
        return 1;
    if (i == 'I')
        return 2;
    if (i == 'N')
        return 3;
    if (i == 'G')
        return 4;
}
int main()
{
    for (int i = 1; i <= 4; i++)
        scanf("%d", &q[i]);
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= q[i]; j++)
        {
            char Temp[5];
            scanf("%s", &Temp);
            CanTransfer[i][CharToInt(Temp[0])][CharToInt(Temp[1])] = true;
        }

    scanf("%s", TransferredString);
    Length = strlen(TransferredString);
    for (int i = 0; i < Length; i++)
        dp[i][i][CharToInt(TransferredString[i])] = true;

    for (int CurrentLength = 1; CurrentLength < Length; CurrentLength++)
        for (int Left = 0; Left < Length - CurrentLength; Left++)
        {
            int Right = Left + CurrentLength;
            for (int Middle = Left; Middle < Right; Middle++)
                for (int ChangeFrom = 1; ChangeFrom <= 4; ChangeFrom++)
                    for (int ChangeTo1 = 1; ChangeTo1 <= 4; ChangeTo1++)
                        for (int ChangeTo2 = 1; ChangeTo2 <= 4; ChangeTo2++)
                            if (CanTransfer[ChangeFrom][ChangeTo1][ChangeTo2] &&
                                dp[Left][Middle][ChangeTo1] &&
                                dp[Middle + 1][Right][ChangeTo2])
                                dp[Left][Right][ChangeFrom] = true;
        }
    if (dp[0][Length - 1][1])
        printf("W");
    if (dp[0][Length - 1][2])
        printf("I");
    if (dp[0][Length - 1][3])
        printf("N");
    if (dp[0][Length - 1][4])
        printf("G");
    if (dp[0][Length - 1][1] == false &&
        dp[0][Length - 1][2] == false &&
        dp[0][Length - 1][3] == false &&
        dp[0][Length - 1][4] == false)
        printf("The name is wrong!");
    return 0;
}
