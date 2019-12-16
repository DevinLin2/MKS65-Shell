#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "parse.h"
#include "bashcommands.h"

void handlePipe(char * string) {
  char ** parsedString = parse_args(string, "|");
  // this only works if there is one pipe and will break for multiple
  char * in = parsedString[0]; // first command whos stdout will be used as input
  char * out = parsedString[1]; // takes stdout from in as its stdin
  char line[1000];
  char cmd[20000]; // hard coded couldnt find a way to read input size
  // popen("ls -l", "r");
  // printf("%s\n", "yay");
  FILE *read = popen(in,"r");
  while (fgets(line,1000,read) != NULL) {
    // printf("%ld\n", sizeof(line));
    line[sizeof(line) - 1] = 0;
    // printf("%s\n", line);
    strcat(cmd,line);
  }
  // printf("%s\n", line);
  pclose(read);
  FILE *write = popen(out,"w");
  fprintf(write,"%s",cmd);
  pclose(write);
}
