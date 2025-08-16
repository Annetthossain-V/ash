
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

#include <readline/readline.h>

#include "console.h"
#include "helper.h"
#include "core.h"

namespace console {

char* user_prompt() {


  char* prompt = (char*) malloc(1024);
  getcwd(prompt, 1000);


  strcat(prompt, "[");
  std::string exit_code = std::to_string(core::exitcode);
  strcat(prompt, exit_code.c_str());
  strcat(prompt, "]->$ ");



  return prompt;
}

char* get_stdin() {
  char* ss = NULL;
  char* s = user_prompt();
  ss = readline(s);
  free(s);
  return ss;
}

}
