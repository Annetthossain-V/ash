#include <stdexcept>
#include <vector>
#include <string>
#include <exception>

#include "math.h"
#include "var.h"

namespace math {

void math_handler(std::vector<std::string>& line) {

  if (line.size() < 4)
    throw std::runtime_error("incorrect size");

  if (line[1] == "cond")
    return cond_handler(line);

  throw std::runtime_error("unimplemented");

  return;
}

void cond_handler(std::vector<std::string>& line) {
  throw std::runtime_error("cond unimplemented");

  return;
}


}
