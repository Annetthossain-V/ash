#include <unistd.h>
#include <vector>
#include <stdexcept>
#include <print>

#include "utils.h"
#include "core.h"

namespace utils {

void cd(std::vector<std::string>& path) {
  if (path.size() != 2)
    throw std::runtime_error("invalid args");

  if (chdir(path[1].c_str()) != 0)
    throw std::runtime_error("path not found");

  core::exitcode = 0;
  return;
}

void utils_print(std::vector<std::string>& line) {
  bool first = true;
  for (auto &str : line) {
    if (first) {
      first = false;
      continue;
    }
    std::print("{} ", str);
  }
  std::println("");;
  
  core::exitcode = 0;
  return;
}

}
