cmake_minimum_required(VERSION 3.9) 
project(MicrosoftShowsDownloader)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(main main.cpp)
target_include_directories(main PUBLIC ../../Lib)

find_library(LIBCURL curl REQUIRED)
set(LIBS
    ${LIBCURL}
)
target_link_libraries(main PRIVATE ${LIBS})
