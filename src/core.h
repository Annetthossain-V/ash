#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <exception>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>


#define SIG_RET   44
#define SIG_ERROR 88
#define SIG_EXIT  64
#define SIG_CONT  16


int shell_core(std::string& line);

namespace core {

extern int exitcode;
extern pid_t new_pid;

extern std::chrono::time_point<std::chrono::high_resolution_clock> start;
extern std::chrono::time_point<std::chrono::high_resolution_clock> stop;

void exec_cmd(char** argv);

template <typename ExceptionType>
void eprintexcept(const ExceptionType& err) {
  std::cerr << "[ASH ERROR EXCP]: " << err.what() << std::endl;
}

template <typename Func, typename... Args>
void invoke_except(Func&& f, Args&&... args) {
  try {
    std::invoke(std::forward<Func>(f), std::forward<Args>(args)...);
  } catch (const std::runtime_error& err) {
    std::cerr << "[Runtime error]";
    eprintexcept(err);
    exitcode = 1;
  } catch (const std::exception& err) {
    eprintexcept(err);
    exitcode = 1;
  } catch (...) {
    std::cerr << "[ASH ERROR EXCP]: ERR 44" << std::endl;
    exitcode = 1;
  }
}

}
