#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
namespace console {
#endif

extern unsigned int exitcode; 

void prompt();


#ifdef __cplusplus
 } }
#endif

#ifdef __cplusplus
#include <string>
namespace console {

  std::string readline();

}
#endif
