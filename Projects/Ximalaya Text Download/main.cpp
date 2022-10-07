#include "../../lib/Curl.cpp"
#include "../../lib/lodepng.cpp"
#include "../../lib/jpeg/jpeglib.h"
#include "SHA1.cpp"
const string WEBSign = "WEB-V1-PRODUCT-E7768904917C4154A925FBE1A3848BC3E84E2C7770744E56AFBC9600C267891F";
const long long INF = 0x7FFFFFFFFFFFFFFF;
struct PICTURE
{
    struct PIXEL
    {
        unsigned char r, g, b, a;
    };
    PIXEL Data[300][600];
    unsigned int Width, Height;
};
PICTURE ReadJPEGFile(string FileName)
{
    PICTURE Picture;
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr JPEGError;
    cinfo.err = jpeg_std_error(&JPEGError);
    jpeg_create_decompress(&cinfo);

    FILE *InputFilePointer = fopen(FileName.c_str(), "rb");
    if (InputFilePointer == NULL)
    {
        cout << "can't open " << FileName << endl;
        exit(0);
    }
    jpeg_stdio_src(&cinfo, InputFilePointer);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    Picture.Width = cinfo.output_width;
    Picture.Height = cinfo.output_height;
    unsigned char *Buffer = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);
    unsigned int i = 0;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, &Buffer, 1);
        for (unsigned int j = 0; j < cinfo.output_width; j++)
        {
            Picture.Data[i][j].r = Buffer[j * 3];
            Picture.Data[i][j].g = Buffer[j * 3 + 1];
            Picture.Data[i][j].b = Buffer[j * 3 + 2];
        }
        i++;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(InputFilePointer);
    free(Buffer);
    return Picture;
}
PICTURE ReadPNGFile(string FileName)
{
    PICTURE Picture;
    unsigned char *Buffer = NULL;
    unsigned int Error = lodepng_decode32_file(&Buffer, &Picture.Width, &Picture.Height, FileName.c_str());
    if (Error)
    {
        printf("error %u: %s\n", Error, lodepng_error_text(Error));
    }
    for (unsigned int y = 0; y < Picture.Height; y++)
        for (unsigned int x = 0; x < Picture.Width; x++)
        {
            Picture.Data[y][x].r = Buffer[4 * y * Picture.Width + 4 * x + 0];
            Picture.Data[y][x].g = Buffer[4 * y * Picture.Width + 4 * x + 1];
            Picture.Data[y][x].b = Buffer[4 * y * Picture.Width + 4 * x + 2];
            Picture.Data[y][x].a = Buffer[4 * y * Picture.Width + 4 * x + 3];
        }
    delete Buffer;
    return Picture;
}
string GetCurrentTime()
{
    GetDataToFile("https://www.ximalaya.com/revision/time");
    return GetDataFromFileToString();
}
string GetNonce()
{
    GetDataToFile("https://passport.ximalaya.com/web/nonce/" + GetCurrentTime());
    json NonceJSON = json::parse(GetDataFromFileToString());
    if (NonceJSON["ret"] != 0)
    {
        cout << "获得随机数值失败 " << NonceJSON["msg"] << endl;
        exit(0);
    }
    return NonceJSON["nonce"].as_string();
}
string ToString36(int Input)
{
    string Output = "";
    while (Input)
    {
        if (Input % 36 < 10)
            Output += (Input % 36 + '0');
        else
            Output += (Input % 36 - 10 + 'A');
        Input /= 36;
    }
    reverse(Output.begin(), Output.end());
    return Output;
}
int main()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);
    string CaptchaSessionId = "xm_" + ToString36(time(NULL)) + "000000";
    GetDataToFile("https://mobile.ximalaya.com/captcha-web/check/slide/get?bpId=139&sessionId=" + CaptchaSessionId);
    json CaptchaJSON = json::parse(GetDataFromFileToString());
    if (!CaptchaJSON["msg"].is_null())
    {
        cout << "获得验证码失败 " << CaptchaJSON["msg"].as_string() << endl;
        exit(0);
    }
    GetDataToFile(CaptchaJSON["data"]["bgUrl"].as_string(), "Header.tmp", "Captcha-Background.jpg");
    GetDataToFile(CaptchaJSON["data"]["fgUrl"].as_string(), "Header.tmp", "Captcha-Foreground.png");
    PICTURE JPEGPicture = ReadJPEGFile(CurrentDir + "Captcha-Background.jpg");
    PICTURE PNGPicture = ReadPNGFile(CurrentDir + "Captcha-Foreground.png");
    unsigned int PNGPictureBottom = 0;
    for (unsigned int x = PNGPicture.Height - 1; x >= 0; x--)
    {
        for (unsigned int y = 0; y < PNGPicture.Width; y++)
            if (PNGPicture.Data[x][y].a != 0)
            {
                PNGPictureBottom = x;
                break;
            }
        if (PNGPictureBottom != 0)
            break;
    }
    PNGPictureBottom--;
    long long MinDelta = INF;
    unsigned int MinY;
    for (unsigned int y = 0; y < JPEGPicture.Width - 62; y++)
    {
        long long delta = 0;
        for (unsigned int i = 0; i < 62; i++)
        {
            delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].r - (int)JPEGPicture.Data[PNGPictureBottom + 1][y + i].r);
            delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].g - (int)JPEGPicture.Data[PNGPictureBottom + 1][y + i].g);
            delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].b - (int)JPEGPicture.Data[PNGPictureBottom + 1][y + i].b);
        }
        if (delta < MinDelta)
        {
            MinDelta = delta;
            MinY = y;
        }
    }
    json CaptchaSubmitJSON;
    CaptchaSubmitJSON["bpId"] = 139;
    CaptchaSubmitJSON["sessionId"] = CaptchaSessionId;
    CaptchaSubmitJSON["startTime"] = GetCurrentTime();
    CaptchaSubmitJSON["startX"] = 673;
    CaptchaSubmitJSON["startY"] = 148;
    CaptchaSubmitJSON["type"] = "slider";
    CaptchaSubmitJSON["captchaText"] = to_string(MinY + 30) + ",0";
    GetDataToFile("https://mobile.ximalaya.com/captcha-web/valid/slider", "Header.tmp", "Body.tmp", true, CaptchaSubmitJSON.dump());
    remove(string(CurrentDir + "Captcha-Background.jpg").c_str());
    remove(string(CurrentDir + "Captcha-Foreground.png").c_str());
    json CaptchaResultJSON = json::parse(GetDataFromFileToString());
    if (CaptchaResultJSON["msg"].as_string() != "captcha check success")
    {
        cout << "验证码校验失败 " << CaptchaResultJSON["msg"].as_string() << " ，重新运行可以重试" << endl;
        return 0;
    }
    cout << CaptchaResultJSON["token"] << endl;
    string PhoneNumber = "18018511393";
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Accept: */*");
    HeaderList = curl_slist_append(HeaderList, "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
    HeaderList = curl_slist_append(HeaderList, "Accept-Encoding: gzip, deflate, br");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://www.ximalaya.com/");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.ximalaya.com");
    HeaderList = curl_slist_append(HeaderList, "Connection: keep-alive");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Dest: empty");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Mode: cors");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Site: same-site");
    HeaderList = curl_slist_append(HeaderList, "Pragma: no-cache");
    HeaderList = curl_slist_append(HeaderList, "Cache-Control: no-cache");
    string Nonce = GetNonce();
    json AuthJSON;
    AuthJSON["mobile"] = PhoneNumber;
    AuthJSON["nonce"] = Nonce;
    AuthJSON["sendType"] = 1;
    AuthJSON["signature"] = SHA1("MOBILE=" + PhoneNumber + "&NONCE=" + Nonce + "&" + WEBSign);
    HeaderList = curl_slist_append(HeaderList, string("Content-Length: " + to_string(AuthJSON.dump().size())).c_str());
    cout << AuthJSON.dump() << endl;
    cout << string(CurrentDir + "Cookies.tmp") << endl;
    GetDataToFile("https://passport.ximalaya.com/web/sms/send", "Header.tmp", "Body.tmp", true, AuthJSON.dump(), HeaderList, NULL, "application/json", ".ximalaya.com\tTRUE\t/\tFALSE\t0\tfds_otp\t" + CaptchaResultJSON["token"].as_string());
    curl_slist_free_all(HeaderList);
    json AuthJSONResponse = json::parse(GetDataFromFileToString());
    if (AuthJSONResponse["ret"].as_integer() != 0)
    {
        cout << "验证码发送失败 " << AuthJSONResponse["msg"].as_string() << endl;
        return 0;
    }
    cout << "验证码发送成功" << endl;
    string Code;
    cout << "请输入验证码：";
    cin >> Code;
    Nonce = GetNonce();
    json LoginJSON;
    LoginJSON["code"] = Code;
    LoginJSON["mobile"] = PhoneNumber;
    LoginJSON["nonce"] = Nonce;
    LoginJSON["signature"] = SHA1("CODE=" + Code + "&MOBILE=" + PhoneNumber + "&NONCE=" + Nonce + "&" + WEBSign);
    GetDataToFile("https://passport.ximalaya.com/web/sms/verify", "Header.tmp", "Body.tmp", true, LoginJSON.dump(), HeaderList);
    json LoginJSONResponse = json::parse(GetDataFromFileToString());
    if (LoginJSONResponse["ret"].as_integer() != 0)
    {
        cout << "登录失败 " << LoginJSONResponse["msg"].as_string() << endl;
        return 0;
    }
    cout << "登录成功" << endl;
    Clean();
    return 0;
}
