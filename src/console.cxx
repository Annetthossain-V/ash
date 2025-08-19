
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <any>

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
char* user_prompt() {
  std::string line;
  std::string var_name = "CFMT";
  variable::var format = variable::getvar(var_name);

  if (format.type != variable::var_mode::str)
    goto ret;

  line = std::any_cast<std::string>(format.data(format.type));
  std::print("format: {} \n", line);

ret:
  char* val = (char*) std::malloc(line.size() + 1);
  std::strcpy(val, line.c_str());
  return val;
}

char* get_stdin() {
  char* ss = NULL;
  char* s = user_prompt();
  ss = readline(s);
  free(s);
  return ss;
}

}
