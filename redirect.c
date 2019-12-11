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
  int f = fork();
  int * waitstatus;
  if(f){
    printf("hi im the parent\n");
    wait(waitstatus);
  }else{
    printf("string is %s\n", string);
    char ** args = parse_args(string, ">");
    size_t arglen = arg_len(args);
    if(arglen >= 1){
      char ** leftside = parse_args(args[0], " ");
      size_t leftlen = arg_len(leftside);
      int writeto = open(args[1], O_WRONLY | O_CREAT, 0644);
      dup2(writeto,STDOUT_FILENO);
      int err = execvp(leftside[0], leftside);
      if(err){
          printf("error:  %s\n", strerror(errno));
      }
    } else{
      printf("Redirection error\n");
    }
  }
}
