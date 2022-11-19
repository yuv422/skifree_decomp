tagRECT struct
left dword ?
top dword ?
right dword ?
bottom dword ?
tagRECT ends

Sound struct
soundResource dword ? ; HGLOBAL
soundData dword ?     ; LPVOID
Sound ends

PermObject struct
    actor dword ?
    spritePtr dword ?
    spriteIdx word ?
    padding word ?
    actorTypeMaybe dword ?
    actorFrameNo dword ?
    maybeX word ?
    maybeY word ?
    unk_0x18 word ?
    xVelocity word ?
    yVelocity word ?
    unk_0x1e word ?
    unk_0x20 dword ?
PermObject ends

PermObjectList struct
    startingObject dword ?
    nextObject dword ?
    currentObj dword ?
PermObjectList ends

Actor struct
    next dword ?
    linkedActor dword ?
    actorPtr dword ?
    permObject dword ?
    spriteIdx2 word ?
    padding word ?
    spritePtr dword ?
    typeMaybe dword ?
    frameNo dword ?
    someRect tagRECT <>
    rect tagRECT <>
    xPosMaybe word ?
    yPosMaybe word ?
    isInAir word ?
    HorizontalVelMaybe word ?
    verticalVelocityMaybe word ?
    inAirCounter word ?
    flags dword ?
Actor ends

ActorVelStruct struct
    unk_0 word ?
    unk_2 word ?
    unk_4 word ?
    unk_6 word ?
    xRelated word ?
    unk_a word ?
    frameNo dword ?
ActorVelStruct ends

extern _malloc: proc
extern _free: proc
extern _strlen: proc
extern _strncpy: proc
extern _strcat: proc
extern _memcpy: proc
extern _rand: proc
extern _srand: proc
extern _atol:proc

