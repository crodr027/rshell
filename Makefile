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
	$(COMPILE) $(FLAGS) -c -I header src/RShell.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/CompositeCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/LeafCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/Ors.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/Ands.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/SemiColon.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/Executable.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header src/Exit.cpp &&\
	$(COMPILE) $(FLAGS) -I header -o rshell src/main.cpp $(OBJS) &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin && mv $(OBJS) bin 
	
#type "make clean" to delete all .o files, the "rshell" executable, and the "bin" directory	
clean: 
	rm -rf *~ bin ; find . -type f -name '*.o' -exec rm {} +