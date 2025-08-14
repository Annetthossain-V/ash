
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "console.h"
#include "helper.h"
#include "core.h"

namespace console {

void user_prompt() {
  char* prompt = (char*) malloc(1024);
  getcwd(prompt, 1000);


  strcat(prompt, "\n");
  std::string exit_code = std::to_string(core::exitcode);
  strcat(prompt, exit_code.c_str());
  strcat(prompt, "$ ");

  printf("%s", prompt);
  free(prompt);
  return;
}

std::string readline() {

  // not gonna implement the full
  char* thing = (char*) malloc(1024);
  fgets(thing, 512, stdin);
  thing[strlen(thing) - 1] = '\0';

  return thing;
}

}
