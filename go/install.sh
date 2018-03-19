#!/bin/sh

# Copy the mcccrypt library to your GOPATH, and install it.
# mcccrypt stands for matasano crypto challenge crypt.
REPOPREFIX="/home/dpl/dev/cryptopals-solution/go"
PREFIX="github.com/dpl0"
LIBPATH="${GOPATH}/src/${PREFIX}/"

if test $GOPATH = ""
then
    echo "GOPATH not set"
    exit
fi

if [ ! -d $LIBPATH ]
then
    mkdir -p $LIBPATH
fi

cp -r $REPOPREFIX/mcclib $LIBPATH
go install ${PREFIX}/mcclib
