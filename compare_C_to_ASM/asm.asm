.386
.model flat
.code

include ..\\structs.inc
include ..\\data_extern.inc
include ..\\c_funcs.inc

extern  _updateGameState: proc
extern @drawWindow@8: proc
extern @formatAndPrintStatusStrings@4: proc
extern @FUN_00402220@4: proc


include asm.inc

end