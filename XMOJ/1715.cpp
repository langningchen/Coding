// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const ll MAX_BRICKS = 405;
// const ll INF = 0x3f3f3f3f3f3f3f3f;
// ll Bricks, Colors, ExceptBeautiful, dp[MAX_BRICKS][MAX_BRICKS][MAX_BRICKS], PaintCost[MAX_BRICKS][MAX_BRICKS], OriginalColor[MAX_BRICKS];
// int main()
// {
//     scanf("%lld%lld%lld", &Bricks, &Colors, &ExceptBeautiful);
//     for (ll Brick = 1; Brick <= Bricks; Brick++)
//         scanf("%lld", &OriginalColor[Brick]);
//     for (ll Brick = 1; Brick <= Bricks; Brick++)
//         for (ll Color = 1; Color <= Colors; Color++)
//         {
//             scanf("%lld", &PaintCost[Brick][Color]);
//             if (OriginalColor[Brick] != 0)
//             {
//                 if (OriginalColor[Brick] != Color)
//                     PaintCost[Brick][Color] = INF;
//                 else
//                     PaintCost[Brick][Color] = 0;
//             }
//         }
//     for (ll Brick = 1; Brick <= Bricks; Brick++)
//         for (ll Color = 1; Color <= Colors; Color++)
//             for (ll Beautiful = 0; Beautiful <= Bricks; Beautiful++)
//                 dp[Brick][Color][Beautiful] = INF;
//     for (ll Brick = 1; Brick <= Bricks; Brick++)
//         for (ll Color = 1; Color <= Colors; Color++)
//             for (ll Beautiful = 1; Beautiful <= Brick; Beautiful++)
//             {
//                 // printf("dp[%lld][%lld][%lld] = ", Brick, Color, Beautiful);
//                 // fflush(stdout);
//                 for (ll LastColor = 1; LastColor <= Colors; LastColor++)
//                     dp[Brick][Color][Beautiful] = min(min(dp[Brick][Color][Beautiful],
//                                                           dp[Brick - 1][LastColor][Beautiful - (Color != LastColor)] + PaintCost[Brick][Color]),
//                                                       INF);
//                 // printf("%lld\n", (dp[Brick][Color][Beautiful] == INF ? -1 : dp[Brick][Color][Beautiful]));
//             }
//     ll Answer = INF;
//     for (ll Color = 1; Color <= Colors; Color++)
//         Answer = min(Answer, dp[Bricks][Color][ExceptBeautiful]);
//     printf("%lld\n", (Answer == INF ? -1 : Answer));
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX_BRICKS = 405;
const ll MAX_COLORS = 405;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
ll Bricks, Colors, ExceptBeautiful, PaintCost[MAX_BRICKS][MAX_COLORS], OriginalColor[MAX_BRICKS], dp[2][MAX_COLORS][MAX_BRICKS];
int main()
{
    scanf("%lld%lld%lld", &Bricks, &Colors, &ExceptBeautiful);
    for (ll Brick = 1; Brick <= Bricks; Brick++)
        scanf("%lld", &OriginalColor[Brick]);
    for (ll Brick = 1; Brick <= Bricks; Brick++)
        for (ll Color = 1; Color <= Colors; Color++)
        {
            scanf("%lld", &PaintCost[Brick][Color]);
            if (OriginalColor[Brick] != 0)
                PaintCost[Brick][Color] = OriginalColor[Brick] == Color ? 0 : INF;
        }
    for (ll Brick = 1; Brick <= Bricks; Brick++)
    {
        for (ll Color = 1; Color <= Colors; Color++)
            for (ll Beautiful = 0; Beautiful <= Bricks; Beautiful++)
                dp[Brick % 2][Color][Beautiful] = INF;
        for (ll Beautiful = 1; Beautiful <= Brick; Beautiful++)
        {
            ll MinValue = INF, MinIndex = 0, SecondMinValue = INF;
            for (ll LastColor = 1; LastColor <= Colors; LastColor++)
            {
                ll CurrentValue = dp[(Brick + 1) % 2][LastColor][Beautiful - 1];
                if (CurrentValue < MinValue)
                {
                    SecondMinValue = MinValue;
                    MinValue = CurrentValue;
                    MinIndex = LastColor;
                }
                else if (CurrentValue < SecondMinValue)
                    SecondMinValue = CurrentValue;
            }
            for (ll Color = 1; Color <= Colors; Color++)
                dp[Brick % 2][Color][Beautiful] = min(min(dp[(Brick + 1) % 2][Color][Beautiful],
                                                          Color != MinIndex ? MinValue : SecondMinValue) +
                                                          PaintCost[Brick][Color],
                                                      INF);
        }
    }
    ll Answer = INF;
    for (ll Color = 1; Color <= Colors; Color++)
        Answer = min(Answer, dp[Bricks % 2][Color][ExceptBeautiful]);
    printf("%lld\n", (Answer == INF ? -1 : Answer));
    return 0;
}
