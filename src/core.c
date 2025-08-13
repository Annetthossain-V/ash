#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

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


