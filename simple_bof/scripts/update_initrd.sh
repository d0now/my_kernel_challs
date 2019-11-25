#!/bin/bash

PROJ_DIR="/home/bc/probs/my_kernel_challs/simple_bof"
INIT_DIR="/tmp/initramfs"

if [ $1 ] && [ $2 ] && [ $3 ] && [ -f $1 ] && [ -f $2 ]; then
    CPIO_PATH=$(realpath $1);
    SRC_PATH=$(realpath $2);
    DST_PATH=$3;
else
    echo "Usage: $0 [cpio file path] [insertion file path] [insertion dst]";
    exit
fi

$PROJ_DIR/scripts/unpack_initrd.sh $CPIO_PATH $INIT_DIR
if [ $? -ne 0 ]; then
    echo "Unpacking failed."
    exit 1
fi

cp $SRC_PATH $INIT_DIR/$DST_PATH
if [ $? -ne 0 ]; then
    echo "Copy failed."
    exit 1
fi

$PROJ_DIR/scripts/pack_initrd.sh $INIT_DIR $CPIO_PATH
if [ $? -ne 0 ]; then
    echo "Packing failed."
    exit 1
fi

echo "Done."
exit 0