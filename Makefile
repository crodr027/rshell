CC=g++
CC_FLAGS=-W -Wall -Werror -pedantic -ansi
EXEC1=bin/rshell
EXEC2=bin/all
SOURCES=$(wildcard src/*.cpp)
#INCLUDES=$(wildcard *.h)
#TEMP:=$(subst ./, bin/, $(SOURCES))
OBJECTS:=$(patsubst src/%.cpp, bin/%.o, $(SOURCES))
#OBJECTS=$(wildcard *.o)

bin/all: bin/rshell
bin/rshell: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC1)
	$(CC) $(OBJECTS) -o $(EXEC2)

$(OBJECTS): | bin

bin:
	@mkdir -p $@

bin/%.o: src/%.cpp src/*.h
	@$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC1) $(EXEC2) $(OBJECTS)
