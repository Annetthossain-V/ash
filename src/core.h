#pragma once

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
namespace core {
#endif

#define CTRL_C      3
#define TAB         9
#define BACK_SPACE  127

void set_buffer(bool enable);
int getch();

void core_shell();


#ifdef __cplusplus
  } }
#endif

