.386
.model flat
.code

include ..\\structs.inc
include ..\\data_extern.inc
include ..\\c_funcs.inc

extern  _updateGameState: proc
extern @drawWindow@8: proc
extern @formatAndPrintStatusStrings@4: proc
;extern @getRandomOffscreenStartingPosition@12: proc
;extern @updateActorRectsAfterPlayerMove@8: proc
;extern @updateActorPositionMaybe@16: proc
extern @random@4: proc
;extern _randomActorType1: proc
;extern _areaBasedActorType: proc
;extern _randomActorType3: proc
;extern _randomActorType2: proc

include asm.inc

end