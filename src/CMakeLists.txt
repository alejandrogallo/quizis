link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(
  quizis
  main.cxx
)

target_link_libraries(quizis jsoncpp curses)

target_include_directories(
  quizis
  PUBLIC
  ${CURSES_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}/include
)

