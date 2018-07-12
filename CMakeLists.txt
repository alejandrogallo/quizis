cmake_minimum_required(VERSION 3.0)
project(quizis)


include(ExternalProject)
ExternalProject_Add(jsoncpp
GIT_REPOSITORY    https://github.com/open-source-parsers/jsoncpp
GIT_TAG           master
PREFIX            ${CMAKE_BINARY_DIR}/lib
CMAKE_ARGS        -DCMAKE_BUILD_TYPE=debug
                  -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=ON
                  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/${PREFIX}
BUILD_COMMAND     make
INSTALL_COMMAND   ""
TEST_COMMAND      ""
)
ExternalProject_Get_Property(jsoncpp SOURCE_DIR)
set(jsoncpp_SOURCE_DIR ${SOURCE_DIR})




add_subdirectory(src)

