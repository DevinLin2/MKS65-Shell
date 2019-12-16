#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "parse.h"
#include "bashcommands.h"

void handleredir(char * string){
  int * waitstatus;
  int f = fork();
  if(f){
    wait(waitstatus);
  }else if(strstr(string, ">") != NULL){
    char ** args = parse_args(string, ">");
    size_t arglen = arg_len(args);
    if(arglen >= 1){
      char ** leftside = parse_args(args[0], " ");
      size_t leftlen = arg_len(leftside);
      int writeto = open(args[1], O_WRONLY | O_CREAT, 0644);
      dup2(writeto,STDOUT_FILENO);
      if(strstr(args[0], "<") != NULL){
        printf("u stupid");
        handleredir(args[0]);
      }else{
        int err = execvp(leftside[0], leftside);
        if(err){
            printf("error:  %s\n", strerror(errno));
        }
      }
    }else{
      printf("Improper use of redirection command\n");
    }
  }else if(strstr(string, "<") != NULL){

      char ** args = parse_args(string, "<");
      size_t arglen = arg_len(args);
      int fd = 0;
      if(arglen > 1){
        fd = open(args[1], O_RDONLY);
        if(fd < 0){
          printf("file error:%s\n", strerror(errno));
        }else{
          dup2(fd, STDIN_FILENO);
          char ** leftside = parse_args(args[0], " ");
          int run = execvp(leftside[0],leftside);
          if(run < 0){
            printf("bad command entered: %s\n", strerror(errno));
          }
        }
      }
      else{
        printf("Improper use of redirection command\n");
      }
    } else{
      printf("Redirection error\n");
    }
  }
