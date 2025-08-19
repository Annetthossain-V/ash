#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <print>

#include "core.h"

namespace core {

int exitcode = 0;

void disable_ctrl_c() {}

void exec_cmd(char** argv) {
  int status;
  pid_t process = fork();

  if (process < 0) {
    perror("fork failed");
    exit(1);
  }

  else if (process == 0) {
    // chiled
    execvp(argv[0], argv);
    std::println("{} not found!", argv[0]);
    exit(1);
  }
  else {
    // parent
    if (waitpid(process, &status, 0) == -1) {
      perror("waitpid failed");
      exit(1);
    }

    if (WIFEXITED(status))
      exitcode = WEXITSTATUS(status);
    else 
     exitcode = -1;
  }

  return;
}



}
