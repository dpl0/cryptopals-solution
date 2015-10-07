#!/bin/sh

# Copy the mcccrypt library to your GOPATH, and install it.
# mcccrypt stands for matasano crypto challenge crypt.

if [ $GOPATH == "" ]
then
	echo "Please set the GOPATH variable."
fi

export OBJECTIVE="$GOPATH/src/github.com/dplbsd/"

mkdir -p $OBJECTIVE
cp -r ./mcccrypt $OBJECTIVE

go build
go install
