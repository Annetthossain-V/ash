
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "console.h"
#include "helper.h"
#include "core.h"

void user_prompt() {

  char* prompt = (char*) malloc(1024);
  getcwd(prompt, 1000);


  strcat(prompt, "\n");
  char* exit_code = to_string(exitcode);
  strcat(prompt, exit_code);
  strcat(prompt, "$ ");

  printf("%s", prompt);
  free(prompt);
  free(exit_code);
  return;
}

char* readline() {

  // not gonna implement the full
  char* thing = malloc(1024);
  fgets(thing, 512, stdin);
  thing[strlen(thing) - 1] = '\0';

  return thing;
}
