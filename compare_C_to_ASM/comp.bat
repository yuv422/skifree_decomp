ml /c /coff asm.asm
cl /c /O2 c.c
dumpbin /disasm asm.obj > asm.out
dumpbin /disasm c.obj > c.out