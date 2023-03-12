#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

#define BITLEN 5


// bitset parser function
// I like reading things into memory before working with them
// Sue me
std::vector<std::bitset<BITLEN>> parse_bitset(const std::string & fname) {
  
  std::vector<std::bitset<BITLEN>> vec;
  std::ifstream datafile(fname);
  std::string line;
  
  while (getline(datafile, line)) {
    std::bitset<BITLEN> bit_line(line);
    vec.push_back(bit_line);
  }
  
  return vec;
} 

int main() {
  std::vector<std::bitset<BITLEN>> power = parse_bitset("data/toy.txt");
  
  // find most common bit 
  std::vector<int> ref_vec(BITLEN, 0);
  for (auto line : power) {
    for (int i = 0; i < BITLEN; i++) {
      if (line[i] == 0) {
        ref_vec[i]--;
      } else {
        ref_vec[i]++;
      }
    }
  }
  
  // convert that to 1s and 0s
  std::bitset<BITLEN> gamma; 
  for (size_t i = 0; i < BITLEN; i++) {
    gamma[i] = (ref_vec[i] > 0) ? 1 : 0; 
  }
  std::bitset<BITLEN> epsilon = ~gamma;

  std::cout << gamma.to_ulong() * epsilon.to_ulong() << std::endl;
}