#!/bin/sh

STRING="ls -IR /;echo listing||#exit\n \
    echo rshell&&ls#-IR /;cat Ors.h\n \
    mkdir #comments&&echo ending\n#\nexit#;cat Or"

echo -e $STRING | ../bin/rshell
