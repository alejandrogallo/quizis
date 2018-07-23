#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <string>
#include <cstdlib>
#include <ncurses.h>
#include <vector>

void
quit_loop(){
  refresh();
  clear();
  endwin();
  exit(0);
}

class WordStatistic {
public:
  unsigned int easy;
  unsigned int medium;
  unsigned int difficult;

  WordStatistic(){
    easy = 0;
    medium = 0;
    difficult = 0;
  }

};

void
loop_curses(Json::Value &root) {
  initscr();
  curs_set(0);
  std::vector<WordStatistic> statistics;
  statistics.resize((int)root.size());
  int key;
  int knownCounter(0);
  int unknownCounter(0);
  while (true) {
    unsigned int index(
      rand() % (int)root.size()
    );
    //std::string wordName(root[index]["word"]);
    int height;
    int width;
    getmaxyx(stdscr, height, width);

    move(0,0);
    clrtoeol();
    printw(
      "%s (%d %d %d)",
      root[index]["word"].asCString(),
      statistics[index].easy,
      statistics[index].medium,
      statistics[index].difficult
    );

    move(1,0);
    printw("\tK:%d\tU:%d", knownCounter, unknownCounter);

    move(2,0);
    key = getch();
    move(2,0);
    clrtoeol();

    if (key == (int)'h') {
      move(2,0);
      printw("%s", root[index]["value"].asCString());
      key = (int)'l';
      getch();
      for (int i(0) ; i < height-3 ; i++) {
        move(2 + i, 0);
        clrtoeol();
      }
    }
    if (key == (int)'j') {
      statistics[index].easy += 1;
    }
    if (key == (int)'k') {
      statistics[index].medium += 1;
    }
    if (key == (int)'l') {
      statistics[index].difficult += 1;
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
