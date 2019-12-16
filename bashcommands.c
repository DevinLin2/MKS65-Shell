#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

/*
 * Function:  runprocess
 * --------------------
 * Does all the forking and execvp stuff.
 * A fork is automatically made and a check is made to see whether it is the parent or child running the function.
 * If parent, wait.
 * If child, checks for special cases where nothing chnges like cd and then does execvp.
 *
 * args: the parsed command line arguments .
 * arg_len: the number of rows in args
 *
 * returns: void function. 
 */
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
