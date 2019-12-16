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

/*
 * Function:  main
 * --------------------
 * prints out gush shell environment
 * gets current director using getcwd
 * uses fgets to get input from the user
 * if it finds a >, <, ; or | in the string, calls the appropriate function
 * otherwise calls, runprocress, entering in info about number of arguments, obtained from funtions in parse.c
 * returns: 0
 */
int main(int argc, char const *argv[]) {
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
        runprocess(args, arglen);
      }
      }
    }else if(strstr(string, ">") != NULL || strstr(string, "<") != NULL){
      handleredir(string);
    }else {
      char ** args = parse_args(string, " ");
      size_t arglen = arg_len(args);
      runprocess(args, arglen);
    }
  }
  return 0;
}
