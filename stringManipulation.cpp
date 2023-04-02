#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void print(std::string string, int sleep_time = 50) {
  for (int i = 0; i < string.size(); ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    std::cout << string[i];
  }
  std::cout << std::endl;
}
std::string removeSpecialCharacters(std::string line) {
  std::string temp = "";
  for (int i = 0; i < line.size(); ++i) {
    if ((line[i] >= 'a' && line[i] <= 'z') ||
        (line[i] >= 'A' && line[i] <= 'Z')) {
      temp = temp + line[i];
    } else {
      temp += " ";
    }
  }
  line = temp;
  std::transform(line.begin(), line.end(), line.begin(), ::tolower);
  return line;
}

std::vector<std::string> split(std::string list) {
  std::vector<std::string> listArray;
  std::string temp = "";
  const char splitObject = ' ';
  for (int i = 0; i < list.size(); ++i) {
    if (list[i] != splitObject) {
      temp += list[i];
    } else {
      listArray.push_back(temp);
      temp = "";
    }
  }

  if (temp != "") {
    listArray.push_back(temp);
  }

  return listArray;
}
std::string lower(std::string string, bool upper = false) {
  removeSpecialCharacters(string);
  if (upper == false) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
  } else {
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
  }
  return string;
}