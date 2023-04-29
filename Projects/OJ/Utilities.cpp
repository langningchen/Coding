#include <sys/stat.h>
#include <sys/dir.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "Settings.hpp"
#include "Utilities.hpp"

void UTILITIES::Init() { Logger.SetLogFileName(Settings.GetBaseFolder() + "/Utilities.log"); }
std::string UTILITIES::StringReplaceAll(std::string Data, std::string Search, std::string Replace)
{
    size_t Pos = Data.find(Search);
    while (Pos != std::string::npos)
    {
        Data.replace(Pos, Search.size(), Replace);
        Pos = Data.find(Search, Pos + Replace.size());
    }
    return Data;
}
// bool UTILITIES::MakeDir(std::string Dir)
// {
//     if (access(Dir.c_str(), F_OK) != -1)
//     {
//         if (!RemoveDir(Dir))
//         {
//             Logger.Error("Can not remove working directory " + Dir);
//             return false;
//         }
//     }
//     if (mkdir(Dir.c_str(), 0755) == -1)
//     {
//         Logger.Error("Can not recreate working directory " + Dir);
//         return false;
//     }
//     return true;
// }
bool UTILITIES::MakeDir(std::string Dir)
{
    if (access(Dir.c_str(), F_OK) == -1 && mkdir(Dir.c_str(), 0755) == -1)
    {
        Logger.Error("Can not create working directory " + Dir);
        return false;
    }
    return true;
}
bool UTILITIES::RemoveDir(std::string Dir)
{
    DIR *DirPtr = opendir(Dir.c_str());
    if (DirPtr == nullptr)
    {
        Logger.Error("Can not open directory " + Dir);
        return false;
    }
    struct dirent *Entry = readdir(DirPtr);
    while (Entry != nullptr)
    {
        if (Entry->d_type == DT_DIR)
        {
            if (strcmp(Entry->d_name, ".") != 0 && strcmp(Entry->d_name, "..") != 0)
                RemoveDir(Dir + "/" + Entry->d_name);
        }
        else
        {
            if (remove((Dir + "/" + Entry->d_name).c_str()) != 0)
                Logger.Error("Can not remove file " + Dir + "/" + Entry->d_name);
            else
                Logger.Debug("Removed file \"" + Dir + "/" + Entry->d_name + "\"");
        }
        Entry = readdir(DirPtr);
    }
    closedir(DirPtr);
    if (rmdir(Dir.c_str()) != 0)
    {
        Logger.Error("Can not remove directory \"" + Dir + "\" after removing all files");
        return false;
    }
    Logger.Debug("Removed directory \"" + Dir + "\"");
    return true;
}
bool UTILITIES::CopyFile(std::string Source, std::string Destination)
{
    FILE *SourceFile = fopen(Source.c_str(), "rb");
    if (SourceFile == nullptr)
    {
        Logger.Error("Can not open source file " + Source);
        return false;
    }
    FILE *DestinationFile = fopen(Destination.c_str(), "wb");
    if (DestinationFile == nullptr)
    {
        Logger.Error("Can not open destination file " + Destination);
        fclose(SourceFile);
        return false;
    }
    char Buffer[1024];
    size_t ReadSize = fread(Buffer, 1, 1024, SourceFile);
    while (ReadSize > 0)
    {
        if (fwrite(Buffer, 1, ReadSize, DestinationFile) != ReadSize)
        {
            Logger.Error("Can not write to destination file " + Destination);
            fclose(SourceFile);
            fclose(DestinationFile);
            return false;
        }
        ReadSize = fread(Buffer, 1, 1024, SourceFile);
    }
    fclose(SourceFile);
    fclose(DestinationFile);

    struct stat FileStatus;
    if (lstat(Source.c_str(), &FileStatus) == -1)
    {
        Logger.Error("Can not get source file \"" + Source + "\" attributions");
        return false;
    }
    if (chmod(Destination.c_str(), FileStatus.st_mode) == -1)
    {
        Logger.Error("Can not set destination file \"" + Destination + "\" attributions");
        return false;
    }

    Logger.Debug("Copied file \"" + Source + "\" to \"" + Destination + "\"");
    return true;
}
bool UTILITIES::CopyDir(std::string Source, std::string Destination)
{
    DIR *DirPtr = opendir(Source.c_str());
    if (DirPtr == nullptr)
    {
        Logger.Error("Can not open directory " + Source);
        return false;
    }
    struct dirent *Entry = readdir(DirPtr);
    while (Entry != nullptr)
    {
        if (Entry->d_type == DT_DIR)
        {
            if (strcmp(Entry->d_name, ".") != 0 && strcmp(Entry->d_name, "..") != 0)
            {
                struct stat FileStatus;
                if (lstat((Source + "/" + Entry->d_name).c_str(), &FileStatus) == -1)
                {
                    Logger.Error("Can not get directory " + Source + "/" + Entry->d_name + " attributions");
                    closedir(DirPtr);
                    return false;
                }
                if (mkdir((Destination + "/" + Entry->d_name).c_str(), FileStatus.st_mode) == -1)
                {
                    Logger.Error("Can not create directory " + Destination + "/" + Entry->d_name);
                    closedir(DirPtr);
                    return false;
                }
                if (!CopyDir(Source + "/" + Entry->d_name, Destination + "/" + Entry->d_name))
                {
                    closedir(DirPtr);
                    return false;
                }
            }
        }
        else if (!CopyFile(Source + "/" + Entry->d_name, Destination + "/" + Entry->d_name))
        {
            closedir(DirPtr);
            return false;
        }
        Entry = readdir(DirPtr);
    }
    closedir(DirPtr);

    Logger.Debug("Copied directory \"" + Source + "\" to \"" + Destination + "\"");
    return true;
}
bool UTILITIES::LoadFile(std::string FileName, std::string &Output)
{
    FILE *File = fopen(FileName.c_str(), "rb");
    if (File == nullptr)
    {
        Logger.Error("Can not open file " + FileName);
        return false;
    }
    fseek(File, 0, SEEK_END);
    size_t Size = ftell(File);
    rewind(File);
    char *Buffer = new char[Size + 1];
    if (fread(Buffer, 1, Size, File) != Size)
    {
        Logger.Error("Can not read file " + FileName);
        fclose(File);
        delete[] Buffer;
        return false;
    }
    Buffer[Size] = '\0';
    Output = Buffer;
    delete[] Buffer;
    fclose(File);
    return true;
}
bool UTILITIES::LoadFile(std::string FileName, int &Output)
{
    std::string Temp;
    if (!LoadFile(FileName, Temp))
        return false;
    Output = atoi(Temp.c_str());
    return true;
}
bool UTILITIES::SaveFile(std::string FileName, std::string Data)
{
    FILE *File = fopen(FileName.c_str(), "wb");
    if (File == nullptr)
    {
        Logger.Error("Can not open file " + FileName);
        return false;
    }
    if (fwrite(Data.c_str(), 1, Data.size(), File) != Data.size())
    {
        Logger.Error("Can not write to file " + FileName);
        fclose(File);
        return false;
    }
    fclose(File);
    return true;
}
bool UTILITIES::SaveFile(std::string FileName, int Data)
{
    return SaveFile(FileName, std::to_string(Data));
}
std::string UTILITIES::RemoveSpaces(std::string Input)
{
    while (Input.size() > 0 && (Input[0] == 0 ||
                                Input[0] == '\n' ||
                                Input[0] == '\r' ||
                                Input[0] == '\t' ||
                                Input[0] == ' '))
        Input.erase(0, 1);
    while (Input.size() > 0 && (Input[Input.size() - 1] == 0 ||
                                Input[Input.size() - 1] == '\n' ||
                                Input[Input.size() - 1] == '\r' ||
                                Input[Input.size() - 1] == '\t' ||
                                Input[Input.size() - 1] == ' '))
        Input.erase(Input.size() - 1, 1);
    return Input;
}
size_t UTILITIES::UploadFunction(char *ptr, size_t size, size_t nmemb, void *userp)
{
    std::string *Upload = (std::string *)userp;
    const char *data = Upload->c_str();
    size_t room = size * nmemb;
    if (room < 1 || data == nullptr)
        return 0;
    size_t len = std::min(room, strlen(data));
    memcpy(ptr, data, len);
    Upload->erase(0, len);
    return len;
}
bool UTILITIES::SendEmail(std::string To, std::string Subject, std::string Body)
{
    std::string From = Settings.GetEmail();
    std::string Password = Settings.GetEmailPassword();
    CURL *Curl = curl_easy_init();
    if (Curl == nullptr)
    {
        Logger.Error("Can not initialize CURL");
        return false;
    }
    struct curl_slist *Recipients = nullptr;
    Recipients = curl_slist_append(Recipients, To.c_str());
    curl_easy_setopt(Curl, CURLOPT_URL, "smtp://smtp-mail.outlook.com:587");
    curl_easy_setopt(Curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(Curl, CURLOPT_USERNAME, From.c_str());
    curl_easy_setopt(Curl, CURLOPT_PASSWORD, Password.c_str());
    curl_easy_setopt(Curl, CURLOPT_MAIL_FROM, From.c_str());
    curl_easy_setopt(Curl, CURLOPT_MAIL_RCPT, Recipients);
    curl_easy_setopt(Curl, CURLOPT_UPLOAD, true);
    std::string Message = "From: " + From + "\r\nTo: " + To + "\r\nSubject: " + Subject + "\r\n\r\n" + Body + "\r\n";
    curl_easy_setopt(Curl, CURLOPT_READDATA, &Message);
    curl_easy_setopt(Curl, CURLOPT_READFUNCTION, UploadFunction);
    CURLcode Result = curl_easy_perform(Curl);
    if (Result != CURLE_OK)
    {
        Logger.Error("Can not send email: " + std::string(curl_easy_strerror(Result)));
        curl_slist_free_all(Recipients);
        curl_easy_cleanup(Curl);
        return false;
    }
    curl_slist_free_all(Recipients);
    curl_easy_cleanup(Curl);
    Logger.Debug("Sent email to " + To);
    return true;
}

UTILITIES Utilities;
