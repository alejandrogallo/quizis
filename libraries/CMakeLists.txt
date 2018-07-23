include(ExternalProject)

find_package(Curses REQUIRED)
message("CURSES_INCLUDE_DIR ${CURSES_INCLUDE_DIR}")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
message("GTKMM_LIBRARY_DIRS ${GTKMM_LIBRARY_DIRS}")
message("GTKMM_LIBRARIES ${GTKMM_LIBRARIES}")
message("GTKMM_INCLUDE_DIRS ${GTKMM_INCLUDE_DIRS}")

ExternalProject_Add(jsoncpp_project
GIT_REPOSITORY    https://github.com/open-source-parsers/jsoncpp
GIT_TAG           80bc776
PREFIX            ${CMAKE_BINARY_DIR}/libraries
CMAKE_ARGS        -DCMAKE_BUILD_TYPE=debug
                  -DBUILD_STATIC_LIBS=OFF -DBUILD_SHARED_LIBS=ON
                  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/
BUILD_COMMAND     make
INSTALL_COMMAND   make install
TEST_COMMAND      ""
)
ExternalProject_Get_Property(jsoncpp_project SOURCE_DIR)
add_dependencies(quizis jsoncpp_project)
