
#include <string>
#include <cstdlib>
#include <cstring>

extern "C" char* to_string(int number) {
  
  std::string str = std::to_string(number);
  char* c_str = (char*) std::malloc(str.length() + 2);
  std::strcpy(c_str, str.c_str());
  
  return c_str;
}
