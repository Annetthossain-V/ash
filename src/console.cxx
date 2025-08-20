
#include <chrono>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <any>
#include <sys/types.h>

#include <readline/readline.h>

#include "console.h"
#include "helper.h"
#include "core.h"
#include "var.h"

#include <print>

namespace console {

// let CFMT = ":[;]->$ "
// : is current dir
// ; is exit code
// ' is execution time 
// ` is current pid
// | is new pid
std::string user_prompt() {
  int _new_pid = (int) core::new_pid;
  static int _curr_pid = -1;
  if (_curr_pid == -1)
    _curr_pid = getpid();

  std::string line;
  std::string var_name = "$CFMT";
  variable::var format = variable::getvar(var_name);
  
  if (format.type != variable::var_mode::str)
    format.type = variable::var_mode::str;

  line = std::any_cast<std::string>(format.data(format.type));
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(core::stop - core::start);
 
  std::println("fmt prompt: {}", line);
  // for (;;);

  std::string curr_dir;
  getcwd(curr_dir.data(), 512);
  curr_dir.append(curr_dir.data());
  std::println("curr dir = {}", curr_dir); 


//ret:
  return line;
}

std::string get_stdin() {
  std::string prompt = user_prompt();
  std::string line = readline(prompt.c_str()); // might be a memory leak
  return line;
}

}
