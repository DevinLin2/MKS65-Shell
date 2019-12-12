#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void runprocess(char ** args, size_t arglen){
  int f = fork();
  int * waitstatus;
  int err = 0;
  if (f){
    wait(waitstatus);
  }else if(arglen > 0 && strcmp(args[0], "cd") == 0){
    if(arglen == 1){
      err = chdir(getenv("HOME"));
    }else{
      err = chdir(args[1]);
    }
  }else if(arglen > 1 && strcmp(args[0], "echo") == 0){
    for (size_t i = 1; args[i] != NULL; i++) {
      printf("%s ",args[i]);
    }
    printf("\n");
  }else{
    err = execvp(args[0], args);
  }
  if(err){
    if(errno == 2){
      for (size_t i = 0; args[i] != NULL; i++) {
        printf("%s", args[i]);
      }
      printf(": command not found\n" );
    } else{
      printf("%s\n", strerror(errno));
    }
  }
  for (size_t i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
}
