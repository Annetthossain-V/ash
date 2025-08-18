#include <fstream>
#include <stdexcept>
#include <string>
#include <cstdlib>


#include "fs.h"
#include "core.h"
#include "io.h"

namespace fs {

std::ifstream file_stream;

void open_file(std::string name) {
  if (file_stream.is_open())
    close_file();

  file_stream.open(name);
  if (!file_stream.is_open())
    throw std::runtime_error("file not found");

  return;
}

void close_file() {
  if (file_stream.is_open())
    file_stream.close();
  return;
}

std::string file_readline() {
  if (!file_stream.is_open())
    throw std::runtime_error("file not open");
  
  std::string line;
  getline(file_stream, line);
  return line;
}

void rcinit() {
  std::string home_dir = io::envinfo("HOME");
  home_dir.append("/");
  home_dir.append(".ashrc");
 
  try {
    file_read(home_dir);
  } catch (std::runtime_error) { return; }

  return;
}

void file_read(std::string& name) {
  try {
    open_file(name);
  } catch (std::runtime_error) {
    throw std::runtime_error("cannot open file");
  }

  while (!file_stream.eof()) {
    std::string line = file_readline();

    if (line.empty() || line[0] == '#')
      continue;

    auto code = shell_core(line);
    if (code == SIG_EXIT)
      exit(0);
    else if (code == SIG_ERROR)
      exit(1);

  }

  close_file();
  return;
}

}
