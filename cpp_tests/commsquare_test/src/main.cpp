#include "FileReader.hpp"
#include "Regex.hpp"
#include <iostream>

int main() {
  FileReader fr("../../data/file.txt");
  fr.print();

  Regex rgx("a|e|i|o|u");
  std::cout << rgx.replace(fr.buffer().data(), "[$&]") << '\n';
}
