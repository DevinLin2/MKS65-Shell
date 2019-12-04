#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parse.h"
#include <string.h>

int main(int argc, char const *argv[]) {
  char string[128];
  fgets(string, 128, stdin);
  strtok(string, "\n");
  printf("entered: %s\n", string);
  char ** args = parse_args(string);
  for (size_t i = 0; args[i] != NULL; i++) {
    printf("%s ", args[i]);
  }
  printf("\n");
  execvp(args[0], args);
  return 0;
}
