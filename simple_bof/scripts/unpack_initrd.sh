#!/bin/bash

if [ $1 ] && [ $2 ] && [ -f $1 ]; then
    CPIO_PATH=$(realpath $1);
    OUT_PATH=$(realpath $2);
else
    echo "Usage: $0 [cpio file path] [cpio out path]";
    exit
fi

WORKDIR=$OUT_PATH
ORIGDIR=`pwd`

if [ -d $WORKDIR ]; then
    echo "$WORKDIR found. deleting..."
    rm -rf $WORKDIR
fi

mkdir $WORKDIR
if [ $? -ne 0 ]; then
    echo "mkdir $WORKDIR Failed."
    exit 1
fi

cd $WORKDIR

cat $CPIO_PATH | cpio -idmv 2>/dev/null
if [ $? -ne 0 ]; then
    echo "Unpacking failed."
    exit 1
fi

echo "Unpacked path $WORKDIR."
exit 0