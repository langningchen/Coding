#include <math.h>
#include <algorithm>
#include "../../lib/BigNumber.cpp"
ll CalculatedDigits, CurrentTestNumber, LastCurrentTestNumber = -1;
string Answer;
BigNumber Input("916748676920039158098660927585380162483106680144308622407126516427934657040867096593279205767480806790022783016354924852380335745316935111903596577547340075681688305620821016129132845564805780158806771");
int main()
{
    while (LastCurrentTestNumber != CurrentTestNumber)
    {
        LastCurrentTestNumber = CurrentTestNumber;
        ll CurrentDigit = 0;
        while (Input.Data[CalculatedDigits] != PowToBigNumber(CurrentTestNumber, 23).Data[CalculatedDigits])
            CurrentDigit++, CurrentTestNumber += pow(10, CalculatedDigits);
        CalculatedDigits++, Answer.push_back(CurrentDigit + '0');
    }
    reverse(Answer.begin(), Answer.end());
    cout << Answer.substr(1, Answer.size() - 1) << endl;
    return 0;
}
// (int)(pow(10,math.log(x,10)/23))