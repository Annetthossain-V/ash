
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "console.h"
#include "core.h"
#include "format.h"

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

    char** encoded_data = formatted_line(line);
    exec_cmd(encoded_data);

    free(line);
  }
  

  return 0;

}
