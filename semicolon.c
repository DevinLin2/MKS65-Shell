#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "parse.h"
#include "bashcommands.h"

/*
 * Function:  handleSemicolon
 * --------------------
 * Parse string on semicolons
 *
 * string: command line argument given
 *
 * returns: a 2-D parsed on semicolons array
 */
char ** handleSemicolon(char * string) {
  char ** returnValue = parse_args(string, ";");
  return returnValue;
}
