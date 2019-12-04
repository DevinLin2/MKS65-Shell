#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

int main(int argc, char const *argv[]) {
  char string[128];
  fgets(string, 128, stdin);
  printf("entered: %s\n", string);
  char ** args = parse_args(string);
  for (size_t i = 0; args[i] != NULL; i++) {
    printf("%s ", args[i]);
  }
  printf("\n");
  return 0;
}
