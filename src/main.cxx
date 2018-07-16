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
  exit(0);
}

void
loop(Json::Value &root) {
  initscr();
  curs_set(0);
  bool stop(false);
  int key;
  int counter;
  while (! stop) {
    move(0,0);
    unsigned int index(
      std::experimental::randint(0, (int)root.size()-1)
    );
    //std::string wordName(root[index]["word"]);
    //printw("%s", root[index]["word"]);
    deleteln();
    printw("%s %d ", root[index]["word"].asCString(), key);
    move(2,0);
    key = getch();
    deleteln();
    move(2,0);
    if (key == (int)'i') {
      printw("%s", root[index]["value"].asCString());
    } else if (key == (int)'q') {
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

  loop(root);

  return 0;
}
