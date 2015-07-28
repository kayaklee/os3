PROJECT(os3test)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

INCLUDE_DIRECTORIES(../../src)
LINK_DIRECTORIES(../../src/common)
SET(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -g -Wall -Wno-unused-variable")

ADD_EXECUTABLE(test_page_arena test_page_arena)
TARGET_LINK_LIBRARIES(test_page_arena libos3common.a pthread)

