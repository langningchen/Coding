#include "JudgingList.hpp"
#include "Submission.hpp"
#include "Settings.hpp"
#include "Mutexes.hpp"
#include <thread>
#include <unistd.h>
#include <dirent.h>

JUDGING_LIST::JUDGING_LIST() {}
JUDGING_LIST::~JUDGING_LIST()
{
    while (!JudgingList.empty())
        ;
}

void JUDGING_LIST::Init()
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/JudgingList.log");
    new std::thread([this]()
                    {
        while (true)
        {
            while (JudgingList.empty())
                sleep(1);
            SUBMISSION Submission;
            if (!Submission.Load(JudgingList.front()))
                Logger.Error("Failed to load submission " + std::to_string(JudgingList.front()));
            JudgingList.pop();
            Submission.Judge();
        } });
}

int JUDGING_LIST::Add(SUBMISSION Submission)
{
    SubmissionAddMutex.lock();
    int SubmissionID = 0;
    DIR *SubmissionDir = opendir(Settings.GetSubmissionBaseFolder().c_str());
    struct dirent *SubmissionDirEntry;
    while ((SubmissionDirEntry = readdir(SubmissionDir)) != NULL)
        if (SubmissionDirEntry->d_type == DT_DIR)
            SubmissionID = std::max(SubmissionID, atoi(SubmissionDirEntry->d_name));
    SubmissionID++;
    Submission.ID = SubmissionID;
    Submission.UpdateWorkDir();
    Submission.CopyTestGroups();
    if (Submission.Save())
        JudgingList.push(SubmissionID);
    else
        SubmissionID = 0;
    SubmissionAddMutex.unlock();
    return SubmissionID;
}

JUDGING_LIST JudgingList;
