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
    unk_0x1a word ?
    unk_0x1c word ?
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
    sprite dword ?
    spriteIdx1 dword ?
    unkActorPtr dword ?
    spriteIdx2 dword ?
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

extern _malloc: proc
extern _free: proc
extern _strlen: proc
extern _strncpy: proc
extern _strcat: proc
extern _memcpy: proc
extern _rand: proc
extern _srand: proc
extern _atol:proc

