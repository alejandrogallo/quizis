add_executable(
  quizis
  main.cxx
)

target_include_directories(
  quizis
  PUBLIC
  ${jsoncpp_SOURCE_DIR}/include
)

