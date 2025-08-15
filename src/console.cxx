
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

#ifdef _BUILD64XX
#include <readline/readline.h>
// make the lsp shut up
#endif

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
  #ifdef _BUILD64XX
  char* s = user_prompt();
  ss = readline(s);
  free(s);
  #endif
  return ss;
}

}
