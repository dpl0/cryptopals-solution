#!/bin/bash

# Color reference
# BLACK="\e[0;30m"
# RED="\e[0;31m"
# GREEN="\e[0;32m"
# YELLOW="\e[0;33m"
# BLUE="\e[0;34m"
# PURPLE="\e[0;35m"
# CYAN="\e[0;36m"
# WHITE="\e[0;37m"
# DEFAULT="\e[0m"

function solve() {
    ./$1
    if [ $? -eq 0 ]
    then
        echo -e "\e[0;32m$1 succeed\e[0m"
    else
        echo -e "\e[0;31m$1 failed\e[0m"
    fi
}

function solveall() {
    echo
    echo -e "\e[0;33mAttempting to solve\e[0m"
    for i in `find * -type f -executable`
    do
        # Avoid cycle executing this file
        [ $i = "solve.sh" ] && continue

        solve $i
    done
}

solveall

