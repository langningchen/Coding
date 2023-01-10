#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;
#define IsBigMonth(YearIndex, Month) ((bool)(LunarCalendarTable[YearIndex] & (0x80000 >> (Month - 1))))
#define GetLunarMonth(YearIndex) ((LunarCalendarTable[YearIndex] & 0xF00000) >> 20)
#define GetChineseNewYearDay(YearIndex) ((LunarCalendarTable[YearIndex] & 0x001F))
#define GetChineseNewYearMonth(YearIndex) ((LunarCalendarTable[YearIndex] & 0x0060) >> 5)
unsigned int LunarCalendarDay;

/*
 0~5 The day of the Chinese New Year.
 6~7 The month of the Chinese New Year.
 8~20 Big small month. If there is no leap month this year, the last digit will be ignored.
 21~23 Which month is leap month.
*/
unsigned int LunarCalendarTable[200] = {
    0x000000, 0x04AE53, 0x0A5748, 0x5526BD, 0x0D2650, 0x0D9544, 0x46AAB9, 0x056A4D, 0x09AD42, 0x24AEB6, // 1901~1909
    0x04AE4A, 0x6A4DBE, 0x0A4D52, 0x0D2546, 0x5D52BA, 0x0B544E, 0x0D6A43, 0x296D37, 0x095B4B, 0x749BC1, // 1910~1919
    0x049754, 0x0A4B48, 0x5B25BC, 0x06A550, 0x06D445, 0x4ADAB8, 0x02B64D, 0x095742, 0x2497B7, 0x04974A, // 1920~1929
    0x664B3E, 0x0D4A51, 0x0EA546, 0x56D4BA, 0x05AD4E, 0x02B644, 0x393738, 0x092E4B, 0x7C96BF, 0x0C9553, // 1930~1939
    0x0D4A48, 0x6DA53B, 0x0B554F, 0x056A45, 0x4AADB9, 0x025D4D, 0x092D42, 0x2C95B6, 0x0A954A, 0x7B4ABD, // 1940~1949
    0x06CA51, 0x0B5546, 0x555ABB, 0x04DA4E, 0x0A5B43, 0x352BB8, 0x052B4C, 0x8A953F, 0x0E9552, 0x06AA48, // 1950~1959
    0x6AD53C, 0x0AB54F, 0x04B645, 0x4A5739, 0x0A574D, 0x052642, 0x3E9335, 0x0D9549, 0x75AABE, 0x056A51, // 1960~1969
    0x096D46, 0x54AEBB, 0x04AD4F, 0x0A4D43, 0x4D26B7, 0x0D254B, 0x8D52BF, 0x0B5452, 0x0B6A47, 0x696D3C, // 1970~1979
    0x095B50, 0x049B45, 0x4A4BB9, 0x0A4B4D, 0xAB25C2, 0x06A554, 0x06D449, 0x6ADA3D, 0x0AB651, 0x093746, // 1980~1989
    0x5497BB, 0x04974F, 0x064B44, 0x36A537, 0x0EA54A, 0x86B2BF, 0x05AC53, 0x0AB647, 0x5936BC, 0x092E50, // 1990~2099
    0x0C9645, 0x4D4AB8, 0x0D4A4C, 0x0DA541, 0x25AAB6, 0x056A49, 0x7AADBD, 0x025D52, 0x092D47, 0x5C95BA, // 2000~2009
    0x0A954E, 0x0B4A43, 0x4B5537, 0x0AD54A, 0x955ABF, 0x04BA53, 0x0A5B48, 0x652BBC, 0x052B50, 0x0A9345, // 2010~2019
    0x474AB9, 0x06AA4C, 0x0AD541, 0x24DAB6, 0x04B64A, 0x69573D, 0x0A4E51, 0x0D2646, 0x5E933A, 0x0D534D, // 2020~2029
    0x05AA43, 0x36B537, 0x096D4B, 0xB4AEBF, 0x04AD53, 0x0A4D48, 0x6D25BC, 0x0D254F, 0x0D5244, 0x5DAA38, // 2030~2039
    0x0B5A4C, 0x056D41, 0x24ADB6, 0x049B4A, 0x7A4BBE, 0x0A4B51, 0x0AA546, 0x5B52BA, 0x06D24E, 0x0ADA42, // 2040~2049
    0x355B37, 0x09374B, 0x8497C1, 0x049753, 0x064B48, 0x66A53C, 0x0EA54F, 0x06B244, 0x4AB638, 0x0AAE4C, // 2050~2059
    0x092E42, 0x3C9735, 0x0C9649, 0x7D4ABD, 0x0D4A51, 0x0DA545, 0x55AABA, 0x056A4E, 0x0A6D43, 0x452EB7, // 2060~2069
    0x052D4B, 0x8A95BF, 0x0A9553, 0x0B4A47, 0x6B553B, 0x0AD54F, 0x055A45, 0x4A5D38, 0x0A5B4C, 0x052B42, // 2070~2079
    0x3A93B6, 0x069349, 0x7729BD, 0x06AA51, 0x0AD546, 0x54DABA, 0x04B64E, 0x0A5743, 0x452738, 0x0D264A, // 2080~2089
    0x8E933E, 0x0D5252, 0x0DAA47, 0x66B53B, 0x056D4F, 0x04AE45, 0x4A4EB9, 0x0A4D4C, 0x0D1541, 0x2D92B5  // 2090~2099
};
const string LunarMonthName[] = {"*", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十", "冬", "腊"};
const string LunarDayName[] = {"*", "初一", "初二", "初三", "初四", "初五",
                               "初六", "初七", "初八", "初九", "初十",
                               "十一", "十二", "十三", "十四", "十五",
                               "十六", "十七", "十八", "十九", "二十",
                               "廿一", "廿二", "廿三", "廿四", "廿五",
                               "廿六", "廿七", "廿八", "廿九", "三十"};
int MonthAdd[12] = {0,
                    31,
                    31 + 28,
                    31 + 28 + 31,
                    31 + 28 + 31 + 30,
                    31 + 28 + 31 + 30 + 31,
                    31 + 28 + 31 + 30 + 31 + 30,
                    31 + 28 + 31 + 30 + 31 + 30 + 31,
                    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
                    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
                    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
                    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30};
struct LUNAR_DAY
{
    unsigned int Year;
    unsigned int Month;
    bool IsLeapMonth;
    unsigned int Day;
};
bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && (Year % 100 != 0 || Year % 1000 == 0));
}
LUNAR_DAY LunarCalendar(unsigned int Year, unsigned int Month, unsigned int Day)
{
    int LunarNewYear, Today, CurrentMonthDayCount, CurrentMonthIndex, YearIndex = Year - 1900;
    bool IsLeapMonth = false;
    LunarNewYear = GetChineseNewYearDay(YearIndex) - 1;
    if (GetChineseNewYearMonth(YearIndex) == 2)
        LunarNewYear += 31;
    Today = MonthAdd[Month - 1] + Day - 1;
    if (IsLeapYear(Year) && Month > 2)
        Today++;
    if (Today >= LunarNewYear)
    {
        Today -= LunarNewYear;
        Month = 1;
        CurrentMonthIndex = 1;
        while (1)
        {
            CurrentMonthDayCount = 29 + IsBigMonth(YearIndex, CurrentMonthIndex);
            if (Today < CurrentMonthDayCount)
                break;
            Today -= CurrentMonthDayCount;
            CurrentMonthIndex++;
            if (Month == GetLunarMonth(YearIndex))
                IsLeapMonth = !IsLeapMonth;
            if (Month != GetLunarMonth(YearIndex) || (Month == GetLunarMonth(YearIndex) && IsLeapMonth == 0))
                Month++;
        }
        Day = Today + 1;
    }
    else
    {
        LunarNewYear -= Today;
        Today = LunarNewYear;
        Year--;
        Month = 12;
        CurrentMonthIndex = 12 + GetLunarMonth(YearIndex);
        while (1)
        {
            CurrentMonthDayCount = 29 + IsBigMonth(YearIndex, CurrentMonthIndex);
            if (Today < CurrentMonthDayCount)
                break;
            Today -= CurrentMonthDayCount;
            CurrentMonthIndex--;
            if (!IsLeapMonth)
                Month--;
            if (Month == GetLunarMonth(YearIndex))
                IsLeapMonth = !IsLeapMonth;
        }
        Day = CurrentMonthDayCount - Today + 1;
    }
    return {Year, Month, IsLeapMonth, Day};
}
int main()
{
    int CurrentYear = 2023;
    freopen("main.csv", "w", stdout);
    const string JieQiName[] = {"小寒", "大寒",
                                "立春", "雨水", "惊蛰", "春分", "清明", "谷雨",
                                "立夏", "小满", "芒种", "夏至", "小暑", "大暑",
                                "立秋", "处暑", "白露", "秋分", "寒露", "霜降",
                                "立冬", "小雪", "大雪", "冬至"};
    for (int CurrentDay = 1; CurrentDay <= 31; CurrentDay++)
    {
        for (int CurrentMonth = 1; CurrentMonth <= 12; CurrentMonth++)
        {
            if (CurrentDay <= MonthAdd[CurrentMonth] - MonthAdd[CurrentMonth - 1] + (IsLeapYear(CurrentYear) && CurrentMonth != 1))
            {
                LunarCalendarDay = 0;
                bool IsJieQi = false;
                cout << CurrentMonth << "/" << CurrentDay << "  ";
                for (int JieQiIndex = 0; JieQiIndex < 24; JieQiIndex++)
                {
                    double DaySum = 365.242 * (CurrentYear - 1900) + 6.2 + 15.22 * JieQiIndex - 1.9 * sin(0.262 * JieQiIndex);
                    int JieQiYear = 1900, JieQiMonth;
                    while (DaySum >= 365 * 4 + 1)
                    {
                        JieQiYear += 4;
                        DaySum -= 365 * 4 + 1;
                    }
                    while (DaySum >= 365)
                    {
                        JieQiYear++;
                        DaySum -= 365;
                    }
                    for (JieQiMonth = 1; JieQiMonth <= 12; JieQiMonth++)
                        if (DaySum < MonthAdd[JieQiMonth])
                            break;
                    int JieQiDay = DaySum - MonthAdd[JieQiMonth - 1];
                    if (JieQiYear == CurrentYear && JieQiMonth == CurrentMonth && JieQiDay == CurrentDay)
                    {
                        cout << JieQiName[JieQiIndex];
                        IsJieQi = true;
                        break;
                    }
                }
                if (!IsJieQi)
                {
                    LUNAR_DAY LunarDay = LunarCalendar(CurrentYear, CurrentMonth, CurrentDay);
                    if (LunarDay.Day == 1)
                    {
                        if (LunarDay.IsLeapMonth)
                            cout << "闰";
                        cout << LunarMonthName[LunarDay.Month] << "月";
                    }
                    else
                        cout << LunarDayName[LunarDay.Day];
                }
            }
            cout << "\t";
        }
        cout << endl;
    }
    return 0;
}