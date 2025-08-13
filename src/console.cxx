#include "core.h"
#include <iostream>
#include <string>
#include <unistd.h>

namespace console {

extern "C" unsigned int exitcode = 0;


extern "C" void prompt() {
  std::string prompt;
  
  char* cwd = prompt.data();
  getcwd(cwd, 1024);
  prompt.append(cwd);

  prompt.append("#\n");
  prompt.append(std::to_string(exitcode));
  prompt.append("$ ");

  std::cout << prompt;
  return;
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

