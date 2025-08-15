#pragma once
#include <string>

int shell_core(std::string& line);

namespace core {

extern int exitcode;

void set_buffer(bool enable);

void exec_cmd(char** argv);

}
