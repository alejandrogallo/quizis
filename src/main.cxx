#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <string>
#include <experimental/random>

void
loop(Json::Value &root) {
  bool stop(false);
  char key;
  while (! stop) {
    unsigned int index(
      std::experimental::randint(0, (int)root.size()-1)
    );
    std::cout << root[index]["word"] << std::endl;
    std::cin >> key;
    if (key == 'i') {
      std::cout << root[index]["value"] << std::endl;
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

  for (unsigned int i(0) ; i < root.size() ; i++) {
    Json::Value word(root[i]);
    std::cout << word["word"] << std::endl;
  }

  loop(root);


//Json::Reader reader;

  return 0;
}
