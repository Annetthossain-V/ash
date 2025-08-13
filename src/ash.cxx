
#include <iostream>

#include "x64.h"
#include "console.h"
#include "core.h"


void flags(int argc, char** argv);

int main(int argc, char** argv) {
  if (argc > 1) {
    char msg[] = "[Warn] ignored flags";
    x64::warnlog(msg);
  }

  loop {
    std::cout << console::prompt();


    break;
  }

  return 0;
}
