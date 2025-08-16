#include <string>
#include <cstdlib>


#include "io.h"

namespace io {

std::string envinfo(const std::string name) {
  const char* env = std::getenv(name.c_str());
  if (env == NULL) 
    return "";
  return env;
}

}
