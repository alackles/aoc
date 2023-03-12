#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// tokenize function from: https://www.techiedelight.com/split-string-cpp-using-delimiter/
std::vector<std::string> tokenize(const std::string &s, const char delim){
    std::vector<std::string> out;
    std::string::size_type beg = 0;
    for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end) {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }
 
    out.push_back(s.substr(beg));
    return out;
}

std::vector<std::vector<std::string>> parser(const std::string & fname) {
  std::vector<std::vector<std::string>> vec;
  std::string line;

  std::ifstream datafile(fname);
  const char delim = ' ';
  while (getline(datafile, line)) {
    vec.push_back(tokenize(line, delim));
  }
  return vec;
}

int main() {
  std::vector<std::vector<std::string>> depths = parser("data/02.txt");
  int horiz = 0;
  int vert = 0; 

  std::string direc;
  int val;
  
  for (auto i : depths) {
    direc = i[0];
    val = std::stoi(i[1]);
    if (direc == "forward") {
      horiz += val;
    } else if (direc == "down") {
      vert += val; 
    } else if (direc == "up") {
      vert -= val;
    } else {
      std::cout << "ERROR" << std::endl;
      return -1;
    }
  }
  std::cout << horiz * vert << std::endl;
}