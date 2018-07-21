link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(
  quizis
  main.cxx
)

target_compile_options(quizis
PUBLIC
  -O0
  -g
  -Wall -Werror -Wextra
  -std=c++14
  -pedantic
)

target_link_libraries(quizis jsoncpp ncursesw)

target_include_directories(
  quizis
  PUBLIC
  ${CURSES_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}/include
)

install(TARGETS quizis DESTINATION bin)
