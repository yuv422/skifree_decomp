.386
.model flat
.code

include ..\\structs.inc
include ..\\data_extern.inc
include ..\\c_funcs.inc

extern  _updateGameState: proc
extern @drawWindow@8: proc
extern @formatAndPrintStatusStrings@4: proc
extern @getRandomOffscreenStartingPosition@12: proc
extern @updateActorRectsAfterPlayerMove@8: proc
;extern @updateActorPositionMaybe@16: proc

include asm.inc

end