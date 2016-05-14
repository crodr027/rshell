#RSHELL
___
####Licensing Information: Read LICENSE
___
####Authors:
Haripriya Vasireddy, Carolina Rodriguez
___
**RSHELL** is a command shell written in C++ programming language. It executes commands in the PATH of underlying bash and a builtin command 'exit'. Features execution of single commands and multiple commands separated by ';'  '&&' or '||'. The rshell prompt is displayed with login and hostname if available.
___
**Execution:** In rshell directory, run $make all or $make

It creates a bin directory with an executable. Run $bin/rshell

$exit     

$ls -l -t -r;echo rshell&&mkdir bin||exit
- Command followed by ';' is always executed.
- Command followed by '&&' is executed only if the previous command succeeded.
- Command followed by '||' is executed only if the previous command failed.

___
**Files:**  
Makefile, LICENSE, README.md
######/src:
RShell.cpp, LeafCommand.cpp, CompositeCommand.cpp, SemiColon.cpp, Ands.cpp, Ors.cpp, Executable.cpp, Exit.cpp
######/header:  
RShell.h, Command.h, LeafCommand.h, CompositeCommand.h, Connector.h,  SemiColon.h, Ands.h, Ors.h, CmdExecutor.h, Executable.h, Builtin.h, Exit.h 
######/tests:
single_command.sh, multi_command.sh, commented_command.sh, exit.sh
___

**Tests:**
The tests folder contains bash scripts to be run from the tests folder. Examples:

$tests/single_command.sh  $tests/multi_command.sh  $tests/commented_command.sh  $exit.sh
___
**Details:**
fork() function call used to spawn a child process. execvp() function call executes the commans in rshell. waitpid() function is used in the parent process to wait for the child process to complete.
___
**Known Bugs/Errors:**
The code does not support single connector operators such as '|' and '&'. After entering an unrecognized command, $ exit must be entered twice in order to fully exit. Entering $ echo hello#comment will only echo everything before the '#'. The program also does not support any commands not already supported by the execvp function which is described in detail here: http://linux.die.net/man/3/execvp .


