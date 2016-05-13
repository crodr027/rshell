#!/bin/sh
INPUT_ARRAY=( "ls -IR /&&echo listing;exit" \
    "echo rshell&&echo `pwd`&&exit||ls#-IR /;cat Ors.h" \
    "mkdir comments&&echo ending;cat Ands.h||exit" "exit")
NUM_ELEMENTS=${#INPUT_ARRAY[@]}

for((i=0;i<NUM_ELEMENTS;i++))
do
    let j=$((i+1))
    echo -e "\n${j}. Executing : ${INPUT_ARRAY[${i}]}\n"
    echo ${INPUT_ARRAY[${i}]} | ../bin/rshell
done
