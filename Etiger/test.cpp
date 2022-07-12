#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

static const int kTextSize = 10;
using namespace std;

wstring stringtowstring(string Input)
{
    setlocale(LC_CTYPE, "");
    wchar_t *OutputTemp = new wchar_t[Input.size() + 1];
    mbstowcs(OutputTemp, Input.c_str(), wcslen(OutputTemp));
    wstring Output(OutputTemp);
    delete OutputTemp;
    return Output;
}

int main()
{
    wstring Temp;
    wcout << s2ws("大帅哥") << endl;
    return 0;
}