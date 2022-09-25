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

Actor struct
    next dword ?
    sprite dword ?
    spriteIdx1 dword ?
    unkActorPtr dword ?
    spriteIdx2 dword ?
    spritePtr dword ?
    typeMaybe dword ?
    unk_0x1c dword ?
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

