#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** parse_args( char * line ){
  char ** args = calloc(32, sizeof(char *));
  size_t argno = 0;
  char * token = "";
  while(line != NULL && argno < 32){
    args[argno] = calloc(1,32);
    token = strsep(&line, " ");
    strncpy(args[argno], token, 32);
    argno++;
  }
  return args;
}

size_t arg_len(char ** args){
  size_t len = 0;
  for (size_t i = 0; args[i] != NULL; i++) {
    len++;
  }
  return len;
}
