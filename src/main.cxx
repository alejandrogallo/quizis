#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <string>
#include <experimental/random>
#include <ncurses.h>

void
quit_loop(){
  refresh();
  clear();
  endwin();
  exit(0);
}

void
loop_curses(Json::Value &root) {
  initscr();
  curs_set(0);
  int key;
  int knownCounter(0);
  int unknownCounter(0);
  while (true) {
    unsigned int index(
      std::experimental::randint(0, (int)root.size()-1)
    );
    //std::string wordName(root[index]["word"]);

    move(0,0);
    clrtoeol();
    printw("%s", root[index]["word"].asCString(), key);

    move(1,0);
    printw("\tK:%d\tU:%d", knownCounter, unknownCounter);

    move(2,0);
    key = getch();
    move(2,0);
    clrtoeol();

    if (key == (int)'j') {
      move(2,0);
      printw("%s", root[index]["value"].asCString());
      key = (int)'l';
    }
    if (key == (int)'h') {
      unknownCounter++;
    }
    if (key == (int)'l') {
      knownCounter++;
    }
    if (key == (int)'q') {
      quit_loop();
    }

  }
}


int main(int argc, char *argv[])
{
  if (argc == 1) {
    std::cout << "You have to give an input file as an argument!" << std::endl;
    exit(1);
  }

  setlocale(LC_ALL, "");
  //setlocale(LC_CTYPE,"C-UTF-8");
  std::string fileName(argv[1]);
  std::cout << "Reading input file " << fileName << std::endl;
  std::ifstream inputFileStream(fileName);
  std::stringstream jsonString;
  jsonString << inputFileStream.rdbuf();

  std::cout << "Parsing json content" << std::endl;
  Json::CharReaderBuilder builder;
  builder["collectComments"] = false;
  Json::Value root;
  bool parseCorrectly(Json::parseFromStream(builder, jsonString, &root, NULL));
  if (parseCorrectly) {
    std::cout << "Content parsed correctly" << std::endl;
  } else {
    std::cout << "Error while parsing" << std::endl;
    exit(1);
  }

  loop_curses(root);

  return 0;
}
