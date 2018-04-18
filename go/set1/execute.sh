#!/bin/sh

if [ $# -gt 0 ]
then
    while [ $# -gt 0 ]
    do
        echo "Executing $1"
        go run $1
        echo
        shift
    done
else
    # Execute all files
    for i in *.go
    do
        echo "Executing $i"
        go run $i
        echo
    done
fi

