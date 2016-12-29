#!/bin/bash

RCol="\e[0m"    # Text Reset
# Regular           Bold                Background
Bla="\e[0;30m";     BBla="\e[1;30m";    On_Bla="\e[40m";
Red="\e[0;31m";     BRed="\e[1;31m";    On_Red="\e[41m";
Gre="\e[0;32m";     BGre="\e[1;32m";    On_Gre="\e[42m";
Yel="\e[0;33m";     BYel="\e[1;33m";    On_Yel="\e[43m";
Blu="\e[0;34m";     BBlu="\e[1;34m";    On_Blu="\e[44m";
Pur="\e[0;35m";     BPur="\e[1;35m";    On_Pur="\e[45m";
Cya="\e[0;36m";     BCya="\e[1;36m";    On_Cya="\e[46m";
Whi="\e[0;37m";     BWhi="\e[1;37m";    On_Whi="\e[47m";

function solve() {
    ./$1
    if [ $? -eq 0 ]
    then
        echo -e "\e[0;32m$1 succeed\e[0m"
    else
        echo -e "\e[0;31m$1 failed\e[0m"
    fi
}

echo
echo -e "\e[0;33mAttempting to solve\e[0m"
for i in `find * -type f -executable`
do
    # Avoid cycle executing this file
    [ $i = "solve.sh" ] && continue

    solve $i
done
