#!/bin/bash

qemu-system-i386                   \
    -m 512M                        \
    -kernel bzImage                \
    -initrd initramfs.cpio         \
    -nographic                     \
    -no-reboot                     \
    -append 'console=ttyS0 log_level=3 oops=panic panic=-1 quiet' \
    -monitor /dev/null             \
    -s