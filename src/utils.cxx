
#include "unistd.h"

#include "utils.h"

namespace utils {

bool cd(std::string& path) {
  if (chdir(path.c_str()) != 0)
    return false;
  return true;
}

}
