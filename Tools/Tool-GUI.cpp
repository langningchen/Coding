#include <iostream>
#include <vector>
#include <string>
#include <termio.h>
using namespace std;
struct termios OldConsoleSettings;
void ConsoleInit()
{
    struct termios ConsoleSettings;
    tcgetattr(0, &ConsoleSettings);
    OldConsoleSettings = ConsoleSettings;
    ConsoleSettings.c_lflag &= (~ICANON);
    ConsoleSettings.c_lflag &= (~ECHO);
    ConsoleSettings.c_cc[VTIME] = 0;
    ConsoleSettings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ConsoleSettings);
}
void ConsoleUninit()
{
    tcsetattr(0, TCSANOW, &OldConsoleSettings);
}
int GetOperation()
{
    while (1)
    {
        char Input = getchar();
        if (Input == 27)
        {
            Input = getchar();
            Input = getchar();
            if (Input == 65)
                return 1;
            if (Input == 66)
                return 2;
        }
        if (Input == 10)
            return 0;
        if (Input == 27)
            return -1;
        cout << (int)Input << endl;
    }
    return 0;
}
int Select(string Title, vector<string> List)
{
    int CurrentSelect = 0;
    while (1)
    {
        system("clear");
        cout << Title << endl;
        int Counter = 0;
        for (auto i : List)
        {
            if (Counter == CurrentSelect)
                cout << "\33[7m" << i << "\33[0m" << endl;
            else
                cout << i << endl;
            Counter++;
        }
        switch (GetOperation())
        {
        case -1:
            return -1;
            break;
        case 0:
            return CurrentSelect;
            break;
        case 1:
            if (CurrentSelect > 0)
                CurrentSelect--;
            break;
        case 2:
            if (CurrentSelect < List.size() - 1)
                CurrentSelect++;
            break;
        }
    }
}
int main()
{
    ConsoleInit();
    while (1)
    {
        int Selected = Select("Please select the OJ.", {"Luogu", "Etiger", "Codeforces", "UVa"});
        if (Selected == -1)
            break;
        if (Selected == 0)
        {
            while (1)
            {
                int Selected = Select("Please select the operation.", {"Create new", "Submit code", "Clock in"});
                if (Selected == -1)
                    break;
                if (Selected == 0)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Luogu/" + QuestionID + ".cpp GetQuestionDetail").c_str());
                }
                if (Selected == 1)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Luogu/" + QuestionID + ".cpp SubmitCode").c_str());
                }
                if (Selected == 2)
                {
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Luogu/P0000.cpp ClockIn").c_str());
                }
            }
        }
        if (Selected == 1)
        {
            while (1)
            {
                int Selected = Select("Please select the operation.", {"Create new", "Submit code", "Clock in"});
                if (Selected == -1)
                    break;
                if (Selected == 0)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Etiger/" + QuestionID + ".cpp GetQuestionDetail").c_str());
                }
                if (Selected == 1)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Etiger/" + QuestionID + ".cpp SubmitCode").c_str());
                }
                if (Selected == 2)
                {
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Etiger/0000.cpp ClockIn").c_str());
                }
            }
        }
        if (Selected == 2)
        {
            while (1)
            {
                int Selected = Select("Please select the operation.", {"Create new", "Submit code"});
                if (Selected == -1)
                    break;
                if (Selected == 0)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Codeforces/" + QuestionID + ".cpp GetQuestionDetail").c_str());
                }
                if (Selected == 1)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/Codeforces/" + QuestionID + ".cpp SubmitCode").c_str());
                }
            }
        }
        if (Selected == 3)
        {
            while (1)
            {
                int Selected = Select("Please select the operation.", {"Create new", "Submit code"});
                if (Selected == -1)
                    break;
                if (Selected == 0)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/UVa/" + QuestionID + ".cpp GetQuestionDetail").c_str());
                }
                if (Selected == 1)
                {
                    system("clear");
                    string QuestionID;
                    cout << "Please input the question ID: ";
                    ConsoleUninit();
                    cin >> QuestionID;
                    ConsoleInit();
                    system("clear");
                    system(string("/workspaces/Coding/Tools/Tool /workspaces/Coding/UVa/" + QuestionID + ".cpp SubmitCode").c_str());
                }
            }
        }
    }
    ConsoleUninit();
    return 0;
}
