
#include <sys/_termios.h>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <string>
#include <cstdlib>

#include "core.h"
#include "console.h"

namespace core {

extern "C" void set_buffer(bool enable) {
  static bool enabled = true;
  static struct termios old;
  struct termios newt;

  if (enable && !enabled) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    enabled = true;
  }
  else if (!enable && enabled) {
    tcgetattr(STDIN_FILENO, &newt);
    old = newt;

    newt.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    enabled = false;
  }
  return;
}

extern "C" int getch() {
  set_buffer(false);
  int ch = getchar();

  set_buffer(true);
  return ch;
}


extern "C" void core_shell() {
  
  std::string line = console::readline();
  if (line == "exit")
    std::exit(0);
  else if (line == "CTRL_C")
    return;
  
  std::string formated_line;



}

void exec_cmd() {}

}


