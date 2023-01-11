#include <string.h>
#include <iostream>

class String
{
private:
    char *Data;
    size_t Len;

public:
    const size_t npos = -1;

    String();
    String(char *NewData);
    String(const char *NewData);
    String(String *NewData);
    String(String &NewData);

    String *substr(size_t Start, size_t Length);
    String *substring(size_t Start, size_t End);
    void erase(size_t Start, size_t Length);
    size_t size();
    size_t length();

    size_t find(char *Key);
    size_t find(const char *Key);
    size_t find(String *Key);
    size_t find(String &Key);

    void insert(size_t Pos, char *Key);
    void insert(size_t Pos, const char *Key);
    void insert(size_t Pos, String *Key);
    void insert(size_t Pos, String &Key);

    void replace(size_t Start, size_t Length, char *Key);
    void replace(size_t Start, size_t Length, const char *Key);
    void replace(size_t Start, size_t Length, String *Key);
    void replace(size_t Start, size_t Length, String &Key);

    String *operator+(char *Other) const;
    String *operator+(const char *Other) const;
    String *operator+(String *Other) const;
    String *operator+(String &Other) const;

    void operator=(char *NewData);
    void operator=(const char *NewData);
    void operator=(String *Other);
    void operator=(String &Other);

    void operator+=(char *Other);
    void operator+=(const char *Other);
    void operator+=(String *Other);
    void operator+=(String &Other);

    bool operator<(char *Other) const;
    bool operator<(const char *Other) const;
    bool operator<(String *Other) const;
    bool operator<(String &Other) const;

    bool operator<=(char *Other) const;
    bool operator<=(const char *Other) const;
    bool operator<=(String *Other) const;
    bool operator<=(String &Other) const;

    bool operator==(char *Other) const;
    bool operator==(const char *Other) const;
    bool operator==(String *Other) const;
    bool operator==(String &Other) const;

    bool operator>=(char *Other) const;
    bool operator>=(const char *Other) const;
    bool operator>=(String *Other) const;
    bool operator>=(String &Other) const;

    bool operator>(char *Other) const;
    bool operator>(const char *Other) const;
    bool operator>(String *Other) const;
    bool operator>(String &Other) const;

    bool operator!=(char *Other) const;
    bool operator!=(const char *Other) const;
    bool operator!=(String *Other) const;
    bool operator!=(String &Other) const;

    ~String();

    friend std::ostream &operator<<(std::ostream &OutputFileStream, String *Value);
    friend std::ostream &operator<<(std::ostream &OutputFileStream, String &Value);
};

String::String()
{
    Data = NULL;
    Len = 0;
}
String::String(char *NewData)
{
    Len = strlen(NewData);
    Data = new char[Len];
    strcpy(Data, NewData);
}
String::String(const char *NewData)
{
    Len = strlen(NewData);
    Data = new char[Len];
    strcpy(Data, NewData);
}
String::String(String *NewData)
{
    Len = NewData->Len;
    Data = new char[Len];
    strcpy(Data, NewData->Data);
}
String::String(String &NewData)
{
    Len = NewData.Len;
    Data = new char[Len];
    strcpy(Data, NewData.Data);
}

String *String::substr(size_t Start, size_t Length)
{
    if (Length == npos)
        Length = Len - Start;
    String *Output = new String;
    Output->Len = Length;
    Output->Data = new char[Length];
    for (size_t i = 0; i <= Length; i++)
        Output->Data[i] = Data[Start + i];
    return Output;
}
String *String::substring(size_t Start, size_t End)
{
    return substr(Start, End - Start);
}
size_t String::size()
{
    return Len;
}
size_t String::length()
{
    return Len;
}
void String::erase(size_t Start, size_t Length)
{
    char *tmp = Data;
    Len -= Length;
    Data = new char[Len];
    for (size_t i = 0; i < Start; i++)
        Data[i] = tmp[i];
    for (size_t i = Start; i < Len; i++)
        Data[i] = tmp[i + Length];
    delete tmp;
}

size_t String::find(char *Key)
{
    for (size_t i = 0; i < Len - strlen(Key) + 1; i++)
        if (*substr(i, strlen(Key)) == Key)
            return i;
    return npos;
}
size_t String::find(const char *Key)
{
    for (size_t i = 0; i < Len - strlen(Key) + 1; i++)
        if (*substr(i, strlen(Key)) == Key)
            return i;
    return npos;
}
size_t String::find(String *Key)
{
    for (size_t i = 0; i < Len - Key->Len + 1; i++)
        if (*substr(i, Key->Len) == *Key)
            return i;
    return npos;
}
size_t String::find(String &Key)
{
    for (size_t i = 0; i < Len - Key.Len + 1; i++)
        if (*substr(i, Key.Len) == Key)
            return i;
    return npos;
}

