#Variables used for creating "rshell" executable
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = RShell.o CompositeCommand.o LeafCommand.o Ors.o Ands.o SemiColon.o Executable.o Exit.o Test.o
#type "make all" to create all .o files and "rshell" executable
all: rshell

#Create "rshell" executable
rshell:
	#Compile into .o files
	#Compile into executable called "rshell"
	#Create directory called "bin" and move all .o files and "rshell" executable to "bin"
	$(COMPILE) $(FLAGS) -c -I header RShell.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header CompositeCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header LeafCommand.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header Ors.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header Ands.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header SemiColon.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header Executable.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header Exit.cpp &&\
	$(COMPILE) $(FLAGS) -c -I header Test.cpp &&\
	$(COMPILE) $(FLAGS) -I header -o rshell main.cpp $(OBJS) &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin && mv $(OBJS) bin 
	
#type "make clean" to delete all .o files, the "rshell" executable, and the "bin" directory	
clean: 
	rm -rf *~ bin ; find . -type f -name '*.o' -exec rm {} +
