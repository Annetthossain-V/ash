#pragma once
#include <string>

namespace console {

char* get_stdin();

}


#ifndef _BUILD64XX

extern "C" char* readline(char* s);
extern "C" void add_history(char* s);
extern "C" void rl_initialize();

#endif
