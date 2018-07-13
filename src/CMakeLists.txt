link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(
  quizis
  main.cxx
)

target_link_libraries(quizis jsoncpp)

target_include_directories(
  quizis
  PUBLIC
  ${CMAKE_BINARY_DIR}/include
)

