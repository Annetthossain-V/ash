


#include "x64.h"
#include "console.h"
#include "core.h"


void flags(int argc, char** argv);


int main(int argc, char** argv) {
  if (argc > 1)
    warnlog("[Warn] ignored arguments");

  loop {
    prompt();
    core_shell();
  }

  return 0;
}
