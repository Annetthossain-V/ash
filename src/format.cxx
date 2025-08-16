#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "iostream"

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

std::vector<std::string> merge_quoted(const std::vector<std::string>& words) {
  std::vector<std::string> result;
  std::string buffer;
  bool in_quotes = false;

  for (const auto& word : words) {
    if (!in_quotes) {
      if (!word.empty() && word.front() == '"') {
        in_quotes = true;
        buffer = word.substr(1);
        if (!buffer.empty() && buffer.back() == '"') {
          buffer.pop_back();
          in_quotes = false;
          result.push_back(buffer);
          buffer.clear();
        }
      } else {
        result.push_back(word);
      }
    } else {
      buffer += (buffer.empty() ? "" : " ") + word;
      if (!word.empty() && word.back() == '"') {
        buffer.pop_back();
        result.push_back(buffer);
        buffer.clear();
        in_quotes = false;
      }
    }
  }

  return result;
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


