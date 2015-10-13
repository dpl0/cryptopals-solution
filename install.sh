#!/bin/sh

# Copy the mcccrypt library to your GOPATH, and install it.
# mcccrypt stands for matasano crypto challenge crypt.

if test $GOPATH = ""
then
	echo "GOPATH not set"
	exit
fi

export PREFIX="github.com/dplbsd/"
export LIBPATH="${GOPATH}/src/${PREFIX}"

if [ ! -d $LIBPATH ]
then
	mkdir -p $LIBPATH
fi

cp -r ./mcclib $LIBPATH

go install ${PREFIX}/mcclib

