#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "io.h"
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

std::vector<std::string> split_space(const std::string& s) {
  std::vector<std::string> result;
  std::string token;
  bool in_quotes = false;
  bool escape = false;

  for (char c : s) {
    if (escape) {
      token += c;
      escape = false;
    }
    else if (c == '\\') {
      escape = true;
    }
    else if (c == '"') {
      in_quotes = !in_quotes;
    }
    else if (c == ' ' && !in_quotes) {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
    }
    else {
      token += c;
    }
  }
  
  if (!token.empty())
    result.push_back(token);

  return result;
}

void replace_home(std::vector<std::string>& line) {
  
  std::string dir = io::envinfo("HOME");
  size_t pos;
  size_t index = 0;

  for (auto &str : line) {
    size_t pos = 0;
    while ((pos = str.find("~", pos)) != std::string::npos) {
      str.replace(pos, 1, dir);
      pos += dir.length();
    }
  }
}

std::vector<std::string> formatted_line(std::string line) {

  std::vector<std::string> line_tokens = split_space(line);
  replace_home(line_tokens);
  // TODO: replace vars and envs

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


