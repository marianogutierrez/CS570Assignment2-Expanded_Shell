# Basic Shell Program
This C++ program was designed together with another student. My work consisted of mainly creating the Shell file that serve as the main driver of the program. The program reads in character input via the command line, tokenizing it, then parsing it and executing the commands inputted. The commands are standard shell comamnds like "cd" and "ls", but the user is not limited to just simple commands thanks to the fork() and execvp() system calls. There are various rules to follow. For example the "&" is not supported, therfore it must be filtered. The source code has plenty of comments to really dig dip into what we did. 

## Running and using this program: 
Via the built in make command in the command line
typing "make mush" complies the program. Then one can type in command line operations like "cd" , "ls" , and more via the various system calls used e.g. execvp. 