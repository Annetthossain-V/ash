#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "fs.h"

namespace fs {

bool is_open = false;
std::ifstream *file_stream;

void open_file(std::string name) {
  if (is_open)
    close_file();

  file_stream = new std::ifstream;

  is_open = true;
  return;
}

void close_file() {
  if (is_open)
    file_stream->close();
  delete file_stream;
  is_open = false;
  return;
}

std::string file_readline() {
  if (!is_open)
    throw std::runtime_error("file not open");
  
  std::string line;
  getline(*file_stream, line);
  return line;
}



}
