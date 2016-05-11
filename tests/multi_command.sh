#!/bin/sh

STRING="ls -l -t -r;cat ../src/Ands.h||echo failed&&echo succeeded\n \
    cat Ors.h||echo failed||echo shouldn'tprint&&cat ../src/Ors.h\n \
    mkdir trials||ls -a&&echo `pwd`;exit"

echo -e $STRING | ../bin/rshell
