#include <stdexcept>
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

void create_env(const std::string name, const std::string value) {
  std::string formatted_str;
  formatted_str.append(name);
  formatted_str.append("=");
  formatted_str.append(value);

  if (putenv(formatted_str.data()) != 0)
    throw std::runtime_error("unable to create environment variable");

  return;
}

}