void String::insert(size_t Pos, char *Key)
{
    char *tmp = Data;
    Len += strlen(Key);
    Data = new char[Len];
    for (size_t i = 0; i < Pos; i++)
        Data[i] = tmp[i];
    for (size_t i = 0; i < strlen(Key); i++)
        Data[Pos + i] = Key[i];
    for (size_t i = 0; i < Len - Pos - strlen(Key); i++)
        Data[Pos + strlen(Key) + i] = tmp[Pos + i];
    delete tmp;
}
void String::insert(size_t Pos, const char *Key)
{
    char *tmp = Data;
    Len += strlen(Key);
    Data = new char[Len];
    for (size_t i = 0; i < Pos; i++)
        Data[i] = tmp[i];
    for (size_t i = 0; i < strlen(Key); i++)
        Data[Pos + i] = Key[i];
    for (size_t i = 0; i < Len - Pos - strlen(Key); i++)
        Data[Pos + strlen(Key) + i] = tmp[Pos + i];
    delete tmp;
}
void String::insert(size_t Pos, String *Key)
{
    char *tmp = Data;
    Len += Key->Len;
    Data = new char[Len];
    for (size_t i = 0; i < Pos; i++)
        Data[i] = tmp[i];
    for (size_t i = 0; i < Key->Len; i++)
        Data[Pos + i] = Key->Data[i];
    for (size_t i = 0; i < Len - Pos - Key->Len; i++)
        Data[Pos + Key->Len + i] = tmp[Pos + i];
    delete tmp;
}
void String::insert(size_t Pos, String &Key)
{
    char *tmp = Data;
    Len += Key.Len;
    Data = new char[Len];
    for (size_t i = 0; i < Pos; i++)
        Data[i] = tmp[i];
    for (size_t i = 0; i < Key.Len; i++)
        Data[Pos + i] = Key.Data[i];
    for (size_t i = 0; i < Len - Pos - Key.Len; i++)
        Data[Pos + Key.Len + i] = tmp[Pos + i];
    delete tmp;
}

void String::replace(size_t Start, size_t Length, char *Key)
{
    erase(Start, Length);
    insert(Start, Key);
}
void String::replace(size_t Start, size_t Length, const char *Key)
{
    erase(Start, Length);
    insert(Start, Key);
}
void String::replace(size_t Start, size_t Length, String *Key)
{
    erase(Start, Length);
    insert(Start, Key);
}
void String::replace(size_t Start, size_t Length, String &Key)
{
    erase(Start, Length);
    insert(Start, Key);
}

String *String::operator+(char *Other) const
{
    String *Output = new String;
    Output->Len = Len + strlen(Other);
    Output->Data = new char[Output->Len];
    strcpy(Output->Data, Data);
    strcat(Output->Data, Other);
    return Output;
}
String *String::operator+(const char *Other) const
{
    String *Output = new String;
    Output->Len = Len + strlen(Other);
    Output->Data = new char[Output->Len];
    strcpy(Output->Data, Data);
    strcat(Output->Data, Other);
    return Output;
}
String *String::operator+(String *Other) const
{
    String *Output = new String;
    Output->Len = Len + Other->Len;
    Output->Data = new char[Output->Len];
    strcpy(Output->Data, Data);
    strcat(Output->Data, Other->Data);
    return Output;
}
String *String::operator+(String &Other) const
{
    String *Output = new String;
    Output->Len = Len + Other.Len;
    Output->Data = new char[Output->Len];
    strcpy(Output->Data, Data);
    strcat(Output->Data, Other.Data);
    return Output;
}

void String::operator=(char *NewData)
{
    if (Data != NULL)
        delete Data;
    Len = strlen(NewData);
    Data = new char[Len];
    strcpy(Data, NewData);
}
void String::operator=(const char *NewData)
{
    if (Data != NULL)
        delete Data;
    Len = strlen(NewData);
    Data = new char[Len];
    strcpy(Data, NewData);
}
void String::operator=(String *NewData)
{
    Len = NewData->Len;
    Data = new char[Len];
    strcpy(Data, NewData->Data);
}
void String::operator=(String &NewData)
{
    Len = NewData.Len;
    Data = new char[Len];
    strcpy(Data, NewData.Data);
}

