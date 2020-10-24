#CMake version
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.5)

#project information
PROJECT(ALGORITHM_PROJECT)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -fPIC")
endif()

ADD_SUBDIRECTORY(src)

INCLUDE_DIRECTORIES(src ${PROJECT_BINARY_DIR})

#target
ADD_EXECUTABLE(AlgorithmTest main.cpp)

SET(LIBS algorithm_impl mysqlclient)

#link lib
TARGET_LINK_LIBRARIES(AlgorithmTest ${LIBS})
