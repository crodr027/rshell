a.out : main.o RShell.o CompositeCommand.o LeafCommand.o Ors.o Ands.o SemiColon.o Executable.o Exit.o
	g++ main.o RShell.o CompositeCommand.o LeafCommand.o Ors.o Ands.o SemiColon.o Executable.o Exit.o -W -Wall -Werror -pedantic -ansi -o a.out
main.o : main.cpp Command.h RShell.h CompositeCommand.h Connector.h LeafCommand.h SemiColon.h Ors.h Ands.h CmdExecutor.h
	g++ -W -Wall -Werror -pedantic -ansi -c main.cpp 
RShell.o : RShell.cpp RShell.h Command.h CompositeCommand.h Connector.h LeafCommand.h SemiColon.h Ors.h Ands.h Exit.h
	g++ -W -Wall -Werror -pedantic -ansi -c RShell.cpp
CompositeCommand.o : CompositeCommand.cpp CompositeCommand.h Command.h
	g++ -W -Wall -Werror -pedantic -ansi -c CompositeCommand.cpp
LeafCommand.o : LeafCommand.cpp LeafCommand.h Command.h CmdExecutor.h Exit.h
	g++ -W -Wall -Werror -pedantic -ansi -c LeafCommand.cpp
Ors.o : Ors.cpp Ors.h Connector.h Command.h
	g++ -W -Wall -Werror -pedantic -ansi -c Ors.cpp
Ands.o : Ands.cpp Ands.h Connector.h Command.h
	g++ -W -Wall -Werror -pedantic -ansi -c Ands.cpp
SemiColon.o : SemiColon.cpp SemiColon.h Connector.h Command.h
	g++ -W -Wall -Werror -pedantic -ansi -c SemiColon.cpp
Executable.o : Executable.cpp Executable.h LeafCommand.h
	g++ -W -Wall -Werror -pedantic -ansi -c Executable.cpp
Exit.o : Exit.cpp Exit.h BuiltIn.h Command.h
	g++ -W -Wall -Werror -pedantic -ansi -c Exit.cpp