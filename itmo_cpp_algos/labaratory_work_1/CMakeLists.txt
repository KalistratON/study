CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(HummurapiGame)

SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx64/x64/cl.exe")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

ADD_EXECUTABLE(HummurapiGame ${SOURCE_FILES} ${HEADER_FILES})