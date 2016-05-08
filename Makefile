#Variables used for creating "rshell" executable
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = RShell.o CompositeCommand.o LeafCommand.o Ors.o Ands.o SemiColon.o Executable.o Exit.o

#type "make all" to create all .o files and "rshell" executable
all: rshell

#Create "rshell" executable
rshell:
	#Compile into .o files
	#Compile into executable called "rshell"
	#Create directory called "bin" and move all .o files and "rshell" executable to "bin"
	$(COMPILE) $(FLAGS) -c src/RShell.cpp &&\
	$(COMPILE) $(FLAGS) -c src/CompositeCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c src/LeafCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Ors.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Ands.cpp &&\
	$(COMPILE) $(FLAGS) -c src/SemiColon.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Executable.cpp &&\
	$(COMPILE) $(FLAGS) -c src/Exit.cpp &&\
	$(COMPILE) $(FLAGS) -o rshell src/main.cpp $(OBJS) &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin && mv $(OBJS) bin 
	
#type "make clean" to delete all .o files, the "rshell" executable, and the "bin" directory	
clean: 
	rm -rf *~ bin