cmake_minimum_required(VERSION 3.9)
project(OJ)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(main
    Database.cpp
    Result.cpp
    HTTPRequest.cpp
    HTTPResponse.cpp
    JudgeResult.cpp
    Logger.cpp
    Problem.cpp
    ProblemList.cpp
    Sample.cpp
    Settings.cpp
    Socket.cpp
    Submission.cpp
    TestCase.cpp
    TestGroup.cpp
    Utilities.cpp
    WebDataProceed.cpp
    JudgingList.cpp
    Mutexes.cpp
    main.cpp)

find_library(LIBTHREAD pthread REQUIRED)
find_library(LIBCURL curl REQUIRED)
set(LIBS
    ${LIBTHREAD}
    ${LIBCURL}
)
target_link_libraries(main PRIVATE ${LIBS})
target_link_libraries(main PRIVATE mysqlcppconn)
target_include_directories(main PRIVATE "/usr/include/mysql")
