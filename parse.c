#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function:  trim_string
 * --------------------
 * Gets rid of empty space.
 *
 * str: the string to be trimmed.
 *
 * returns: the new trimmed string.
 */
char * trim_string(char * str){
  while(*str == ' '){
    str++;
  }
  char * end = str + strlen(str) -1;
  while(end > str && *end == ' '){
    end--;
  }
  *(end + 1) = '\0';
  return str;
}

/*
 * Function:  parse_args
 * --------------------
 * Loops through the command line argument and parses based on the given delimiter.
 *
 * line: the command line argument
 * delimiter: what to parse the string by
 *
 * returns: a 2-D array of the separated command line arguments.
 */
char ** parse_args(char * line , char * delimiter){
  char ** args = calloc(32, sizeof(char *));
  size_t argno = 0;
  char * token = "";
  //printf("delim> is %s\n", delimiter);
  while(line != NULL && argno < 32){
    args[argno] = calloc(8,32);
    token = trim_string(strsep(&line, delimiter));
    strncpy(args[argno], token, 32);
    argno++;
  }

  return args;
}

/*
 * Function: arg_len
 * --------------------
 * Calculates the number of rows of the given argument.
 *
 * args: given 2-D array
 *
 * returns:a size_t number denoting the number of rows in args.
 */
size_t arg_len(char ** args){
  size_t len = 0;
  for (size_t i = 0; args[i] != NULL; i++) {
    len++;
  }
  return len;
}
