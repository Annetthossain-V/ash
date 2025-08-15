
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "console.h"
#include "core.h"
#include "format.h"
#include "helper.h"
#include "utils.h"
#include "var.h"

#define SIG_CONT  22
#define SIG_RET   73
#define SIG_ERROR 67
#define SIG_EXIT  87


void flags(int argc, char** argv) { }

int main(int argc, char** argv) {

  flags(argc, argv);

  while (true) {
    console::user_prompt();
    std::string line = console::readline();

    int sig = shell_core(line);
    switch (sig) {
      case SIG_CONT:
      case SIG_RET:
        continue;
      case SIG_ERROR:
        return 1;
      case SIG_EXIT:
        return 0;
    }
  }
  return 0;
}

int shell_core(std::string& line) {
  if (line.empty())
    return SIG_CONT;
  else if (line == "exit")
    return SIG_EXIT;

  std::vector<std::string> fmt_line = format::formatted_line(line);
    
  enum key_cmd key = helper::check_if_internel(fmt_line[0]);
  switch (key) {
    case key_cmd::none_key:
      break;
    case key_cmd::cd_key:
      if (fmt_line.size() != 2) {
        std::cerr << "too many arguments for cd\n";
        return SIG_CONT;
      }
      if (!utils::cd(fmt_line[1]))
        perror("cd");
      return SIG_RET;

    case key_cmd::let_key:
      if (!var_handler(fmt_line))
        core::exitcode = 1;
      return SIG_RET;
    default:
      return SIG_CONT;
    }
    

  char** exec_args = format::vector_to_char_ptr(fmt_line);
  core::exec_cmd(exec_args);
  format::formatted_line_free(exec_args);

  return SIG_RET;
}
