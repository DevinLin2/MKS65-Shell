#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parse.h"
#include <string.h>

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
    for (size_t i = 0; args[i] != NULL; i++) {
      printf("%s ", args[i]);
    }
    printf("\n");
    if(arglen > 0 && strcmp(args[0], "exit") == 0){
      return 0;
    }
    int f = fork();
    int * waitstatus;
    if (f){
        wait(waitstatus);
    }else if(arglen > 0 && strcmp(args[0], "cd") == 0){
      if(arglen == 1){
        chdir(getenv("HOME"));
      }else{
        chdir(args[1]);
      }
    }else{
        execvp(args[0], args);
    }
    for (size_t i = 0; args[i] != NULL; i++) {
      free(args[i]);
    }
  }
  return 0;
}
