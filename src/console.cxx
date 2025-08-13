#include "core.h"
#include <iostream>
#include <string>
#include <unistd.h>

namespace console {

unsigned int exitcode = 0;


std::string prompt() {
  std::string prompt;
  
  char* cwd = prompt.data();
  getcwd(cwd, 1024);
  prompt.append(cwd);

  prompt.append("#\n");
  prompt.append(std::to_string(exitcode));
  prompt.append("$ ");

  return prompt;
}

std::string readline() {

  int ch = 0;
  std::string line;

  do {
    ch = core::getch();
    switch(ch) {
      case TAB:
      case BACK_SPACE:
      case CTRL_C:
        return "CTRL_C";
      default:
        break;
    }


  } while (ch != '\n');

  return line;
}


}

