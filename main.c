#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "parse.h"
#include "bashcommands.h"
#include "redirect.h"
#include "semicolon.h"
#include "pipe.h"

int main(int argc, char const *argv[]) {
  int myexit = 0;
  char string[128];
  while(1){
    char ** semicolonString;
    char * curdir;
    curdir = getcwd(curdir, 64);
    printf("gush: %s ", curdir);
    fgets(string, 128, stdin);
    if(strstr(string, "exit") != NULL){
      exit(0);
    }
    strtok(string, "\n");
    if(strstr(string, ">") != NULL){
      handleredir(string);
    } else if (strstr(string, "|") != NULL) {
      handlePipe(string);
    } else if (strstr(string, ";") != NULL) {
      // printf("%d\n", countSemicolon(string));
      semicolonString = handleSemicolon(string);
      for (size_t i = 0; semicolonString[i] != NULL; i++) {
      if(strstr(semicolonString[i], ">") != NULL || strstr(semicolonString[i], "<") != NULL){
        handleredir(semicolonString[i]);
      }else{
        char ** args = parse_args(semicolonString[i], " ");
        size_t arglen = arg_len(args);
        if(arglen > 0 && strcmp(args[0], "exit") == 0){
          exit(0);
        } else {
        runprocess(args, arglen);
        }
      }
      }
    }else if(strstr(string, ">") != NULL || strstr(string, "<") != NULL){
      handleredir(string);
    }else {
      char ** args = parse_args(string, " ");
      size_t arglen = arg_len(args);
      if(arglen > 0 && strcmp(args[0], "exit") == 0){
        exit(0);
      } else {
      runprocess(args, arglen);
      }
    }
  }
  return 0;
}
