#!/bin/sh
#objdump -M intel -d c.obj > c.out
#objdump -M intel -d asm.obj > asm.out
/c/Program\ Files/Microsoft\ Visual\ Studio/2022/Community/VC/Tools/MSVC/14.32.31326/bin/Hostx64/x64/dumpbin.exe //disasm c.obj > c.out
/c/Program\ Files/Microsoft\ Visual\ Studio/2022/Community/VC/Tools/MSVC/14.32.31326/bin/Hostx64/x64/dumpbin.exe //disasm asm.obj > asm.out

~/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.3739.54/bin/clion64.exe diff asm.out c.out

