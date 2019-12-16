# MKS65-Shell
GUSH: Grotesquely Underdeveloped Shell

by Qiong Zhou Huang and Devin Lin

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >, <!
  Switch between directories using cd!
  Exits when you want it to!
  Let's you pipe!


Attempted:
	Could not get multiple redirects to work (i.e tr a-z A-Z < hi > die)
  Multiple pipes don't work

Bugs:
	Running the shell using a test_functions file might sometimes print the directory more than once
	
Files & Function Headers:
main.c

 ** Function:  main
 * prints out gush shell environment
 * gets current director using getcwd
 * uses fgets to get input from the user
 * if it finds a >, <, ; or | in the string, calls the appropriate function
 * otherwise calls, runprocress, entering in info about number of arguments, obtained from funtions in parse.c
 * returns: 0

 
 bashcommands.c
 ** Function:  runprocess
 * Does all the forking and execvp stuff.
 * A fork is automatically made and a check is made to see whether it is the parent or child running the function.
 * If parent, wait.
 * If child, checks for special cases where nothing chnges like cd and then does execvp.
 * args: the parsed command line arguments .
 * arg_len: the number of rows in args
 * returns: void function. 

 
 pipe.c:
 ** Function:  handlePipe
 * This function takes care of pipes by using popen.
 * The input is parsed on the pipe and separated into two functions.
 * In is ran through popen read and out is ran through popen write.
 * string: the command line argument.
 * returns: Void function prints out the result of the command line argument.

 
 semicolon.c: 

 ** Function:  handleSemicolon
 * Parse string on semicolons
 * string: command line argument given
 * returns: a 2-D parsed on semicolons array
 
 parse.c:
 ** Function:  trim_string
 * Gets rid of empty space.
 * str: the string to be trimmed.
 * returns: the new trimmed string.

 ** Function:  parse_args
 * Loops through the command line argument and parses based on the given delimiter.
 * line: the command line argument
 * delimiter: what to parse the string by
 * returns: a 2-D array of the separated command line arguments.

 ** Function: arg_len
 * Calculates the number of rows of the given argument.
 * args: given 2-D array
 * returns:a size_t number denoting the number of rows in args.
 
 redir.c
 ** Function:  handleredir
 * checks to see if there is a >
 * if there is a > redirect, open the file on the right of the >,
 * and then use dup2 to make it so that when the function on the left is run using
 * execvp, stdout writes that file
 * otherwise, if there is a <, opens the file on the right and sets it contents to stdin
 * when the function on the command on the left is run, it uses info from that file
 * returns: void function.
