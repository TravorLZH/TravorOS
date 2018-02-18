#!/bin/sh

yasm -fbin diskdemo.asm -o diskdemo.bin
qemu-system-i386 -fda diskdemo.bin -hda disk.img

