#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "core.h"

int exitcode = 0;

void set_buffer(bool enable) {
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

void exec_cmd(char** argv) {
  
  int status;
  pid_t process = fork();

  if (process < 0) {
    perror("fork failed");
    exit(1);
  }

  else if (process == 0) {
    // chiled
    if (execvp(argv[0], argv) == 1) {
      perror("execvp failed");
      exit(1);
    }
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
