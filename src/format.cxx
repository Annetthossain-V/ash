#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "format.h"

static int split_len = 0;

namespace format {

char** vector_to_char_ptr(std::vector<std::string>& split) {
  int vector_len = split.size();
  int index = 0;
  char** c_array = (char**) std::malloc(sizeof(char*) * vector_len + 1);

  while (index != vector_len) {
    c_array[index] = (char*) std::malloc(split[index].length() + 4);
    std::strcpy(c_array[index], split[index].c_str());
    index++;
  }

  c_array[index] = NULL;

  return c_array;
}

std::vector<std::string> split_space(const std::string& str) {
  std::vector<std::string> tokens;
  std::istringstream iss(str);
  std::string token;
  split_len = 0;

  while (iss >> token) {
    tokens.push_back(token);
  }

  return tokens;
}

std::vector<std::string> formatted_line(std::string line) {

  std::vector<std::string> line_tokens = split_space(line);
  

  split_len = line_tokens.size();
  return line_tokens;
}

void formatted_line_free(char** line) {
  int index = 0;
  while (index < split_len) {
    free(line[index]);
    index++;
  }
  free(line);
}

}
