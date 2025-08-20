#pragma once
#include <string>
#include <vector>

namespace math {

void math_handler(std::vector<std::string>& line);

void cond_handler(std::vector<std::string>& line);

void cond_runner(std::vector<std::string>& line);

void cond_if(std::vector<std::string>& line);
void cond_while(std::vector<std::string>& line);

}
