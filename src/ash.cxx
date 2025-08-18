
#include <iostream>
#include <cstdlib>
#include <nl_types.h>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <csignal>
#include <print>

#include "console.h"
#include "core.h"
#include "format.h"
#include "helper.h"
#include "utils.h"
#include "var.h"
#include "math.h"
#include "io.h"
#include "fs.h"


void flags(int argc, char** argv) { }

void ctrl_c(int signum) { 
  char* cstr = console::get_stdin();
  add_history(cstr);
  std::string str = cstr;
  if (shell_core(str) == SIG_EXIT)
    exit(0);
}

int main(int argc, char** argv) {

  signal(SIGINT, ctrl_c);
  flags(argc, argv);
  rl_initialize();
  
  fs::rcinit();

  while (true) {
    char* line_ptr = console::get_stdin();
    std::string line = line_ptr;
    add_history(line_ptr);

    int sig = shell_core(line);
     
    if (sig == SIG_EXIT)
      return 0;
    else if (sig == SIG_ERROR)
      return 1;

    free(line_ptr);
  }

  return 0;
}

int shell_core(std::string& line) {
  if (line.empty())
    return SIG_CONT;

  else if (line == "exit")
    return SIG_EXIT;

  else if (line == "version" || line == "ver") {
    std::println("Ash Version 1.1");
    return SIG_CONT;
  }

  else if (line[0] == '#')
    return SIG_CONT;
    
   
  
  std::vector<std::string> fmt_line = format::formatted_line(line);
  if (fmt_line.empty())
    return SIG_CONT;

  key_cmd key = helper::check_if_internel(fmt_line[0]);

  switch (key) {
    case key_cmd::none_key:
      break;

    case key_cmd::cd_key:
      core::invoke_except(utils::cd, std::ref(fmt_line));
      return SIG_RET;

    case key_cmd::let_key:
      if (!variable::var_handler(fmt_line))
        core::exitcode = 1;
      return SIG_RET;

    case key_cmd::alias_key:
      core::invoke_except(format::setalias, std::ref(fmt_line));
      return SIG_RET;

    case key_cmd::math_key:
      core::invoke_except(math::math_handler, std::ref(fmt_line)); 
      return SIG_RET;

    case key_cmd::import_key:
      core::invoke_except(io::import_handler, std::ref(fmt_line));
      return SIG_RET;

    case key_cmd::export_key:
      core::invoke_except(io::export_handler, std::ref(fmt_line));
      return SIG_RET;

    case key_cmd::print_key:
      utils::utils_print(fmt_line);
      return SIG_RET;

    default:
      return SIG_CONT;
    }
    

  char** exec_args = format::vector_to_char_ptr(fmt_line);
  core::exec_cmd(exec_args);
  format::formatted_line_free(exec_args);

  return SIG_RET;
}
