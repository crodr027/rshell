#RSHELL
___
####Licensing Information: Read LICENSE
___
####Authors:
Haripriya Vasireddy, Carolina Rodriguez
___
**RSHELL** is a command shell written in C++ programming language. It handles input and output redirection with '<', '>' and '>>' and piping with '|'. It executes commands in the PATH of underlying bash and builtin commands 'exit', 'test and '[]'. The test command and its symbolic version '[]' can be executed with three flags namely, -e, -f and -d, which check if the file/directory exists, is a file and is a directory respectively. Features execution of single commands and multiple commands separated by ';'  '&&' or '||'. Allows grouping of commands by use of parentheses which takes precedence. The rshell prompt is displayed with login and hostname if available.
___
**Execution:** In rshell directory, run $make all or $make

It creates a bin directory with an executable. Run $bin/rshell
Examples :
$cat < src/Ands.cpp
$ls -a > out.txt
$ls -ltr >> out.txt
$cat < Ands.cpp | tr A-Z a-z | tee newFile1.txt | tr a-z A-Z > newFile2.txt
$test -e src/Ands.cpp
$test -f src/Ands.cpp
$[ -d tests ]
$[ -f src/Ands.cpp ]
$(echo A || echo B) || (echo C || echo D)
$exit     
$ls -l -t -r;echo rshell&&mkdir bin||exit

- Command followed by ';' is always executed.
- Command followed by '&&' is executed only if the previous command succeeded.
- Command followed by '||' is executed only if the previous command failed.
- Commands grouped by parentheses take precedence

___
**Files:**  
Makefile, LICENSE, README.md
######/src:
RShell.cpp, LeafCommand.cpp, CompositeCommand.cpp, SemiColon.cpp, Ands.cpp, Ors.cpp, Executable.cpp, Exit.cpp, Test.cpp, PipeExecutable.cpp, Pipe.cpp, PipeCommand.cpp, ORedirect.cpp, OILeafCommands.cpp, OExecutable.cpp, OARedirect.cpp, IRedirect.cpp, main.cpp
######/header:  
RShell.h, Command.h, LeafCommand.h, CompositeCommand.h, Connector.h,  SemiColon.h, Ands.h, Ors.h, CmdExecutor.h, Executable.h, Builtin.h, Exit.h, Test.h, Pipe.h, PipeExecutable.h, PipeCommand.h, ORedirect.h, OILeafCommands.h, OExecutable.h, OARedirect.h, IRedirect.h 
######/tests:
test_test.sh, precedence_test.sh, single_command.sh, multi_command.sh, commented_command.sh, exit.sh
___

**Tests:**
The tests folder contains bash scripts to be run from the "tests folder". Examples:
Change to tests directory and run the following test scripts:

$./test_test.sh  $./precedence_test.sh  $./commented_command.sh  $./exit.sh
___
**Details:**
fork() function call used to spawn a child process. execvp() function call executes the commands in rshell. waitpid() function is used in the parent process to wait for the child process to complete. Builtin commands test, exit and "[]" are implemented with extensibility for newer builtin commands. Input and output redirection as well as piping of appropriate commands is supported.
___
**Known Bugs/Errors:**
The code does not support single connector operators such as '|' and '&'. Entering $ echo hello#comment will only echo everything before the '#'. The program also does not support any commands not already supported by the execvp function which is described in detail here: http://linux.die.net/man/3/execvp .


