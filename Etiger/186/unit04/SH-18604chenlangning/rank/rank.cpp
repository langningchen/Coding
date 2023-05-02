#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
const int M = 105;
const int INF = 0x7FFFFFFF;
struct TOTALSCORE
{
    string Name;
    ll TotalScore;
    short StudentID;
};
int n;
unsigned short NameMaxLength;
short ScoreList[M][N];
TOTALSCORE TotalScoreList[M];
map<string, short> NameList;
bool cmp(const TOTALSCORE &cmp1, const TOTALSCORE &cmp2)
{
    if (cmp1.TotalScore != cmp2.TotalScore)
        return cmp1.TotalScore > cmp2.TotalScore;
    else
        return cmp1.Name < cmp2.Name;
}
int main()
{
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);
    scanf("%d", &n);
    for (short i = 0; i < n; i++)
    {
        short x;
        scanf("%hd", &x);
        for (short j = 0; j < x; j++)
        {
            char Temp[256];
            string Name;
            scanf("%s", Temp);
            Name = Temp;
            int StudentID = NameList[Name];
            if (StudentID == 0)
            {
                if (Name.size() > NameMaxLength)
                    NameMaxLength = Name.size();
                StudentID = NameList.size();
                NameList[Name] = StudentID;
                TotalScoreList[StudentID].Name = Name;
                TotalScoreList[StudentID].StudentID = StudentID;
            }
            short Score;
            scanf("%hd", &Score);
            ScoreList[StudentID][i] = (Score == 0 ? -1 : Score);
            TotalScoreList[StudentID].TotalScore += Score;
        }
    }
    sort(TotalScoreList + 1, TotalScoreList + NameList.size() + 1, cmp);
    for (unsigned int i = 1; i < NameList.size() + 1; i++)
    {
        printf("%s", TotalScoreList[i].Name.c_str());
        for (unsigned int j = 0; j < NameMaxLength - TotalScoreList[i].Name.size(); j++)
            putchar('_');
        putchar(' ');
        printf("%lld", TotalScoreList[i].TotalScore);
        if (TotalScoreList[i].TotalScore < 100)
            putchar('_');
        if (TotalScoreList[i].TotalScore < 10)
            putchar('_');
        putchar(':');
        putchar(' ');
        for (int j = 0; j < n; j++)
        {
            switch (ScoreList[TotalScoreList[i].StudentID][j])
            {
            case -1:
                putchar('0');
                break;
            case 0:
                putchar('_');
                break;
            default:
                cout << ScoreList[TotalScoreList[i].StudentID][j];
                break;
            }
            if (ScoreList[TotalScoreList[i].StudentID][j] < 100)
                putchar('_');
            if (ScoreList[TotalScoreList[i].StudentID][j] < 10)
                putchar('_');
            putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}