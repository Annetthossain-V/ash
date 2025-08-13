#pragma once


namespace core {

#define CTRL_C      3
#define TAB         9
#define BACK_SPACE  127

void set_buffer(bool enable);
int getch();

}
