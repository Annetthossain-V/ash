
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "console.h"

void flags(int argc, char** argv) { }


int main(int argc, char** argv) {

  flags(argc, argv);


  while (true) {

    user_prompt();
    char* line = readline();
    if (!strcmp(line, "exit"))
      return 0;
    else if (!strcmp(line, "") || !strcmp(line, " "))
      continue;


  }
  

  return 0;

}
