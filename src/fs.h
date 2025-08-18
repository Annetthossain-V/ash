#pragma once
#include <filesystem>
#include <string>


namespace fs {

extern std::ifstream file_stream;

void open_file(std::string name);
std::string file_readline();
void close_file();

void rcinit();

void file_read(std::string& name);

}
