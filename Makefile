#Variables used for creating "rshell" executable
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = RShell.o CompositeCommand.o LeafCommand.o Ors.o Ands.o SemiColon.o Executable.o Exit.o

#type "make all" to create all .o files and "rshell" executable
all: rshell

#Create "rshell" executable
rshell:
#Compile into .o files
	$(COMPILE) $(FLAGS) -c src/RShell.h src/RShell.cpp &&\
	$(COMPILE) $(FLAGS) -c src/CompositeCommand.h src/CompositeCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c src/LeafCommand.h src/LeafCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Ors.h src/Ors.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Ands.h src/Ands.cpp &&\
	$(COMPILE) $(FLAGS) -c src/SemiColon.h src/SemiColon.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Executable.h src/Executable.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Exit.h src/Exit.cpp &&\
	
#Compile into executable called "rshell"
	$(COMPILE) $(FLAGS) -o rshell src/main.cpp $(OBJS) &&\
	
#Create directory called "bin" and move all .o files and "rshell" executable to "bin"
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin && mv $(OBJS) bin 
	
#type "make clean" to delete all .o files, the "rshell" executable, and the "bin" directory	
clean: 
	rm -rf *~ bin