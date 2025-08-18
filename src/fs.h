#pragma once
#include <filesystem>
#include <string>


namespace fs {

extern bool is_open;
extern std::ifstream* file_stream;

void open_file(std::string name);
std::string file_readline();
void close_file();

void set_rc();


}