void String::operator+=(char *Other)
{
    (*this) = (*this) + Other;
}
void String::operator+=(const char *Other)
{
    (*this) = (*this) + Other;
}
void String::operator+=(String *Other)
{
    (*this) = (*this) + Other;
}
void String::operator+=(String &Other)
{
    (*this) = (*this) + Other;
}

bool String::operator<(char *Other) const
{
    if (Len < strlen(Other))
        return true;
    if (Len > strlen(Other))
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] < Other[i])
            return true;
        else if (Data[i] > Other[i])
            return false;
    return false;
}
bool String::operator<(const char *Other) const
{
    if (Len < strlen(Other))
        return true;
    if (Len > strlen(Other))
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] < Other[i])
            return true;
        else if (Data[i] > Other[i])
            return false;
    return false;
}
bool String::operator<(String *Other) const
{
    if (Len < Other->Len)
        return true;
    if (Len > Other->Len)
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] < Other->Data[i])
            return true;
        else if (Data[i] > Other->Data[i])
            return false;
    return false;
}
bool String::operator<(String &Other) const
{
    if (Len < Other.Len)
        return true;
    if (Len > Other.Len)
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] < Other.Data[i])
            return true;
        else if (Data[i] > Other.Data[i])
            return false;
    return false;
}

bool String::operator<=(char *Other) const
{
    if (((*this) < Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator<=(const char *Other) const
{
    if (((*this) < Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator<=(String *Other) const
{
    if (((*this) < Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator<=(String &Other) const
{
    if (((*this) < Other) || ((*this) == Other))
        return true;
    return false;
}

bool String::operator==(char *Other) const
{
    if (Len != strlen(Other))
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] != Other[i])
            return false;
    return true;
}
bool String::operator==(const char *Other) const
{
    if (Len != strlen(Other))
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] != Other[i])
            return false;
    return true;
}
bool String::operator==(String *Other) const
{
    if (Len != Other->Len)
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] != Other->Data[i])
            return false;
    return true;
}
bool String::operator==(String &Other) const
{
    if (Len != Other.Len)
        return false;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] != Other.Data[i])
            return false;
    return true;
}

bool String::operator>=(char *Other) const
{
    if (((*this) > Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator>=(const char *Other) const
{
    if (((*this) > Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator>=(String *Other) const
{
    if (((*this) > Other) || ((*this) == Other))
        return true;
    return false;
}
bool String::operator>=(String &Other) const
{
    if (((*this) > Other) || ((*this) == Other))
        return true;
    return false;
}

bool String::operator>(char *Other) const
{
    if (Len < strlen(Other))
        return false;
    if (Len > strlen(Other))
        return true;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] > Other[i])
            return true;
        else if (Data[i] < Other[i])
            return false;
    return false;
}
bool String::operator>(const char *Other) const
{
    if (Len < strlen(Other))
        return false;
    if (Len > strlen(Other))
        return true;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] > Other[i])
            return true;
        else if (Data[i] < Other[i])
            return false;
    return false;
}
bool String::operator>(String *Other) const
{
    if (Len < Other->Len)
        return false;
    if (Len > Other->Len)
        return true;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] > Other->Data[i])
            return true;
        else if (Data[i] < Other->Data[i])
            return false;
    return false;
}
bool String::operator>(String &Other) const
{
    if (Len < Other.Len)
        return false;
    if (Len > Other.Len)
        return true;
    for (size_t i = 0; i < Len; i++)
        if (Data[i] > Other.Data[i])
            return true;
        else if (Data[i] < Other.Data[i])
            return false;
    return false;
}

bool String::operator!=(char *Other) const
{
    return !((*this) == Other);
}
bool String::operator!=(const char *Other) const
{
    return !((*this) == Other);
}
bool String::operator!=(String *Other) const
{
    return !((*this) == Other);
}
bool String::operator!=(String &Other) const
{
    return !((*this) == Other);
}

String::~String()
{
    if (Data != NULL)
    {
        delete Data;
        Len = 0;
        Data = NULL;
    }
}

std::ostream &operator<<(std::ostream &OutputFileStream, String *Value)
{
    OutputFileStream << Value->Data;
    return OutputFileStream;
}
std::ostream &operator<<(std::ostream &OutputFileStream, String &Value)
{
    OutputFileStream << Value.Data;
    return OutputFileStream;
}
