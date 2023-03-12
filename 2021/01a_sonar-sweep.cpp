#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> FileArray(const std::string & fname) {
  std::vector<int> new_array;
  std::string line;
  std::ifstream datafile(fname);
  while (getline(datafile, line)) {
    new_array.push_back(std::stoi(line));
  }
  return new_array;
}

int main() {
  std::vector<int> depths = FileArray("data/01a.txt");
  int greaters = 0;
  for (int i = 1; i < depths.size(); i++) {
    if (depths[i] > depths[i-1]) {
      greaters++;
    }
  }
  std::cout << greaters << std::endl;
}