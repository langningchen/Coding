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
                usleep(100000);
            SUBMISSION Submission;
            OUTPUT_IF_FAILED(Submission.Load(JudgingList.front()))
            JudgingList.pop();
            OUTPUT_IF_FAILED(Submission.Judge())
            Logger.Info(Submission.WorkDir);
            OUTPUT_IF_FAILED(Submission.Save())
        } });
}

RESULT JUDGING_LIST::Add(SUBMISSION Submission, int &SubmissionID)
{
    SubmissionAddMutex.lock();
    SubmissionID = 0;
    DIR *SubmissionDir = opendir(Settings.GetSubmissionBaseFolder().c_str());
    struct dirent *SubmissionDirEntry;
    while ((SubmissionDirEntry = readdir(SubmissionDir)) != NULL)
        if (SubmissionDirEntry->d_type == DT_DIR)
            SubmissionID = std::max(SubmissionID, atoi(SubmissionDirEntry->d_name));
    SubmissionID++;
    Submission.ID = SubmissionID;
    Submission.UpdateWorkDir();
    Submission.CopyTestGroups();
    Logger.Info(Submission.WorkDir);
    RETURN_IF_FAILED_WITH_OPERATION(Submission.Save(), SubmissionAddMutex.unlock())
    JudgingList.push(SubmissionID);
    SubmissionAddMutex.unlock();
    CREATE_RESULT(true, "Submission added to judging list")
}

JUDGING_LIST JudgingList;
