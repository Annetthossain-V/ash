
#include <string>
#include <cstdlib>
#include <cstring>

#include "helper.h"

namespace helper {

enum key_cmd check_if_internel(std::string& cmd) {

  if (cmd == "cd")
    return key_cmd::cd_key;
  else if (cmd == "let")
    return key_cmd::let_key;
  else if (cmd == "export")
    return key_cmd::export_key;
  else if (cmd == "import")
    return key_cmd::import_key;
  else if (cmd == "math")
    return key_cmd::math_key;
  else if (cmd == "alias")
    return key_cmd::alias_key;

  return key_cmd::none_key;
}

}
