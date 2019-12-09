#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "parse.h"
#include "bashcommands.h"
#include "redirect.h"

int main(int argc, char const *argv[]) {
  int exit = 0;
  while(!exit){
    char string[128];
    char * curdir;
    curdir = getcwd(curdir, 64);
    printf("gush:~%s$ ", curdir);
    fgets(string, 128, stdin);
    strtok(string, "\n");
    char ** args = parse_args(string);
    size_t arglen = arg_len(args);
    int needsredirect = hasredirect(args);
    if(arglen > 0 && strcmp(args[0], "exit") == 0){
      return 0;
    }
    runprocess(args, arglen, needsredirect);
  }
  return 0;
}
