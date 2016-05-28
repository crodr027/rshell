#!/bin/sh

../bin/./rshell << EOF
(echo A && echo B) || (echo C && echo D)
echo A && echo B || echo C && echo D
(echo A &&) echo B (
)echo A || echo B(
echo A && echo B ()
(echo A) && (echo B) || echo (D)
(echo D || echo B) && echo A
(echo D || echo B) || (echo A && echo B)
echo A && echoB) || echo C
echo A && )(echo B
echo A & echo B
echo A && (echo B || echo C) && echo D
exit

EOF
printf "\n"
