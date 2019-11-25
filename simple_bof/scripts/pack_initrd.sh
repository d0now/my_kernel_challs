#!/bin/bash

if [ $1 ] && [ $2 ] && [ -d $1 ]; then
    CPIO_PATH=$(realpath $1);
    OUT_PATH=$(realpath $2);
else
    echo "Usage: $0 [cpio folder path] [cpio result path]";
    exit 1
fi

if [ -d $2 ]; then
    echo "Usage: $0 [cpio folder path] [cpio result path]";
    exit 1
fi

ORIGDIR=`pwd`

cd $CPIO_PATH

exec find . | cpio -H newc -ov -F $OUT_PATH 2>/dev/null
if [ $? -ne 0 ]; then
    echo "Packing failed."
    exit 1
fi

echo "Packed path $OUT_PATH"
exit 0