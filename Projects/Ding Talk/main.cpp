#include "../../Lib/Curl.hpp"
#include <unistd.h>
string JSONPToJSON(string Input)
{
    return Input.substr(Input.find("{"), Input.find_last_of("}") - Input.find("{") + 1);
}
int main()
{
    GetDataToFile("https://login.dingtalk.com/user/qrcode/generate.jsonp");
    json QRCodeResult = json::parse(JSONPToJSON(GetDataFromFileToString()));
    if (!QRCodeResult["success"].as_bool())
    {
        cout << "Login QRCode generate failed!" << endl;
        return 0;
    }
    string QRCodeDetail = QRCodeResult["result"].as_string();
    GetDataToFile("https://api.qrserver.com/v1/create-qr-code/?size=150%C3%97150&data=" +
                      URLEncode("http://qr.dingtalk.com/action/login?code=" + QRCodeDetail),
                  "Header.tmp",
                  "LoginQRCode.png");
    while (1)
    {
        GetDataToFile("https://login.dingtalk.com/user/qrcode/is_logged.jsonp?qrcode=" + QRCodeDetail);
        json IsLogged = json::parse(
            GetDataFromFileToString().substr(
                16, GetDataFromFileToString().size() - 18));
        if (IsLogged["success"].as_bool())
        {
            break;
        }
    }
    // Clean();
    return 0;
}