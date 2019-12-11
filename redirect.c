#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parse.h"
#include "bashcommands.h"

void handleredir(char * string){
  char ** args = parse_args(string, "<");
  size_t arglen = arg_len(args);
  if(arglen >= 2){
    char ** args = parse_args(string, " ");
    size_t arglen = arg_len(args);
    int writeto = open(args[2], O_WRONLY | O_CREAT);
    dup2(writeto,1);
    runprocess(args,arglen,false);
  } else{
    printf("Redirection error\n");
  }
}
