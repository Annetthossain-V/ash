
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "console.h"
#include "core.h"
#include "format.h"
#include "helper.h"
#include "utils.h"

<<<<<<< HEAD

#define SIG_CONT 22
#define SIG_RET 73


void flags(int argc, char** argv) { }
=======
extern int shell_core();
>>>>>>> f0b8307 (shell_core)

void flags(int argc, char** argv) { }

int main(int argc, char** argv) {

  flags(argc, argv);
  return shell_core();
}

int shell_core() {

  while (true) {

    console::user_prompt();
    std::string line = console::readline();

    if (line == "exit")
      return 0;
    else if (line.empty())
      continue;

    std::vector<std::string> fmt_line = format::formatted_line(line);
    
    enum key_cmd key = helper::check_if_internel(fmt_line[0]);
    switch (key) {
      case key_cmd::none_key:
        break;

      case key_cmd::cd_key:
        if (fmt_line.size() != 2) {
          std::cerr << "too many arguments for cd\n";
          continue;
        }
        if (!utils::cd(fmt_line[1]))
          perror("cd");

      default:
        continue;
    }
    

    char** exec_args = format::vector_to_char_ptr(fmt_line);
    core::exec_cmd(exec_args);
    format::formatted_line_free(exec_args);
  }  

  return 0;
}
