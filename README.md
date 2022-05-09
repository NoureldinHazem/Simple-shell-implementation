# Simple-shell-implementation
It is required to implement a Unix shell program.</br> Your shell must support the following:
1. The internal shell command "exit" which terminates the shell</br>
Concepts: shell commands, exiting the shell.</br>
System calls: exit()
2. A command with no arguments</br>
Example: ls …etc</br>
Details: Your shell must block until the command completes and, if the return
code is abnormal, print out a message to that effect.</br>
Concepts: Forking a child process, waiting for it to complete and synchronous
execution.</br>
System calls: fork() , execvp() , exit() , wait()
3. A command with arguments
Example: ls –l, cp source destination, rm filename.</br>
Details: Argument 0 is the name of the command.</br>
Concepts: Command-line parameters
4. A command, with or without arguments, executed in the background using &.</br>
Example: firefox &</br>
Details: In this case, your shell must execute the command and return
immediately, not blocking until the command finishes.</br>
Concepts: Background execution, signals, signal handlers, processes and
asynchronous execution.</br></br>
This was assignment 1 in OS course.
