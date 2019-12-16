#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "parse.h"
#include "bashcommands.h"
#include "redirect.h"
#include "semicolon.h"

int main(int argc, char const *argv[]) {
  int exit = 0;
  while(!exit){
    char string[128];
    char ** semicolonString;
    char * curdir;
    curdir = getcwd(curdir, 64);
    printf("gush:~%s$ ", curdir);
    fgets(string, 128, stdin);
    strtok(string, "\n");
     if (strstr(string, ";") != NULL) {
      semicolonString = handleSemicolon(string);
      for (size_t i = 0; semicolonString[i] != NULL; i++) {
      if(strstr(semicolonString[i], ">") != NULL || strstr(semicolonString[i], "<") != NULL){
        handleredir(semicolonString[i]);
      }else{
        char ** args = parse_args(semicolonString[i], " ");
        size_t arglen = arg_len(args);
        if(arglen > 0 && strcmp(args[0], "exit") == 0){
          return 0;
        } else {
        runprocess(args, arglen);
        }
      }
      }
    }else if(strstr(string, ">") != NULL || strstr(string, "<") != NULL){
      handleredir(string);
    }else {
      printf("yeet hey\n");
      char ** args = parse_args(string, " ");
      size_t arglen = arg_len(args);
      if(arglen > 0 && strcmp(args[0], "exit") == 0){
        return 0;
      } else {
      runprocess(args, arglen);
      }
    }
  }
  return 0;
}
