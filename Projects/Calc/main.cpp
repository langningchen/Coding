#include "../../lib/BigNumber.cpp"
#pragma GCC optimize("Ofast,unroll-loops")
ll CurrentTestNumber, LastCurrentTestNumber = -1, CurrentPow = 1;
short CalculatedDigits;
BigNumber Input("916748676920039158098660927585380162483106680144308622407126516427934657040867096593279205767480806790022783016354924852380335745316935111903596577547340075681688305620821016129132845564805780158806771");
int main()
{
    while (LastCurrentTestNumber != CurrentTestNumber)
    {
        LastCurrentTestNumber = CurrentTestNumber;
        while (Input.Data[CalculatedDigits] != PowToBigNumber(CurrentTestNumber, 23).Data[CalculatedDigits])
            CurrentTestNumber += CurrentPow;
        CalculatedDigits++, CurrentPow *= 10;
    }
    cout << CurrentTestNumber << endl;
    return 0;
}
// (int)(pow(10,math.log(x,10)/23))