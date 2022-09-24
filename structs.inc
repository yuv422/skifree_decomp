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

extern _malloc: proc
extern _free: proc
extern _strlen: proc
extern _strncpy: proc
extern _strcat: proc
extern _memcpy: proc
extern _rand: proc
extern _srand: proc
extern _atol:proc

