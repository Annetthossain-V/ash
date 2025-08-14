#pragma once
#include <stdbool.h>

namespace core {

extern int exitcode;

void set_buffer(bool enable);

void exec_cmd(char** argv);

}
