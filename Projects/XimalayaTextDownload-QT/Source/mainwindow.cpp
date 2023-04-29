#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "Curl-QT.hpp"
#include "lodepng.cpp"
#include "jpeg/jpeglib.h"
#include "SHA1-QT.hpp"
#include "MD5-QT.hpp"
#include <locale>
const QString WEBSign = "WEB-V1-PRODUCT-E7768904917C4154A925FBE1A3848BC3E84E2C7770744E56AFBC9600C267891F";
const QString LinuxFilePath = "/mnt/d/12_Mom/";
const QString WindowsFilePath = "D:\\12_Mom\\";
struct PICTURE
{
    struct PIXEL
    {
        unsigned char r, g, b, a;
    };
    PIXEL Data[300][600];
    unsigned int Width, Height;
};
PICTURE ReadJPEGFile(QString FileName)
{
    PICTURE Picture;
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr JPEGError;
    cinfo.err = jpeg_std_error(&JPEGError);
    jpeg_create_decompress(&cinfo);

    FILE *InputFilePointer = fopen(FileName.toStdString().c_str(), "rb");
    if (InputFilePointer == NULL)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("无法打开文件") + FileName);
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
PICTURE ReadPNGFile(QString FileName)
{
    PICTURE Picture;
    unsigned char *Buffer = NULL;
    unsigned int Error = lodepng_decode32_file(&Buffer, &Picture.Width, &Picture.Height, FileName.toStdString().c_str());
    if (Error)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QString::number(Error) + QTranslator::tr("无法打开文件") + lodepng_error_text(Error));
        exit(0);
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
QString GetCurrentTime()
{
    if (GetDataToFile("https://www.ximalaya.com/revision/time"))
        return "";
    return GetDataFromFileToString();
}
QString GetNonce()
{
    if (GetDataToFile("https://passport.ximalaya.com/web/nonce/" + GetCurrentTime()))
        return "";
    json NonceJSON = json::parse(GetDataFromFileToString().toStdString());
    if (NonceJSON["ret"] != 0)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("获得随机数值失败 ") + QString::fromStdString(NonceJSON["msg"].as_string()));
        exit(0);
    }
    return QString::fromStdString(NonceJSON["nonce"].as_string());
}
QString ToString36(int Input)
{
    QString Output = "";
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
QString UpperCase(QString Input)
{
    for (int i = 0; i < Input.length(); i++)
        if (Input[i] >= 'a' && Input[i] <= 'z')
            Input[i].unicode() -= 32;
    return Input;
}
curl_slist *GetBasicHeaderList(QString Host = "www", QString Referer = "https://www.ximalaya.com/", bool AddXM_SIGN = false)
{
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, QString("Host: " + Host + ".ximalaya.com").toStdString().c_str());
    HeaderList = curl_slist_append(HeaderList, "Accept: */*");
    HeaderList = curl_slist_append(HeaderList, "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
    HeaderList = curl_slist_append(HeaderList, "Accept-Encoding: deflate, br");
    HeaderList = curl_slist_append(HeaderList, QString("Referer: " + Referer).toStdString().c_str());
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.ximalaya.com");
    HeaderList = curl_slist_append(HeaderList, "Connection: keep-alive");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Dest: empty");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Mode: cors");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Site: same-site");
    HeaderList = curl_slist_append(HeaderList, "Pragma: no-cache");
    HeaderList = curl_slist_append(HeaderList, "Cache-Control: no-cache");
    if (AddXM_SIGN)
    {
        QString CurrentTime = GetCurrentTime();
        MD5 MD5Encoder;
        HeaderList = curl_slist_append(HeaderList, QString("xm-sign: {" +
                                                           MD5Encoder.encode("himalaya-" + CurrentTime) +
                                                           "}(" +
                                                           QString::number(rand() % 100) +
                                                           ")" +
                                                           CurrentTime +
                                                           "(" +
                                                           QString::number(rand() % 100) +
                                                           ")" +
                                                           QString::number(time(NULL)))
                                                       .toStdString()
                                                       .c_str());
    }
    return HeaderList;
}
QString EncodeWString(wstring Input)
{
    QString Output;
    for (size_t i = 0; i < Input.size(); i++)
        if (Input[i] <= 0x7f)
            Output.push_back((char)Input[i]);
        else
            Output += "\\u" + QString::number((int)Input[i]) + "?";
    return Output;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->progressBar->setValue(1);
    if (GetDataToFile("https://www.ximalaya.com/revision/my/getCurrentUserInfo", "Header.tmp", "Body.tmp", false, "", GetBasicHeaderList("www", "https://www.ximalaya.com/my/subscribed", true)))
    {
        ui->pushButton->setEnabled(true);
        return;
    }
    if (json::parse(GetDataFromFileToString().toStdString())["ret"].as_integer() != 200)
    {
        bool CaptchaSuccess = false;
        unsigned short CaptchaCounter = 0;
        json CaptchaResultJSON;
        while (!CaptchaSuccess)
        {
            ui->progressBar->setValue(5);
            if (CaptchaCounter == 5)
            {
                QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("多次失败，请重新运行程序重试"));
                
                ui->pushButton->setEnabled(true);
                return;
            }
            ui->progressBar->setValue(10);
            QString CaptchaSessionId = "xm_" + ToString36(time(NULL)) + "000000";
            if (GetDataToFile("https://mobile.ximalaya.com/captcha-web/check/slide/get?bpId=139&sessionId=" + CaptchaSessionId))
            {
                ui->pushButton->setEnabled(true);
                return;
            }
            json CaptchaJSON = json::parse(GetDataFromFileToString().toStdString());
            if (!CaptchaJSON["msg"].is_null())
            {
                QMessageBox::critical(NULL, QTranslator::tr("错误"), QString(QTranslator::tr("获得验证码失败 ") + QString::fromStdString(CaptchaJSON["msg"].as_string())));
                exit(0);
            }
            ui->progressBar->setValue(15);
            if (GetDataToFile(QString::fromStdString(CaptchaJSON["data"]["bgUrl"].as_string()), "Header.tmp", "Captcha-Background.jpg"))
            {
                ui->pushButton->setEnabled(true);
                return;
            }
            if (GetDataToFile(QString::fromStdString(CaptchaJSON["data"]["fgUrl"].as_string()), "Header.tmp", "Captcha-Foreground.png"))
            {
                ui->pushButton->setEnabled(true);
                return;
            }
            PICTURE JPEGPicture = ReadJPEGFile(CurrentDir + "Captcha-Background.jpg");
            PICTURE PNGPicture = ReadPNGFile(CurrentDir + "Captcha-Foreground.png");
            unsigned int PNGPictureBottom = 0;
            for (unsigned int x = PNGPicture.Height; x > 0; x--)
            {
                for (unsigned int y = 0; y < PNGPicture.Width; y++)
                    if (PNGPicture.Data[x - 1][y].a != 0)
                    {
                        PNGPictureBottom = x - 1;
                        break;
                    }
                if (PNGPictureBottom != 0)
                    break;
            }
            set<pair<long long, unsigned int>, greater<pair<long long, unsigned int>>> Deltas;
            for (unsigned int y = 0; y < JPEGPicture.Width - 62; y++)
            {
                long long Delta = 0;
                for (unsigned int i = 0; i < 62; i++)
                {
                    Delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].r - (int)JPEGPicture.Data[PNGPictureBottom][y + i].r);
                    Delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].g - (int)JPEGPicture.Data[PNGPictureBottom][y + i].g);
                    Delta += abs((int)PNGPicture.Data[PNGPictureBottom][14 + i].b - (int)JPEGPicture.Data[PNGPictureBottom][y + i].b);
                }
                Deltas.insert(make_pair(Delta, y));
            }
            set<pair<long long, unsigned int>>::iterator sit = Deltas.begin();
            unsigned int SlideLength = 0xFFFFFFFF;
            while (SlideLength == 0xFFFFFFFF)
            {
                bool CanBe = true;
                for (unsigned int i = 5; i < 57; i++)
                    if ((JPEGPicture.Data[PNGPictureBottom - 1][sit->second + i].r +
                         JPEGPicture.Data[PNGPictureBottom - 1][sit->second + i].g +
                         JPEGPicture.Data[PNGPictureBottom - 1][sit->second + i].b) < 600)
                    {
                        CanBe = false;
                        break;
                    }
                if (CanBe)
                    SlideLength = sit->second;
                sit++;
                if (sit == Deltas.end())
                    SlideLength = (*Deltas.begin()).second;
            }
            ui->progressBar->setValue(20);
            json CaptchaSubmitJSON;
            CaptchaSubmitJSON["bpId"] = 139;
            CaptchaSubmitJSON["sessionId"] = CaptchaSessionId.toStdString();
            CaptchaSubmitJSON["startTime"] = GetCurrentTime().toStdString();
            CaptchaSubmitJSON["startX"] = 673;
            CaptchaSubmitJSON["startY"] = 148;
            CaptchaSubmitJSON["type"] = "slider";
            CaptchaSubmitJSON["captchaText"] = to_string(SlideLength + 30) + ",0";
            if (GetDataToFile("https://mobile.ximalaya.com/captcha-web/valid/slider", "Header.tmp", "Body.tmp", true, QString::fromStdString(CaptchaSubmitJSON.dump())))
            {
                ui->pushButton->setEnabled(true);
                return;
            }
            CaptchaResultJSON = json::parse(GetDataFromFileToString().toStdString());
            if (CaptchaResultJSON["msg"].as_string() != "captcha check success")
            {
                QMessageBox::critical(NULL, QTranslator::tr("错误"), QString(QTranslator::tr("验证码校验失败 ") + QString::fromStdString(CaptchaResultJSON["msg"].as_string()) + QTranslator::tr("匹配到的滑块位置为 ") + QString::number(SlideLength) + QTranslator::tr("正在重试")));
                CaptchaCounter++;
            }
            else
                CaptchaSuccess = true;
            remove(QString(CurrentDir + "Captcha-Background.jpg").toStdString().c_str());
            remove(QString(CurrentDir + "Captcha-Foreground.png").toStdString().c_str());
        }
        ui->progressBar->setValue(25);
        QString PhoneNumber = GetDataFromFileToString("Keys/PhoneNumber2");
        QString Nonce = GetNonce();
        json AuthJSON;
        AuthJSON["mobile"] = PhoneNumber.toStdString();
        AuthJSON["nonce"] = Nonce.toStdString();
        AuthJSON["sendType"] = 1;
        AuthJSON["signature"] = SHA1(UpperCase("mobile=" + PhoneNumber + "&nonce=" + Nonce + "&sendType=1&" + WEBSign)).toStdString();
        if (GetDataToFile("https://passport.ximalaya.com/web/sms/send", "Header.tmp", "Body.tmp", true, QString::fromStdString(AuthJSON.dump()), GetBasicHeaderList("passport"), NULL, "application/json", ".ximalaya.com\tTRUE\t/\tFALSE\t0\tfds_otp\t" + QString::fromStdString(CaptchaResultJSON["token"].as_string())))
        {
            ui->pushButton->setEnabled(true);
            return;
        }
        json AuthJSONResponse = json::parse(GetDataFromFileToString().toStdString());
        if (AuthJSONResponse["ret"].as_integer() != 0)
        {
            QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("验证码发送失败 ") + QString::fromStdString(AuthJSONResponse["msg"].as_string()));
            
            ui->pushButton->setEnabled(true);
            return;
        }
        ui->progressBar->setValue(30);
        bool CheckCodeSuccess = false;
        json CheckCodeJSONResponse;
        while (!CheckCodeSuccess)
        {
            QString Code;
            Code = QInputDialog::getInt(NULL, "Input", QTranslator::tr("请输入验证码"));
            Nonce = GetNonce();
            json CheckCodeJSON;
            CheckCodeJSON["code"] = Code.toStdString();
            CheckCodeJSON["mobile"] = PhoneNumber.toStdString();
            CheckCodeJSON["nonce"] = Nonce.toStdString();
            CheckCodeJSON["signature"] = SHA1(UpperCase(QString("code=" + Code + "&mobile=" + PhoneNumber + "&nonce=" + Nonce + "&" + WEBSign))).toStdString();
            if (GetDataToFile("https://passport.ximalaya.com/web/sms/verify", "Header.tmp", "Body.tmp", true, QString::fromStdString(CheckCodeJSON.dump()), GetBasicHeaderList("passport")))
            {
                ui->pushButton->setEnabled(true);
                return;
            }
            CheckCodeJSONResponse = json::parse(GetDataFromFileToString().toStdString());
            if (CheckCodeJSONResponse["ret"].as_integer() != 0)
                QMessageBox::critical(NULL, QTranslator::tr("错误"), (QTranslator::tr("验证码校验失败 ") + QString::fromStdString(CheckCodeJSONResponse["msg"].as_string())));
            else
                CheckCodeSuccess = true;
        }
        ui->progressBar->setValue(35);
        json LoginJSON;
        Nonce = GetNonce();
        LoginJSON["mobile"] = PhoneNumber.toStdString();
        LoginJSON["nonce"] = Nonce.toStdString();
        LoginJSON["smsKey"] = CheckCodeJSONResponse["bizKey"].as_string();
        LoginJSON["signature"] = SHA1(UpperCase(
                                          "mobile=" + PhoneNumber +
                                          "&nonce=" + Nonce +
                                          "&smsKey=" + QString::fromStdString(CheckCodeJSONResponse["bizKey"].as_string()) +
                                          "&" + WEBSign))
                                     .toStdString();
        if (GetDataToFile("https://passport.ximalaya.com/web/login/quick/v1", "Header.tmp", "Body.tmp", true, QString::fromStdString(LoginJSON.dump()), GetBasicHeaderList("passport")))
        {
            ui->pushButton->setEnabled(true);
            return;
        }
        json LoginJSONResponse = json::parse(GetDataFromFileToString().toStdString());
        if (LoginJSONResponse["ret"].as_integer() != 0)
        {
            QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("登录失败 ") + QString::fromStdString(LoginJSONResponse["msg"].as_string()));
            
            ui->pushButton->setEnabled(true);
            return;
        }
    }
    ui->progressBar->setValue(40);
    QString AlbumID = "43254755";
    if (GetDataToFile("https://www.ximalaya.com/revision/album/v1/getTracksList?albumId=" + AlbumID + "&pageNum=1", "Header.tmp", "Body.tmp", false, "", GetBasicHeaderList("www", "https://www.ximalaya.com/album/" + AlbumID, true)))
    {
        ui->pushButton->setEnabled(true);
        return;
    }
    json AlbumJSONResponse = json::parse(GetDataFromFileToString().toStdString());
    if (AlbumJSONResponse["ret"].as_integer() != 200)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("获取合集信息失败 ") + QString::fromStdString(AlbumJSONResponse["msg"].as_string()));
        
        ui->pushButton->setEnabled(true);
        return;
    }
    ui->progressBar->setValue(45);
    int TrackIndex;
    TrackIndex = ui->spinBox->value();
    if (TrackIndex < 1 || TrackIndex > AlbumJSONResponse["data"]["trackTotalCount"])
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("请输入大于1小于") + QString::fromStdString(AlbumJSONResponse["data"]["trackTotalCount"].as_string()) + QTranslator::tr("的数字"));
        
        ui->pushButton->setEnabled(true);
        return;
    }
    GetDataToFile("https://www.ximalaya.com/revision/album/v1/getTracksList?albumId=" + AlbumID + "&pageNum=" + QString::number(TrackIndex / AlbumJSONResponse["data"]["pageSize"].as_integer() + 1),
                  "Header.tmp", "Body.tmp", false, "",
                  GetBasicHeaderList("www", "https://www.ximalaya.com/album/" + AlbumID, true));
    AlbumJSONResponse = json::parse(GetDataFromFileToString().toStdString());
    if (AlbumJSONResponse["ret"].as_integer() != 200)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("获取合集信息失败 ") + QString::fromStdString(AlbumJSONResponse["msg"].as_string()));
        
        ui->pushButton->setEnabled(true);
        return;
    }
    ui->progressBar->setValue(50);
    QString TrackID = QString::fromStdString(AlbumJSONResponse["data"]["tracks"][TrackIndex % AlbumJSONResponse["data"]["pageSize"].as_integer() - 1]["trackId"].as_string());
    GetDataToFile("https://www.ximalaya.com/revision/track/simple?trackId=" + TrackID,
                  "Header.tmp", "Body.tmp", false, "",
                  GetBasicHeaderList("www", "https://www.ximalaya.com/sound/" + TrackID, true));
    json TrackJSONResponse = json::parse(GetDataFromFileToString().toStdString());
    if (TrackJSONResponse["ret"].as_integer() != 200)
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("获取音频信息失败 ") + QString::fromStdString(TrackJSONResponse["msg"].as_string()));
        
        ui->pushButton->setEnabled(true);
        return;
    }
    ui->progressBar->setValue(55);
    QString Content = QString::fromStdString(TrackJSONResponse["data"]["trackInfo"]["richIntro"].as_string());
    Content = StringReplaceAll(Content, "\r", "");
    Content = StringReplaceAll(Content, "</p>", "\n");
    Content = StringReplaceAll(Content, "<br>", "\n");
    Content = EraseHTMLElement(Content);
    Content = StringReplaceAll(Content, "\n\n", "\n");
    while (Content[0] == '\n' && Content.size() > 0)
        Content.remove(0, 1);
    while (Content[Content.size() - 1] == '\n' && Content.size() > 0)
        Content.remove(Content.size() - 1, 1);
    ui->progressBar->setValue(60);
    size_t LastPos = 0;
    QString RTFTitle = QString::fromStdString(TrackJSONResponse["data"]["trackInfo"]["title"].as_string());
    RTFTitle = StringReplaceAll(RTFTitle, "<", "");
    RTFTitle = StringReplaceAll(RTFTitle, ">", "");
    RTFTitle = StringReplaceAll(RTFTitle, "|", "");
    RTFTitle = StringReplaceAll(RTFTitle, "\"", "");
    RTFTitle = StringReplaceAll(RTFTitle, "/", "");
    RTFTitle = StringReplaceAll(RTFTitle, "\\", "");
    RTFTitle = StringReplaceAll(RTFTitle, ":", "");
    RTFTitle = StringReplaceAll(RTFTitle, "*", "");
    RTFTitle = StringReplaceAll(RTFTitle, "?", "");
    ui->progressBar->setValue(70);
    ofstream OutputFileStream(QString(LinuxFilePath + RTFTitle + ".rtf").toStdString());
    if (!OutputFileStream.is_open())
    {
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("打开输出文件失败"));
        
        ui->pushButton->setEnabled(true);
        return;
    }
    OutputFileStream << "{\\rtf1\\paperw12240\\paperh15840\\margl720\\margr720\\margt360\\margb360" << endl
                     << EncodeWString(QString::fromStdString(TrackJSONResponse["data"]["trackInfo"]["title"].as_string()).toStdWString()).toStdString() << endl;
    ui->progressBar->setValue(80);
    for (int Pos = 0; Pos < Content.size(); Pos++)
        if (Content[Pos] == '\n')
        {
            OutputFileStream << "\\par" << EncodeWString(Content.mid(LastPos, Pos - LastPos).toStdWString()).toStdString() << endl;
            LastPos = Pos + 1;
        }
    OutputFileStream << "\\par}" << endl;
    OutputFileStream.close();
    ui->progressBar->setValue(90);
    if (system(QString("fish -c \"/mnt/c/Program\\ Files/Microsoft\\ Office/root/Office16/WINWORD.EXE \\\"" + WindowsFilePath + RTFTitle + ".rtf\\\"\" > /dev/null 2>&1 &").toStdString().c_str()))
        QMessageBox::critical(NULL, QTranslator::tr("错误"), QTranslator::tr("执行失败"));
    ui->progressBar->setValue(100);
    
    ui->pushButton->setEnabled(true);
}
