link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(
  quizis
  main.cxx
)

add_executable(
  quizis-gtk
  gtk/main.cxx
)

target_compile_options(quizis
PUBLIC
  -O0
  -g
  -Wall -Werror -Wextra
  -std=c++14
  -pedantic
)

target_compile_options(quizis-gtk
PUBLIC
  -O0
  -g
  -Wall -Werror -Wextra
  -std=c++14
  -pedantic
)

target_link_libraries(quizis jsoncpp ncursesw)
target_link_libraries(quizis-gtk jsoncpp ${GTKMM_LIBRARIES})

target_include_directories(
  quizis-gtk
  PUBLIC
  ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  quizis
  PUBLIC
  ${CURSES_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}/include
)

install(TARGETS quizis DESTINATION bin)
install(TARGETS quizis-gtk DESTINATION bin)
