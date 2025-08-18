#include <any>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <cstring>

#include "io.h"
#include "var.h"
#include "core.h"

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

  char* cptr = (char*) std::malloc(formatted_str.size() + 6);
  std::strcpy(cptr, formatted_str.c_str());

  if (putenv(cptr) != 0)
    throw std::runtime_error("unable to create environment variable");

  // cptr must not be freed
  // because putenv makes it a part
  // of the current system
  return;
}

void import_handler(std::vector<std::string>& line) {
  // import $local_var env_var

  if (line.size() != 3)
    throw std::runtime_error("invalid args");

  std::string local_var_name = line[1];
  if (local_var_name[0] != '$')
    throw std::runtime_error("invalid local variable");

  std::string value = envinfo(line[2]);
  
  variable::var data(variable::var_mode::str, std::any(value));
  variable::setvar(data, local_var_name);
  return;
}

void export_handler(std::vector<std::string> &line) {
  // export $local_var env_var

  if (line.size() != 3)
    throw std::runtime_error("invalid args");
  
  std::string env_name = line[2];
  std::string value = line[1];

  core::invoke_except(create_env, env_name, value);
  return;
}

}
