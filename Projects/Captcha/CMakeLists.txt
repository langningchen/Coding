cmake_minimum_required(VERSION 3.9) 
project(Captcha)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -std=c++11")

add_executable(main main.cpp)
target_include_directories(main PUBLIC ../../Lib)

find_library(LIBCURL curl REQUIRED)
find_library(LIBJPEG jpeg REQUIRED)
set(LIBS
    ${LIBCURL}
    ${LIBJPEG}
)
target_link_libraries(main PRIVATE ${LIBS})
