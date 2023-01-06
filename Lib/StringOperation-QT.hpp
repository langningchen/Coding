#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTranslator>
#include <unistd.h>
#include <vector>
using namespace std;
QString CurrentDir;
void GetCurrentDir()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    memset(Buffer, 0, sizeof(char) * BufferSize);
    if (readlink("/proc/self/exe", Buffer, BufferSize) == 0)
        return;
    CurrentDir = Buffer;
    delete[] Buffer;
    CurrentDir.remove(CurrentDir.lastIndexOf("/") + 1, -1);
}
QString StringReplaceAll(QString Data, QString Before, QString After)
{
    int Index = 0;
    while ((Index = Data.indexOf(Before)) != -1)
        Data.replace(Index, Before.size(), After);
    return Data;
}
QString GetStringBetween(QString Data, QString Start, QString End)
{
    int StartPos = Data.indexOf(Start);
    if (StartPos == -1)
        return "";
    StartPos += Start.size();
    int EndPos = Data.indexOf(End, StartPos + 1);
    if (EndPos == -1)
        return "";
    return Data.mid(StartPos, EndPos - StartPos);
}
vector<QString> StringSpilt(QString Input, QString Seperator)
{
    Input += "\n";
    vector<QString> Output;
    size_t Last = 0;
    for (int i = 0; i < Input.size() - Seperator.size() + 1; i++)
        if (Input.mid(i, Seperator.size()) == Seperator)
        {
            Output.push_back(Input.mid(Last, i - Last));
            i += Seperator.size();
            Last = i;
            i--;
        }
    return Output;
}
bool IfFileExist(QString FileName)
{
    if (CurrentDir == "")
        GetCurrentDir();
    QFile File(CurrentDir + FileName);
    if(!File.isOpen())
        return false;
    File.close();
    return true;
}
QString GetDataFromFileToString(QString FileName = "Body.tmp")
{
    if (CurrentDir == "")
        GetCurrentDir();
    QString Data = "";
    QFile File(CurrentDir + FileName);
    if(!File.isOpen())
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), "Can not open input file: " + FileName);
        exit(0);
    }
    Data = File.readAll();
    File.close();
    return Data;
}
void SetDataFromStringToFile(QString FileName, QString Data)
{
    if (CurrentDir == "")
        GetCurrentDir();
    QFile File(CurrentDir + FileName);
    if(!File.isOpen())
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), "Can not open output file: " + FileName);
        exit(0);
    }
    File.seek(0);
    File.write(Data.toStdString().c_str());
    File.close();
}
QString FixString(QString Data)
{
    return (Data[Data.size() - 1] == '\n' || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == ' ' ? FixString(Data.remove(Data.size() - 1, 1)) : Data);
}
