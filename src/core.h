#pragma once
#include <stdbool.h>

extern int exitcode;

void set_buffer(bool enable);

void exec_cmd(char** argv);
