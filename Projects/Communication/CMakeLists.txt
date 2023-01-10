cmake_minimum_required(VERSION 3.9) 
project(Communication)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -std=c++11")

add_executable(server Server.cpp)
add_executable(client Client.cpp)
target_include_directories(server PUBLIC /workspaces/Coding/Lib)
target_include_directories(client PUBLIC /workspaces/Coding/Lib)

find_library(LIBCURL curl REQUIRED)
find_library(LIBPTHREAD pthread REQUIRED)
set(LIBS
    ${LIBCURL}
    ${LIBPTHREAD}
)
target_link_libraries(server PRIVATE ${LIBS})
target_link_libraries(client PRIVATE ${LIBS})
