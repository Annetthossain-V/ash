#pragma once
#include <string>


enum key_cmd {
  none_key,
  cd_key,
  let_key,
  export_key,
  import_key,
  math_key,
  alias_key,
  print_key,
};

namespace helper {


enum key_cmd check_if_internel(std::string& cmd);

}
