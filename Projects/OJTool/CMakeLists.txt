cmake_minimum_required(VERSION 3.9) 
project(OJTool)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -std=c++11")

add_executable(main main.cpp)
target_include_directories(main PUBLIC /workspaces/Coding/Lib)

find_library(LIBCURL curl REQUIRED)
find_library(LIBJPEG jpeg REQUIRED)
find_library(LIBTIDY tidy REQUIRED)
set(LIBS
    ${LIBCURL}
    ${LIBJPEG}
    ${LIBTIDY}
)
target_link_libraries(main PRIVATE ${LIBS})
