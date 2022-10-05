#include "../../lib/Curl.cpp"
#include <unistd.h>
int main()
{
    GetDataToFile("https://login.dingtalk.com/user/qrcode/generate.jsonp");
    string QRCode = GetDataFromFileToString().substr(42, 36);
    GetDataToFile("https://www.chitus.com/ewm/createPc?config={%22content%22%3A%22http%3A%2F%2Fqr.dingtalk.com%2Faction%2Flogin%3Fcode%3D" + QRCode + "%22}&k=89758512345678", "Header.tmp", "LoginQRCode.png");
    while (1)
    {
        GetDataToFile("https://login.dingtalk.com/user/qrcode/is_logged.jsonp?qrcode=" + QRCode);
        json IsLogged = json::parse(GetDataFromFileToString().substr(16, GetDataFromFileToString().size() - 18));
        if (!IsLogged["success"].as_bool())
        {
            cout << IsLogged["errorCode"].as_integer() << endl
                 << IsLogged["errorMsg"].as_string() << endl
                 << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}