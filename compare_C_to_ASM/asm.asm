.386
.model flat
.code

include ..\\asm\\structs.inc
include ..\\asm\\data_extern.inc
include ..\\asm\\c_funcs.inc

;extern  _updateGameState: proc
;extern @drawWindow@8: proc
;extern @formatAndPrintStatusStrings@4: proc
;extern @getRandomOffscreenStartingPosition@12: proc
;extern @updateActorRectsAfterPlayerMove@8: proc
;extern @updateActorPositionMaybe@16: proc
extern @random@4: proc
;extern _randomActorType1: proc
;extern _areaBasedActorType: proc
;extern _randomActorType3: proc
;extern _randomActorType2: proc

;extern @updatePlayerActor@4: proc
;extern @updateActorType3_snowboarder@4: proc
;extern @updateActorTypeA_walkingTree@4: proc
;extern @updateActorVelMaybe@8: proc
;extern @updateSsGameMode@12: proc
;extern @updateFsGameMode@12: proc
;extern @updateGsGameMode@12: proc
;extern @FUN_00402e30@20: proc
;extern _resetPlayerFrameNo: proc
;extern @updateEntPackIniKeyValue@12: proc
;extern @permObjectSetSpriteIdx@8: proc

include asm.inc

end