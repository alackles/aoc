#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>

#define BITLEN 12


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

// find the most common bit at an index 
// given a vector of bitsets and an index
bool most_common_bit(const std::vector<std::bitset<BITLEN>> & vec, const size_t & index) {
  int common_bit = 0;
  for (auto entry : vec) {
    if (entry[index] == 0) {
      common_bit--;
    } else {
      common_bit++;
    }
  }
  return common_bit >= 0;
}  

// wrapper for least common bit
bool least_common_bit(const std::vector<std::bitset<BITLEN>> & vec, const size_t & index) {
  return !most_common_bit(vec, index);
}

int get_oxygen_int(std::vector<std::bitset<BITLEN>> oxygen_vec) {

  int index = BITLEN-1;

  // initialize outside loop
  std::vector<std::bitset<BITLEN>> keep;
  bool mcb;
  
  while (oxygen_vec.size() != 1 && index >= 0) {

    // empty our candidate solutions
    keep.clear(); 

    // find the most common bit at the current index
    mcb = most_common_bit(oxygen_vec, index);

    // loop through to find candidate solns
    for (auto reading : oxygen_vec) {
      if (reading[index] == mcb) {
        keep.push_back(reading);
      }
    }

    // set oxygen to only our candidate solutions
    oxygen_vec = keep;

    // decrement
    index--;
  }

  return oxygen_vec[0].to_ulong();
}

int get_co2_int(std::vector<std::bitset<BITLEN>> co2_vec) {

  int index = BITLEN-1;

  // initialize outside loop
  std::vector<std::bitset<BITLEN>> keep;
  bool lcb;
  
  while (co2_vec.size() != 1 && index >= 0) {

    // empty our candidate solutions
    keep.clear(); 

    // find the most common bit at the current index
    lcb = least_common_bit(co2_vec, index);

    // loop through to find candidate solns
    for (auto reading : co2_vec) {
      if (reading[index] == lcb) {
        keep.push_back(reading);
      }
    }

    // set oxygen to only our candidate solutions
    co2_vec = keep;

    // decrement
    index--;
  }

  return co2_vec[0].to_ulong();

}

int main() {

  // let's start with the oxygen one
  std::vector<std::bitset<BITLEN>> oxygen = parse_bitset("data/03.txt");
  auto co2 = oxygen;

  int oxy_int = get_oxygen_int(oxygen);
  int co2_int = get_co2_int(co2);
  
  std::cout << oxy_int * co2_int << std::endl;
}