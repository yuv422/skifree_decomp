#!/bin/sh
objdump -M intel -d c.obj > c.out
objdump -M intel -d asm.obj > asm.out
~/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.3739.54/bin/clion64.exe diff asm.out c.out

