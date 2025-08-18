#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <any>

#include "io.h"
#include "format.h"
#include "var.h" 

static int split_len = 0;


namespace format {

std::map<std::string, std::string> alias;

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

  for (auto &str : line) {
    size_t pos = 0;
    while ((pos = str.find("~", pos)) != std::string::npos) {
      str.replace(pos, 1, dir);
      pos += dir.length();
    }
  }

  return;
}

void replace_asterisk(std::vector<std::string>& line) {}

void replace_alias(std::vector<std::string>& line) {
  if (line[0] == "alias")
    return;

  for (auto &str : line) {
    if (alias.contains(str)) {
      auto item = alias.find(str);
      str = item->second;
    }
  }
}

void replace_vars(std::vector<std::string>& line) {
  variable::var data(variable::var_mode::i32, 1);
  if (line[0] == "math")
    return;

  for (auto &str : line) {
    if (str[0] == '$') {
      variable::var curr_var = variable::getvar(str);
      std::string content;
      switch(curr_var.type) {
        case variable::var_mode::i32:
          content = std::to_string(std::any_cast<int>(curr_var.data(curr_var.type)));
          break;
        case variable::var_mode::f32:
          content = std::to_string(std::any_cast<float>(curr_var.data(curr_var.type)));
          break;
        case variable::var_mode::str:
          content = std::any_cast<std::string>(curr_var.data(curr_var.type));
          break;
      }
      str = content;
    } 
  }

  return;
}

std::vector<std::string> formatted_line(std::string line) {

  std::vector<std::string> line_tokens = split_space(line);
  replace_home(line_tokens);
  replace_vars(line_tokens);
  replace_alias(line_tokens);

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

void setalias(std::vector<std::string> &line) {
  std::string name;
  std::string val;

  if (line.size() < 3 || (line[2] == "=" && line.size() < 4))
    throw std::runtime_error("invalid args");

  if (line[2] == "=") {
    name = line[1];
    val = line[3];
  } else {
    name = line[1];
    val = line[2];
  }
  alias.insert_or_assign(name, val);
  return;
}


}


