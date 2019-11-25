#!/bin/bash

PROJ_DIR="/home/bc/probs/my_kernel_challs/simple_bof"
KERN_DIR="/home/bc/workspace/kernel/4.19.86"
INIT_DIR="/tmp/initramfs"

## Extract default image
if [ $1 ] && [ "$1" == "default" ]; then
    echo "[debug.sh] Update to default image"
    $PROJ_DIR/scripts/unpack_initrd.sh      \
        $PROJ_DIR/vm/default/initramfs.cpio \
        $INIT_DIR
else
    echo "[debug.sh] Using debug image"
    $PROJ_DIR/scripts/unpack_initrd.sh      \
        $PROJ_DIR/vm/debug/initramfs.cpio   \
        $INIT_DIR
fi

## Update exploit
cd $PROJ_DIR/exploit
./build.sh
cp ./exploit.elf32 $INIT_DIR/exploit
cd $PROJ_DIR

## Pack initrd
$PROJ_DIR/scripts/pack_initrd.sh        \
    $INIT_DIR                           \
    $PROJ_DIR/vm/debug/initramfs.cpio

## spawn
cd vm/debug
./run.sh