#!/bin/sh

install() {
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
}

handleInstall() {
    echo "Updating library... "
    install
    if [ $? -gt 0 ]
    then
        echo
        echo "Error reinstalling the library!"
        exit
    fi
    echo "Done updating library"
}


main() {
    if [ $1 -a $1 = "-i" ]
    then
        handleInstall
        exit
    fi

    handleInstall
    echo

    # Unless there's a direct path as first arg, solve everything
    if [ $# -gt 0 ]
    then
        while [ $# -gt 0 ]
        do
            cd `dirname $1`
            ./execute.sh `basename $1`
            cd -
            shift
        done
    else
        for dir in 'set*/' #Gobbling parameter that takes all directories
        do
            echo "Executing all in $dir"
            cd $dir
            ./execute.sh
            cd -
        done
    fi
}

main $@
