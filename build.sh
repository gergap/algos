#!/bin/bash

BASEDIR=$PWD
BLDDIR=$PWD/bld
DISTDIR=$PWD
BUILD_TYPE=Debug
#BUILD_TYPE=RelWithDebInfo
#BUILD_TYPE=MinSizeRel

function usage {
    echo "Usage: ./build.sh [-m32] [clean]"
    exit 1
}

# process commandline arguments
while getopts "m:c" opt; do
    case $opt in
        m)
            if [ "$OPTARG" == "32" ]; then
                # build 32bit exeutable on 64bit systems
                BLDDIR="${BLDDIR}32"
                DISTDIR="${DISTDIR}32"
                export CFLAGS="-m32"
            else
                usage
            fi
            ;;
        *)
            usage
            ;;
    esac
done

# shift out arguments processed by getopt
shift $((OPTIND-1))

if [ $# -gt 0 ] && [ "$1" == "clean" ]; then
    rm -rf $BLDDIR
fi

mkdir $BLDDIR
cd $BLDDIR
cmake -DCMAKE_INSTALL_PREFIX=$DISTDIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
make
make test
make install

