.386
.MODEL FLAT, SYSCALL
option casemap:none ; Treat labels as case-sensitive
.CONST


PUBLIC C PTR_DeleteObject_0040a000
PTR_DeleteObject_0040a000 byte 0a4h, 0adh, 2 DUP (00h)
PUBLIC C PTR_SelectObject_0040a004
PTR_SelectObject_0040a004 byte 0b4h, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetTextExtentPoint32A_0040a008
PTR_GetTextExtentPoint32A_0040a008 byte 44h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_BitBlt_0040a00c
PTR_BitBlt_0040a00c byte 76h, 0adh, 2 DUP (00h)
PUBLIC C PTR_PatBlt_0040a010
PTR_PatBlt_0040a010 byte 80h, 0adh, 2 DUP (00h)
PUBLIC C PTR_CreateCompatibleBitmap_0040a014
PTR_CreateCompatibleBitmap_0040a014 byte 8ah, 0adh, 2 DUP (00h)
PUBLIC C PTR_TextOutA_0040a018
PTR_TextOutA_0040a018 byte 0c4h, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetStockObject_0040a01c
PTR_GetStockObject_0040a01c byte 0d0h, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetDeviceCaps_0040a020
PTR_GetDeviceCaps_0040a020 byte 0e2h, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetObjectA_0040a024
PTR_GetObjectA_0040a024 byte 18h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_DeleteDC_0040a028
PTR_DeleteDC_0040a028 byte 26h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_CreateBitmap_0040a02c
PTR_CreateBitmap_0040a02c byte 0f2h, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetTextMetricsA_0040a030
PTR_GetTextMetricsA_0040a030 byte 32h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_CreateCompatibleDC_0040a034
PTR_CreateCompatibleDC_0040a034 byte 02h, 0aeh, 2 DUP (00h)
db 4 DUP (00h)
PUBLIC C PTR_FreeResource_0040a03c
PTR_FreeResource_0040a03c byte 62h, 0abh, 2 DUP (00h)
PUBLIC C PTR_lstrlenA_0040a040
PTR_lstrlenA_0040a040 byte 72h, 0abh, 2 DUP (00h)
PUBLIC C PTR_FreeLibrary_0040a044
PTR_FreeLibrary_0040a044 byte 54h, 0abh, 2 DUP (00h)
PUBLIC C PTR_FindResourceA_0040a048
PTR_FindResourceA_0040a048 byte 44h, 0abh, 2 DUP (00h)
PUBLIC C PTR_LoadResource_0040a04c
PTR_LoadResource_0040a04c byte 34h, 0abh, 2 DUP (00h)
PUBLIC C PTR_lstrcmpiA_0040a050
PTR_lstrcmpiA_0040a050 byte 28h, 0abh, 2 DUP (00h)
PUBLIC C PTR_GetPrivateProfileStringA_0040a054
PTR_GetPrivateProfileStringA_0040a054 byte 0ch, 0abh, 2 DUP (00h)
PUBLIC C PTR_WritePrivateProfileStringA_0040a058
PTR_WritePrivateProfileStringA_0040a058 byte 0eeh, 0aah, 2 DUP (00h)
PUBLIC C PTR_LockResource_0040a05c
PTR_LockResource_0040a05c byte 0deh, 0aah, 2 DUP (00h)
PUBLIC C PTR_lstrcpyA_0040a060
PTR_lstrcpyA_0040a060 byte 0c4h, 0aah, 2 DUP (00h)
PUBLIC C PTR_LCMapStringA_0040a064
PTR_LCMapStringA_0040a064 byte 0d0h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_LoadLibraryA_0040a068
PTR_LoadLibraryA_0040a068 byte 0c0h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_LCMapStringW_0040a06c
PTR_LCMapStringW_0040a06c byte 0e0h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_HeapReAlloc_0040a070
PTR_HeapReAlloc_0040a070 byte 0a0h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetProcAddress_0040a074
PTR_GetProcAddress_0040a074 byte 0aeh, 0b0h, 2 DUP (00h)
PUBLIC C PTR_HeapAlloc_0040a078
PTR_HeapAlloc_0040a078 byte 84h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetOEMCP_0040a07c
PTR_GetOEMCP_0040a07c byte 78h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_VirtualAlloc_0040a080
PTR_VirtualAlloc_0040a080 byte 90h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetCPInfo_0040a084
PTR_GetCPInfo_0040a084 byte 62h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetStringTypeW_0040a088
PTR_GetStringTypeW_0040a088 byte 50h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetACP_0040a08c
PTR_GetACP_0040a08c byte 6eh, 0b0h, 2 DUP (00h)
PUBLIC C PTR_MultiByteToWideChar_0040a090
PTR_MultiByteToWideChar_0040a090 byte 28h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_WriteFile_0040a094
PTR_WriteFile_0040a094 byte 1ch, 0b0h, 2 DUP (00h)
PUBLIC C PTR_GetStringTypeA_0040a098
PTR_GetStringTypeA_0040a098 byte 3eh, 0b0h, 2 DUP (00h)
PUBLIC C PTR_HeapFree_0040a09c
PTR_HeapFree_0040a09c byte 04h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_VirtualFree_0040a0a0
PTR_VirtualFree_0040a0a0 byte 0f6h, 0afh, 2 DUP (00h)
PUBLIC C PTR_RtlUnwind_0040a0a4
PTR_RtlUnwind_0040a0a4 byte 10h, 0b0h, 2 DUP (00h)
PUBLIC C PTR_HeapDestroy_0040a0a8
PTR_HeapDestroy_0040a0a8 byte 0dah, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetFileType_0040a0ac
PTR_GetFileType_0040a0ac byte 0cch, 0afh, 2 DUP (00h)
PUBLIC C PTR_HeapCreate_0040a0b0
PTR_HeapCreate_0040a0b0 byte 0e8h, 0afh, 2 DUP (00h)
PUBLIC C PTR_SetHandleCount_0040a0b4
PTR_SetHandleCount_0040a0b4 byte 0aah, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetEnvironmentStringsW_0040a0b8
PTR_GetEnvironmentStringsW_0040a0b8 byte 90h, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetStdHandle_0040a0bc
PTR_GetStdHandle_0040a0bc byte 0bch, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetTickCount_0040a0c0
PTR_GetTickCount_0040a0c0 byte 0b4h, 0aah, 2 DUP (00h)
PUBLIC C PTR_LocalAlloc_0040a0c4
PTR_LocalAlloc_0040a0c4 byte 0d0h, 0aah, 2 DUP (00h)
PUBLIC C PTR_GetModuleHandleA_0040a0c8
PTR_GetModuleHandleA_0040a0c8 byte 80h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_GetStartupInfoA_0040a0cc
PTR_GetStartupInfoA_0040a0cc byte 94h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_WideCharToMultiByte_0040a0d0
PTR_WideCharToMultiByte_0040a0d0 byte 62h, 0afh, 2 DUP (00h)
PUBLIC C PTR_FreeEnvironmentStringsW_0040a0d4
PTR_FreeEnvironmentStringsW_0040a0d4 byte 48h, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetEnvironmentStrings_0040a0d8
PTR_GetEnvironmentStrings_0040a0d8 byte 78h, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetModuleFileNameA_0040a0dc
PTR_GetModuleFileNameA_0040a0dc byte 18h, 0afh, 2 DUP (00h)
PUBLIC C PTR_UnhandledExceptionFilter_0040a0e0
PTR_UnhandledExceptionFilter_0040a0e0 byte 0fch, 0aeh, 2 DUP (00h)
PUBLIC C PTR_FreeEnvironmentStringsA_0040a0e4
PTR_FreeEnvironmentStringsA_0040a0e4 byte 2eh, 0afh, 2 DUP (00h)
PUBLIC C PTR_GetVersion_0040a0e8
PTR_GetVersion_0040a0e8 byte 0b8h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_GetCommandLineA_0040a0ec
PTR_GetCommandLineA_0040a0ec byte 0a6h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_GetCurrentProcess_0040a0f0
PTR_GetCurrentProcess_0040a0f0 byte 0e8h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_TerminateProcess_0040a0f4
PTR_TerminateProcess_0040a0f4 byte 0d4h, 0aeh, 2 DUP (00h)
PUBLIC C PTR_ExitProcess_0040a0f8
PTR_ExitProcess_0040a0f8 byte 0c6h, 0aeh, 2 DUP (00h)
db 4 DUP (00h)
PUBLIC C PTR_CreateWindowExA_0040a100
PTR_CreateWindowExA_0040a100 byte 24h, 0ach, 2 DUP (00h)
PUBLIC C PTR_RegisterClassA_0040a104
PTR_RegisterClassA_0040a104 byte 36h, 0ach, 2 DUP (00h)
PUBLIC C PTR_wsprintfA_0040a108
PTR_wsprintfA_0040a108 byte 8ch, 0abh, 2 DUP (00h)
PUBLIC C PTR_LoadStringA_0040a10c
PTR_LoadStringA_0040a10c byte 0b6h, 0abh, 2 DUP (00h)
PUBLIC C PTR_DestroyWindow_0040a110
PTR_DestroyWindow_0040a110 byte 98h, 0abh, 2 DUP (00h)
PUBLIC C PTR_MessageBoxA_0040a114
PTR_MessageBoxA_0040a114 byte 0a8h, 0abh, 2 DUP (00h)
PUBLIC C PTR_GetMessageA_0040a118
PTR_GetMessageA_0040a118 byte 0ech, 0abh, 2 DUP (00h)
PUBLIC C PTR_TranslateMessage_0040a11c
PTR_TranslateMessage_0040a11c byte 0c4h, 0abh, 2 DUP (00h)
PUBLIC C PTR_DispatchMessageA_0040a120
PTR_DispatchMessageA_0040a120 byte 0d8h, 0abh, 2 DUP (00h)
PUBLIC C PTR_ShowWindow_0040a124
PTR_ShowWindow_0040a124 byte 16h, 0ach, 2 DUP (00h)
PUBLIC C PTR_SetTimer_0040a128
PTR_SetTimer_0040a128 byte 0fah, 0abh, 2 DUP (00h)
PUBLIC C PTR_UpdateWindow_0040a12c
PTR_UpdateWindow_0040a12c byte 06h, 0ach, 2 DUP (00h)
PUBLIC C PTR_FrameRect_0040a130
PTR_FrameRect_0040a130 byte 5eh, 0adh, 2 DUP (00h)
PUBLIC C PTR_LoadCursorA_0040a134
PTR_LoadCursorA_0040a134 byte 48h, 0ach, 2 DUP (00h)
PUBLIC C PTR_FillRect_0040a138
PTR_FillRect_0040a138 byte 36h, 0adh, 2 DUP (00h)
PUBLIC C PTR_MoveWindow_0040a13c
PTR_MoveWindow_0040a13c byte 50h, 0adh, 2 DUP (00h)
PUBLIC C PTR_BeginPaint_0040a140
PTR_BeginPaint_0040a140 byte 42h, 0adh, 2 DUP (00h)
PUBLIC C PTR_LoadBitmapA_0040a144
PTR_LoadBitmapA_0040a144 byte 0ch, 0adh, 2 DUP (00h)
PUBLIC C PTR_EndPaint_0040a148
PTR_EndPaint_0040a148 byte 2ah, 0adh, 2 DUP (00h)
PUBLIC C PTR_GetClientRect_0040a14c
PTR_GetClientRect_0040a14c byte 1ah, 0adh, 2 DUP (00h)
PUBLIC C PTR_DefWindowProcA_0040a150
PTR_DefWindowProcA_0040a150 byte 0dch, 0ach, 2 DUP (00h)
PUBLIC C PTR_PostQuitMessage_0040a154
PTR_PostQuitMessage_0040a154 byte 0fah, 0ach, 2 DUP (00h)
PUBLIC C PTR_SetFocus_0040a158
PTR_SetFocus_0040a158 byte 0eeh, 0ach, 2 DUP (00h)
PUBLIC C PTR_InvalidateRect_0040a15c
PTR_InvalidateRect_0040a15c byte 2 DUP (0ach), 2 DUP (00h)
PUBLIC C PTR_KillTimer_0040a160
PTR_KillTimer_0040a160 byte 0d0h, 0ach, 2 DUP (00h)
PUBLIC C PTR_SetWindowTextA_0040a164
PTR_SetWindowTextA_0040a164 byte 0beh, 0ach, 2 DUP (00h)
PUBLIC C PTR_FindWindowA_0040a168
PTR_FindWindowA_0040a168 byte 8ah, 0ach, 2 DUP (00h)
PUBLIC C PTR_GetDC_0040a16c
PTR_GetDC_0040a16c byte 0a4h, 0ach, 2 DUP (00h)
PUBLIC C PTR_ReleaseDC_0040a170
PTR_ReleaseDC_0040a170 byte 98h, 0ach, 2 DUP (00h)
PUBLIC C PTR_OpenIcon_0040a174
PTR_OpenIcon_0040a174 byte 62h, 0ach, 2 DUP (00h)
PUBLIC C PTR_SetWindowPos_0040a178
PTR_SetWindowPos_0040a178 byte 7ah, 0ach, 2 DUP (00h)
PUBLIC C PTR_IsIconic_0040a17c
PTR_IsIconic_0040a17c byte 6eh, 0ach, 2 DUP (00h)
PUBLIC C PTR_LoadIconA_0040a180
PTR_LoadIconA_0040a180 byte 56h, 0ach, 2 DUP (00h)
db 4 DUP (00h)
PUBLIC C PTR_sndPlaySoundA_0040a188
PTR_sndPlaySoundA_0040a188 byte 66h, 0aeh, 2 DUP (00h)
db 4 DUP (00h)
PUBLIC C s_skiMain
s_skiMain byte 53h, 6bh, 69h, 4dh, 61h, 69h, 6eh, 00h
PUBLIC C s_skiStatus
s_skiStatus byte 53h, 6bh, 69h, 53h, 74h, 61h, 74h, 75h, 73h, 00h
db 2 DUP (00h), 62h, 75h, 2 DUP (74h), 6fh, 6eh, 2 DUP (00h)
PUBLIC C unk_array_0040a1ac
unk_array_0040a1ac byte 01h, 00h, 02h, 00h, 03h, 00h, 04h, 00h, 05h, 00h, 06h, 00h, 07h, 00h, 08h, 00h
db 09h, 00h, 0ah, 00h, 0bh, 00h, 0ch, 00h, 0dh, 00h, 0eh, 00h, 0fh, 00h, 10h, 00h
db 11h, 00h, 12h, 00h, 13h, 00h, 14h, 00h, 15h, 00h, 16h, 00h, 1ch, 00h, 1dh, 00h
db 1eh, 00h, 1fh, 00h, 20h, 00h, 21h, 00h, 22h, 00h, 23h, 00h, 24h, 00h, 25h, 00h
db 26h, 00h, 27h, 00h, 28h, 00h, 29h, 00h, 2ah, 00h, 2bh, 00h, 2ch, 00h, 41h, 00h
db 42h, 00h, 43h, 00h, 44h, 00h, 45h, 00h, 46h, 00h, 47h, 00h, 48h, 00h, 49h, 00h
db 4ah, 00h, 4bh, 00h, 4ch, 00h, 4dh, 00h, 4eh, 00h, 4fh, 00h, 50h, 00h, 51h, 00h
db 53h, 00h, 54h, 00h, 55h, 00h, 54h, 00h, 31h, 00h, 57h, 00h, 58h, 00h, 59h, 00h
PUBLIC C DAT_0040a22c
DAT_0040a22c byte 06h
db 3 DUP (00h), 16h, 3 DUP (00h), 1bh, 3 DUP (00h), 1fh, 3 DUP (00h), 27h, 3 DUP (00h), 2ah, 3 DUP (00h), 2ah, 3 DUP (00h), 2ah, 3 DUP (00h), 2ah
db 3 DUP (00h), 38h, 3 DUP (00h), 3ch, 3 DUP (00h)
PUBLIC C DAT_0040a258
DAT_0040a258 byte 01h
db 3 DUP (00h)
PUBLIC C DAT_0040a25c
DAT_0040a25c byte 04h
db 3 DUP (00h), 02h, 7 DUP (00h), 03h, 3 DUP (00h), 01h, 3 DUP (00h), 07h, 3 DUP (00h), 02h, 7 DUP (00h), 05h, 3 DUP (00h), 04h, 3 DUP (00h), 06h
db 3 DUP (00h), 05h, 3 DUP (00h), 08h, 3 DUP (00h), 03h, 3 DUP (00h), 02h, 3 DUP (00h), 05h, 3 DUP (00h), 06h, 3 DUP (00h), 09h, 3 DUP (00h), 02h
db 3 DUP (00h), 05h, 3 DUP (00h), 0ah, 3 DUP (00h), 03h, 3 DUP (00h), 06h, 3 DUP (00h), 03h, 3 DUP (00h), 06h, 3 DUP (00h), 0eh, 3 DUP (00h), 0fh
db 3 DUP (00h), 10h, 3 DUP (00h), 0dh, 3 DUP (00h), 0dh, 3 DUP (00h), 10h, 3 DUP (00h), 0fh, 3 DUP (00h), 0eh, 3 DUP (00h), 0eh, 3 DUP (00h), 0fh
db 3 DUP (00h), 14h, 3 DUP (00h), 15h, 3 DUP (00h), 14h, 3 DUP (00h), 15h, 3 DUP (00h), 10h, 3 DUP (00h), 0dh, 3 DUP (00h), 0dh, 3 DUP (00h), 10h
db 3 DUP (00h)
PUBLIC C DAT_0040a308
DAT_0040a308 byte 01h
db 00h, 10h, 13 DUP (00h), 01h, 00h, 0ch, 00h, 01h, 00h, 01h, 00h, 2 DUP (0ffh), 2 DUP (00h), 01h, 3 DUP (00h), 01h
db 00h, 06h, 00h, 01h, 00h, 04h, 00h, 2 DUP (0ffh), 2 DUP (00h), 02h, 3 DUP (00h), 01h, 3 DUP (00h), 01h, 00h, 08h
db 00h, 2 DUP (0ffh), 2 DUP (00h), 03h, 3 DUP (00h), 01h, 00h, 0ch, 00h, 01h, 00h, 01h, 00h, 01h, 3 DUP (00h), 04h
db 3 DUP (00h), 01h, 00h, 06h, 00h, 01h, 00h, 04h, 00h, 01h, 3 DUP (00h), 05h, 3 DUP (00h), 01h, 3 DUP (00h), 01h
db 00h, 08h, 00h, 01h, 3 DUP (00h), 06h, 3 DUP (00h), 01h, 3 DUP (00h), 01h, 00h, 08h, 00h, 2 DUP (0ffh), 2 DUP (00h), 07h
db 3 DUP (00h), 01h, 3 DUP (00h), 01h, 00h, 08h, 00h, 01h, 3 DUP (00h), 08h, 3 DUP (00h), 01h, 11 DUP (00h), 09h, 3 DUP (00h), 01h
db 11 DUP (00h), 0ah, 15 DUP (00h), 0bh, 15 DUP (00h), 0ch, 3 DUP (00h), 01h, 00h, 18h, 9 DUP (00h), 0dh, 3 DUP (00h), 01h, 00h, 16h
db 9 DUP (00h), 0eh, 3 DUP (00h), 01h, 00h, 16h, 9 DUP (00h), 0fh, 3 DUP (00h), 01h, 00h, 14h, 9 DUP (00h), 10h, 3 DUP (00h), 01h
db 00h, 18h, 9 DUP (00h), 11h, 3 DUP (00h), 01h, 00h, 14h, 9 DUP (00h)
PUBLIC C UINT_ARRAY_0040a434
UINT_ARRAY_0040a434 byte 12h, 3 DUP (00h), 01h, 00h, 14h, 9 DUP (00h), 13h, 3 DUP (00h), 01h, 00h, 16h, 9 DUP (00h), 14h, 3 DUP (00h), 01h, 00h
db 16h, 9 DUP (00h), 15h, 7 DUP (00h), 03h, 3 DUP (00h), 06h, 3 DUP (00h)
db 0bh, 3 DUP (00h), 0bh, 3 DUP (00h), 0bh, 3 DUP (00h), 0bh, 3 DUP (00h), 0bh, 3 DUP (00h), 0bh, 7 DUP (00h)
PUBLIC C DAT_0040a490
DAT_0040a490 byte 01h
db 00h, 01h, 9 DUP (00h), 16h, 3 DUP (00h), 01h, 00h, 01h, 00h, 01h, 00h, 04h, 00h, 2 DUP (0ffh), 2 DUP (00h), 17h
db 3 DUP (00h), 01h, 00h, 01h, 00h, 01h, 00h, 04h, 00h, 01h, 3 DUP (00h), 18h, 15 DUP (00h), 19h, 15 DUP (00h), 1ah
db 3 DUP (00h)
PUBLIC C DAT_0040a4e0
DAT_0040a4e0 byte 02h
db 00h, 12h, 00h, 02h, 00h, 01h, 00h, 2 DUP (0ffh), 2 DUP (00h), 1fh, 3 DUP (00h), 02h, 00h, 12h, 00h, 02h
db 00h, 01h, 00h, 01h, 3 DUP (00h), 20h, 3 DUP (00h), 01h, 00h, 16h, 9 DUP (00h), 21h, 3 DUP (00h), 01h, 00h, 04h
db 9 DUP (00h), 22h, 3 DUP (00h), 01h, 00h, 04h, 9 DUP (00h), 23h, 3 DUP (00h), 01h, 00h, 04h, 9 DUP (00h), 24h, 3 DUP (00h), 01h
db 00h, 04h, 9 DUP (00h), 25h, 3 DUP (00h), 01h, 00h, 04h, 9 DUP (00h), 26h, 3 DUP (00h)
PUBLIC C DAT_0040a560
DAT_0040a560 byte 0ffh
db 3 DUP (0ffh), 5ah, 6eh, 40h, 00h, 2 DUP (6eh), 40h, 00h, 72h, 75h, 6eh, 74h, 69h, 6dh, 65h, 20h
db 65h, 2 DUP (72h), 6fh, 72h, 20h, 2 DUP (00h), 0dh, 0ah, 2 DUP (00h), 54h, 4ch, 4fh, 2 DUP (53h), 20h, 65h, 2 DUP (72h)
db 6fh, 72h, 0dh, 0ah, 3 DUP (00h), 53h, 49h, 4eh, 47h, 20h, 65h, 2 DUP (72h), 6fh, 72h, 0dh, 0ah
db 4 DUP (00h), 44h, 4fh, 4dh, 41h, 49h, 4eh, 20h, 65h, 2 DUP (72h), 6fh, 72h, 0dh, 0ah, 2 DUP (00h), 52h
db 36h, 30h, 32h, 38h, 0dh, 0ah, 2dh, 20h, 75h, 6eh, 61h, 62h, 6ch, 65h, 20h, 74h
db 6fh, 20h, 69h, 6eh, 69h, 74h, 69h, 61h, 6ch, 69h, 7ah, 65h, 20h, 68h, 65h, 61h
db 70h, 0dh, 0ah, 4 DUP (00h), 52h, 36h, 30h, 32h, 37h, 0dh, 0ah, 2dh, 20h, 6eh, 6fh, 74h
db 20h, 65h, 6eh, 6fh, 75h, 67h, 68h, 20h, 73h, 70h, 61h, 63h, 65h, 20h, 66h, 6fh
db 72h, 20h, 6ch, 6fh, 77h, 69h, 6fh, 20h, 69h, 6eh, 69h, 74h, 69h, 61h, 6ch, 69h
db 7ah, 61h, 74h, 69h, 6fh, 6eh, 0dh, 0ah, 4 DUP (00h), 52h, 36h, 30h, 32h, 36h, 0dh, 0ah
db 2dh, 20h, 6eh, 6fh, 74h, 20h, 65h, 6eh, 6fh, 75h, 67h, 68h, 20h, 73h, 70h, 61h
db 63h, 65h, 20h, 66h, 6fh, 72h, 20h, 73h, 74h, 64h, 69h, 6fh, 20h, 69h, 6eh, 69h
db 74h, 69h, 61h, 6ch, 69h, 7ah, 61h, 74h, 69h, 6fh, 6eh, 0dh, 0ah, 4 DUP (00h), 52h, 36h
db 30h, 32h, 35h, 0dh, 0ah, 2dh, 20h, 70h, 75h, 72h, 65h, 20h, 76h, 69h, 72h, 74h
db 75h, 61h, 6ch, 20h, 66h, 75h, 6eh, 63h, 74h, 69h, 6fh, 6eh, 20h, 63h, 61h, 2 DUP (6ch)
db 0dh, 0ah, 3 DUP (00h), 52h, 36h, 30h, 32h, 34h, 0dh, 0ah, 2dh, 20h, 6eh, 6fh, 74h, 20h
db 65h, 6eh, 6fh, 75h, 67h, 68h, 20h, 73h, 70h, 61h, 63h, 65h, 20h, 66h, 6fh, 72h
db 20h, 5fh, 6fh, 6eh, 65h, 78h, 69h, 74h, 2fh, 61h, 74h, 65h, 78h, 69h, 74h, 20h
db 74h, 61h, 62h, 6ch, 65h, 0dh, 0ah, 4 DUP (00h), 52h, 36h, 30h, 31h, 39h, 0dh, 0ah, 2dh
db 20h, 75h, 6eh, 61h, 62h, 6ch, 65h, 20h, 74h, 6fh, 20h, 6fh, 70h, 65h, 6eh, 20h
db 63h, 6fh, 6eh, 73h, 6fh, 6ch, 65h, 20h, 64h, 65h, 76h, 69h, 63h, 65h, 0dh, 0ah
db 4 DUP (00h), 52h, 36h, 30h, 31h, 38h, 0dh, 0ah, 2dh, 20h, 75h, 6eh, 65h, 78h, 70h, 65h
db 63h, 74h, 65h, 64h, 20h, 68h, 65h, 61h, 70h, 20h, 65h, 2 DUP (72h), 6fh, 72h, 0dh, 0ah
db 4 DUP (00h), 52h, 36h, 30h, 31h, 37h, 0dh, 0ah, 2dh, 20h, 75h, 6eh, 65h, 78h, 70h, 65h
db 63h, 74h, 65h, 64h, 20h, 6dh, 75h, 6ch, 74h, 69h, 74h, 68h, 72h, 65h, 61h, 64h
db 20h, 6ch, 6fh, 63h, 6bh, 20h, 65h, 2 DUP (72h), 6fh, 72h, 0dh, 0ah, 4 DUP (00h), 52h, 36h, 30h
db 31h, 36h, 0dh, 0ah, 2dh, 20h, 6eh, 6fh, 74h, 20h, 65h, 6eh, 6fh, 75h, 67h, 68h
db 20h, 73h, 70h, 61h, 63h, 65h, 20h, 66h, 6fh, 72h, 20h, 74h, 68h, 72h, 65h, 61h
db 64h, 20h, 64h, 61h, 74h, 61h, 0dh, 0ah, 00h, 0dh, 0ah, 61h, 62h, 6eh, 6fh, 72h
db 6dh, 61h, 6ch, 20h, 70h, 72h, 6fh, 67h, 72h, 61h, 6dh, 20h, 74h, 65h, 72h, 6dh
db 69h, 6eh, 61h, 74h, 69h, 6fh, 6eh, 0dh, 0ah, 4 DUP (00h), 52h, 36h, 2 DUP (30h), 39h, 0dh, 0ah
db 2dh, 20h, 6eh, 6fh, 74h, 20h, 65h, 6eh, 6fh, 75h, 67h, 68h, 20h, 73h, 70h, 61h
db 63h, 65h, 20h, 66h, 6fh, 72h, 20h, 65h, 6eh, 76h, 69h, 72h, 6fh, 6eh, 6dh, 65h
db 6eh, 74h, 0dh, 0ah, 00h
PUBLIC C not_enough_space_for_arg_str
not_enough_space_for_arg_str byte 52h, 36h, 2 DUP (30h), 38h, 0dh, 0ah, 2dh, 20h, 6eh, 6fh, 74h, 20h, 65h, 6eh, 6fh, 75h
db 67h, 68h, 20h, 73h, 70h, 61h, 63h, 65h, 20h, 66h, 6fh, 72h, 20h, 61h, 72h, 67h
db 75h, 6dh, 65h, 6eh, 74h, 73h, 0dh, 0ah, 00h
db 2 DUP (00h)
PUBLIC C floating_point_not_loaded_str
floating_point_not_loaded_str byte 52h, 36h, 2 DUP (30h), 32h, 0dh, 0ah, 2dh, 20h, 66h, 6ch, 6fh, 61h, 74h, 69h, 6eh, 67h
db 20h, 70h, 6fh, 69h, 6eh, 74h, 20h, 6eh, 6fh, 74h, 20h, 6ch, 6fh, 61h, 64h, 65h
db 64h, 0dh, 0ah, 4 DUP (00h)
PUBLIC C microsoft_visual_str
microsoft_visual_str byte 4dh, 69h, 63h, 72h, 6fh, 73h, 6fh, 66h, 74h, 20h, 56h, 69h, 73h, 75h, 61h, 6ch
db 20h, 43h, 2 DUP (2bh), 20h, 52h, 75h, 6eh, 74h, 69h, 6dh, 65h, 20h, 4ch, 69h, 62h, 72h
db 61h, 72h, 79h, 00h
db 3 DUP (00h)
PUBLIC C s_runtime_error
s_runtime_error byte 52h, 75h, 6eh, 74h, 69h, 6dh, 65h, 20h, 45h, 2 DUP (72h), 6fh, 72h, 21h, 2 DUP (0ah), 50h, 72h
db 6fh, 67h, 72h, 61h, 6dh, 3ah, 20h, 00h
db 2 DUP (00h)
PUBLIC C DAT_0040a83c
DAT_0040a83c byte 2eh
db 2 DUP (2eh), 00h
PUBLIC C s_program_name_unknown
s_program_name_unknown byte 3ch, 70h, 72h, 6fh, 67h, 72h, 61h, 6dh, 20h, 6eh, 61h, 6dh, 65h, 20h, 75h, 6eh
db 6bh, 6eh, 6fh, 77h, 6eh, 3eh, 00h
db 00h
PUBLIC C DAT_0040a858
DAT_0040a858 byte 00h
db 3 DUP (00h)
PUBLIC C DAT_0040a85c
DAT_0040a85c byte 00h
db 3 DUP (00h)
PUBLIC C DAT_0040a860
DAT_0040a860 byte 0ffh
db 3 DUP (0ffh), 0c9h, 7ch, 40h, 00h, 0cdh, 7ch, 40h, 00h
PUBLIC C s_GetLastActivePopup_0040a86c
s_GetLastActivePopup_0040a86c byte 47h, 65h, 74h, 4ch, 61h, 73h, 74h, 41h, 63h, 74h, 69h, 76h, 65h, 50h, 6fh, 70h
db 75h, 70h, 00h
db 00h
PUBLIC C s_GetActiveWindow_0040a880
s_GetActiveWindow_0040a880 byte 47h, 65h, 74h, 41h, 63h, 74h, 69h, 76h, 65h, 57h, 69h, 6eh, 64h, 6fh, 77h, 00h
PUBLIC C s_MessageBoxA_0040a890
s_MessageBoxA_0040a890 byte 4dh, 65h, 2 DUP (73h), 61h, 67h, 65h, 42h, 6fh, 78h, 41h, 00h
PUBLIC C s_user32_dll
s_user32_dll byte 75h, 73h, 65h, 72h, 33h, 32h, 2eh, 64h, 2 DUP (6ch), 00h
db 00h
PUBLIC C DAT_0040a8a8
DAT_0040a8a8 byte 0ffh
db 3 DUP (0ffh), 0fh, 92h, 40h, 00h, 13h, 92h, 40h, 00h, 4 DUP (0ffh), 0c3h, 92h, 40h, 00h, 0c7h, 92h
db 40h, 00h
PUBLIC C DWORD_0040a8c0
DWORD_0040a8c0 byte 60h, 0a9h, 2 DUP (00h)
db 8 DUP (00h), 7eh, 0abh, 2 DUP (00h), 3ch, 0a0h, 2 DUP (00h), 24h, 0aah, 10 DUP (00h), 6ah, 0adh, 3 DUP (00h), 0a1h, 2 DUP (00h), 24h
db 0a9h, 10 DUP (00h), 5ch, 0aeh, 3 DUP (00h), 0a0h, 2 DUP (00h), 0ach, 0aah, 10 DUP (00h), 76h, 0aeh, 2 DUP (00h), 88h, 0a1h, 22 DUP (00h)
db 0a4h, 0adh, 2 DUP (00h), 0b4h, 0adh, 2 DUP (00h), 44h, 0aeh, 2 DUP (00h), 76h, 0adh, 2 DUP (00h), 80h, 0adh, 2 DUP (00h), 8ah
db 0adh, 2 DUP (00h), 0c4h, 0adh, 2 DUP (00h), 0d0h, 0adh, 2 DUP (00h), 0e2h, 0adh, 2 DUP (00h), 18h, 0aeh, 2 DUP (00h), 26h, 0aeh
db 2 DUP (00h), 0f2h, 0adh, 2 DUP (00h), 32h, 0aeh, 2 DUP (00h), 02h, 0aeh, 6 DUP (00h), 62h, 0abh, 2 DUP (00h), 72h, 0abh, 2 DUP (00h)
db 54h, 0abh, 2 DUP (00h), 44h, 0abh, 2 DUP (00h), 34h, 0abh, 2 DUP (00h), 28h, 0abh, 2 DUP (00h), 0ch, 0abh, 2 DUP (00h), 0eeh
db 0aah, 2 DUP (00h), 0deh, 0aah, 2 DUP (00h), 0c4h, 0aah, 2 DUP (00h), 0d0h, 0b0h, 2 DUP (00h), 0c0h, 0b0h, 2 DUP (00h), 0e0h, 0b0h
db 2 DUP (00h), 0a0h, 0b0h, 2 DUP (00h), 0aeh, 0b0h, 2 DUP (00h), 84h, 0b0h, 2 DUP (00h), 78h, 0b0h, 2 DUP (00h), 90h, 0b0h, 2 DUP (00h)
db 62h, 0b0h, 2 DUP (00h), 50h, 0b0h, 2 DUP (00h), 6eh, 0b0h, 2 DUP (00h), 28h, 0b0h, 2 DUP (00h), 1ch, 0b0h, 2 DUP (00h), 3eh
db 0b0h, 2 DUP (00h), 04h, 0b0h, 2 DUP (00h), 0f6h, 0afh, 2 DUP (00h), 10h, 0b0h, 2 DUP (00h), 0dah, 0afh, 2 DUP (00h), 0cch, 0afh
db 2 DUP (00h), 0e8h, 0afh, 2 DUP (00h), 0aah, 0afh, 2 DUP (00h), 90h, 0afh, 2 DUP (00h), 0bch, 0afh, 2 DUP (00h), 0b4h, 0aah, 2 DUP (00h)
db 0d0h, 0aah, 2 DUP (00h), 80h, 0aeh, 2 DUP (00h), 94h, 0aeh, 2 DUP (00h), 62h, 0afh, 2 DUP (00h), 48h, 0afh, 2 DUP (00h), 78h
db 0afh, 2 DUP (00h), 18h, 0afh, 2 DUP (00h), 0fch, 0aeh, 2 DUP (00h), 2eh, 0afh, 2 DUP (00h), 0b8h, 0aeh, 2 DUP (00h), 0a6h, 0aeh
db 2 DUP (00h), 0e8h, 0aeh, 2 DUP (00h), 0d4h, 0aeh, 2 DUP (00h), 0c6h, 0aeh, 6 DUP (00h), 24h, 0ach, 2 DUP (00h), 36h, 0ach, 2 DUP (00h)
db 8ch, 0abh, 2 DUP (00h), 0b6h, 0abh, 2 DUP (00h), 98h, 0abh, 2 DUP (00h), 0a8h, 0abh, 2 DUP (00h), 0ech, 0abh, 2 DUP (00h), 0c4h
db 0abh, 2 DUP (00h), 0d8h, 0abh, 2 DUP (00h), 16h, 0ach, 2 DUP (00h), 0fah, 0abh, 2 DUP (00h), 06h, 0ach, 2 DUP (00h), 5eh, 0adh
db 2 DUP (00h), 48h, 0ach, 2 DUP (00h), 36h, 0adh, 2 DUP (00h), 50h, 0adh, 2 DUP (00h), 42h, 0adh, 2 DUP (00h), 0ch, 0adh, 2 DUP (00h)
db 2ah, 0adh, 2 DUP (00h), 1ah, 0adh, 2 DUP (00h), 0dch, 0ach, 2 DUP (00h), 0fah, 0ach, 2 DUP (00h), 0eeh, 0ach, 2 DUP (00h), 2 DUP (0ach)
db 2 DUP (00h), 0d0h, 0ach, 2 DUP (00h), 0beh, 0ach, 2 DUP (00h), 8ah, 0ach, 2 DUP (00h), 0a4h, 0ach, 2 DUP (00h), 98h, 0ach, 2 DUP (00h)
db 62h, 0ach, 2 DUP (00h), 7ah, 0ach, 2 DUP (00h), 6eh, 0ach, 2 DUP (00h), 56h, 0ach, 6 DUP (00h), 66h, 0aeh, 6 DUP (00h), 6dh
db 01h, 47h, 65h, 74h, 54h, 69h, 63h, 6bh, 43h, 6fh, 75h, 6eh, 74h, 2 DUP (00h), 02h, 03h
db 6ch, 73h, 74h, 72h, 63h, 70h, 79h, 41h, 2 DUP (00h), 0c8h, 01h, 4ch, 6fh, 63h, 61h, 6ch
db 41h, 2 DUP (6ch), 6fh, 63h, 2 DUP (00h), 0d5h, 01h, 4ch, 6fh, 63h, 6bh, 52h, 65h, 73h, 6fh, 75h
db 72h, 63h, 65h, 2 DUP (00h), 0e5h, 02h, 57h, 72h, 69h, 74h, 65h, 50h, 72h, 69h, 76h, 61h
db 74h, 65h, 50h, 72h, 6fh, 66h, 69h, 6ch, 65h, 53h, 74h, 72h, 69h, 6eh, 67h, 41h
db 2 DUP (00h), 3ah, 01h, 47h, 65h, 74h, 50h, 72h, 69h, 76h, 61h, 74h, 65h, 50h, 72h, 6fh
db 66h, 69h, 6ch, 65h, 53h, 74h, 72h, 69h, 6eh, 67h, 41h, 2 DUP (00h), 0ffh, 02h, 6ch, 73h
db 74h, 72h, 63h, 6dh, 70h, 69h, 41h, 00h, 0c7h, 01h, 4ch, 6fh, 61h, 64h, 52h, 65h
db 73h, 6fh, 75h, 72h, 63h, 65h, 2 DUP (00h), 0a3h, 00h, 46h, 69h, 6eh, 64h, 52h, 65h, 73h
db 6fh, 75h, 72h, 63h, 65h, 41h, 00h, 0b4h, 00h, 46h, 72h, 2 DUP (65h), 4ch, 69h, 62h, 72h
db 61h, 72h, 79h, 00h, 0b6h, 00h, 46h, 72h, 2 DUP (65h), 52h, 65h, 73h, 6fh, 75h, 72h, 63h
db 65h, 2 DUP (00h), 08h, 03h, 6ch, 73h, 74h, 72h, 6ch, 65h, 6eh, 41h, 2 DUP (00h), 4bh, 45h, 52h
db 4eh, 45h, 4ch, 33h, 32h, 2eh, 64h, 2 DUP (6ch), 2 DUP (00h), 0ach, 02h, 77h, 73h, 70h, 72h, 69h
db 6eh, 74h, 66h, 41h, 00h, 8eh, 00h, 44h, 65h, 73h, 74h, 72h, 6fh, 79h, 57h, 69h
db 6eh, 64h, 6fh, 77h, 00h, 0beh, 01h, 4dh, 65h, 2 DUP (73h), 61h, 67h, 65h, 42h, 6fh, 78h
db 41h, 00h, 0abh, 01h, 4ch, 6fh, 61h, 64h, 53h, 74h, 72h, 69h, 6eh, 67h, 41h, 00h
db 82h, 02h, 54h, 72h, 61h, 6eh, 73h, 6ch, 61h, 74h, 65h, 4dh, 65h, 2 DUP (73h), 61h, 67h
db 65h, 2 DUP (00h), 95h, 00h, 44h, 69h, 73h, 70h, 61h, 74h, 63h, 68h, 4dh, 65h, 2 DUP (73h), 61h
db 67h, 65h, 41h, 2 DUP (00h), 2ah, 01h, 47h, 65h, 74h, 4dh, 65h, 2 DUP (73h), 61h, 67h, 65h, 41h
db 00h, 52h, 02h, 53h, 65h, 74h, 54h, 69h, 6dh, 65h, 72h, 2 DUP (00h), 91h, 02h, 55h, 70h
db 64h, 61h, 74h, 65h, 57h, 69h, 6eh, 64h, 6fh, 77h, 2 DUP (00h), 6ah, 02h, 53h, 68h, 6fh
db 77h, 57h, 69h, 6eh, 64h, 6fh, 77h, 2 DUP (00h), 59h, 00h, 43h, 72h, 65h, 61h, 74h, 65h
db 57h, 69h, 6eh, 64h, 6fh, 77h, 45h, 78h, 41h, 00h, 0f2h, 01h, 52h, 65h, 67h, 69h
db 73h, 74h, 65h, 72h, 43h, 6ch, 61h, 2 DUP (73h), 41h, 2 DUP (00h), 9ah, 01h, 4ch, 6fh, 61h, 64h
db 43h, 75h, 72h, 73h, 6fh, 72h, 41h, 00h, 9eh, 01h, 4ch, 6fh, 61h, 64h, 49h, 63h
db 6fh, 6eh, 41h, 00h, 0d6h, 01h, 4fh, 70h, 65h, 6eh, 49h, 63h, 6fh, 6eh, 2 DUP (00h), 8ch
db 01h, 49h, 73h, 49h, 63h, 6fh, 6eh, 69h, 63h, 2 DUP (00h), 5bh, 02h, 53h, 65h, 74h, 57h
db 69h, 6eh, 64h, 6fh, 77h, 50h, 6fh, 73h, 2 DUP (00h), 0d5h, 00h, 46h, 69h, 6eh, 64h, 57h
db 69h, 6eh, 64h, 6fh, 77h, 41h, 00h, 03h, 02h, 52h, 65h, 6ch, 65h, 61h, 73h, 65h
db 44h, 43h, 00h, 0fdh, 00h, 47h, 65h, 74h, 44h, 43h, 00h, 7ah, 01h, 49h, 6eh, 76h
db 61h, 6ch, 69h, 64h, 61h, 74h, 65h, 52h, 65h, 63h, 74h, 2 DUP (00h), 5eh, 02h, 53h, 65h
db 74h, 57h, 69h, 6eh, 64h, 6fh, 77h, 54h, 65h, 78h, 74h, 41h, 2 DUP (00h), 95h, 01h, 4bh
db 69h, 2 DUP (6ch), 54h, 69h, 6dh, 65h, 72h, 00h, 84h, 00h, 44h, 65h, 66h, 57h, 69h, 6eh
db 64h, 6fh, 77h, 50h, 72h, 6fh, 63h, 41h, 2 DUP (00h), 2fh, 02h, 53h, 65h, 74h, 46h, 6fh
db 63h, 75h, 73h, 2 DUP (00h), 0e0h, 01h, 50h, 6fh, 73h, 74h, 51h, 75h, 69h, 74h, 4dh, 65h
db 2 DUP (73h), 61h, 67h, 65h, 00h, 98h, 01h, 4ch, 6fh, 61h, 64h, 42h, 69h, 74h, 6dh, 61h
db 70h, 41h, 00h, 0f0h, 00h, 47h, 65h, 74h, 43h, 6ch, 69h, 65h, 6eh, 74h, 52h, 65h
db 63h, 74h, 00h, 0bbh, 00h, 45h, 6eh, 64h, 50h, 61h, 69h, 6eh, 74h, 2 DUP (00h), 0d4h, 00h
db 46h, 69h, 2 DUP (6ch), 52h, 65h, 63h, 74h, 2 DUP (00h), 0ch, 00h, 42h, 65h, 67h, 69h, 6eh, 50h
db 61h, 69h, 6eh, 74h, 2 DUP (00h), 0c9h, 01h, 4dh, 6fh, 76h, 65h, 57h, 69h, 6eh, 64h, 6fh
db 77h, 2 DUP (00h), 0dbh, 00h, 46h, 72h, 61h, 6dh, 65h, 52h, 65h, 63h, 74h, 00h, 55h, 53h
db 45h, 52h, 33h, 32h, 2eh, 64h, 2 DUP (6ch), 2 DUP (00h), 11h, 00h, 42h, 69h, 74h, 42h, 6ch, 74h
db 2 DUP (00h), 94h, 01h, 50h, 61h, 74h, 42h, 6ch, 74h, 2 DUP (00h), 29h, 00h, 43h, 72h, 65h, 61h
db 74h, 65h, 43h, 6fh, 6dh, 70h, 61h, 74h, 69h, 62h, 6ch, 65h, 42h, 69h, 74h, 6dh
db 61h, 70h, 2 DUP (00h), 53h, 00h, 44h, 65h, 6ch, 65h, 74h, 65h, 4fh, 62h, 6ah, 65h, 63h
db 74h, 2 DUP (00h), 0c7h, 01h, 53h, 65h, 6ch, 65h, 63h, 74h, 4fh, 62h, 6ah, 65h, 63h, 74h
db 2 DUP (00h), 05h, 02h, 54h, 65h, 78h, 74h, 4fh, 75h, 74h, 41h, 2 DUP (00h), 5fh, 01h, 47h, 65h
db 74h, 53h, 74h, 6fh, 63h, 6bh, 4fh, 62h, 6ah, 65h, 63h, 74h, 2 DUP (00h), 25h, 01h, 47h
db 65h, 74h, 44h, 65h, 76h, 69h, 63h, 65h, 43h, 61h, 70h, 73h, 00h, 24h, 00h, 43h
db 72h, 65h, 61h, 74h, 65h, 42h, 69h, 74h, 6dh, 61h, 70h, 2 DUP (00h), 2ah, 00h, 43h, 72h
db 65h, 61h, 74h, 65h, 43h, 6fh, 6dh, 70h, 61h, 74h, 69h, 62h, 6ch, 65h, 44h, 43h
db 2 DUP (00h), 4fh, 01h, 47h, 65h, 74h, 4fh, 62h, 6ah, 65h, 63h, 74h, 41h, 2 DUP (00h), 50h, 00h
db 44h, 65h, 6ch, 65h, 74h, 65h, 44h, 43h, 2 DUP (00h), 75h, 01h, 47h, 65h, 74h, 54h, 65h
db 78h, 74h, 4dh, 65h, 74h, 72h, 69h, 63h, 73h, 41h, 00h, 6eh, 01h, 47h, 65h, 74h
db 54h, 65h, 78h, 74h, 45h, 78h, 74h, 65h, 6eh, 74h, 50h, 6fh, 69h, 6eh, 74h, 33h
db 32h, 41h, 00h, 47h, 44h, 49h, 33h, 32h, 2eh, 64h, 2 DUP (6ch), 00h, 91h, 00h, 73h, 6eh
db 64h, 50h, 6ch, 61h, 79h, 53h, 6fh, 75h, 6eh, 64h, 41h, 00h, 57h, 49h, 4eh, 2 DUP (4dh)
db 2eh, 64h, 2 DUP (6ch), 00h, 26h, 01h, 47h, 65h, 74h, 4dh, 6fh, 64h, 75h, 6ch, 65h, 48h
db 61h, 6eh, 64h, 6ch, 65h, 41h, 2 DUP (00h), 50h, 01h, 47h, 65h, 74h, 53h, 74h, 61h, 72h
db 74h, 75h, 70h, 49h, 6eh, 66h, 6fh, 41h, 00h, 0cah, 00h, 47h, 65h, 74h, 43h, 6fh
db 2 DUP (6dh), 61h, 6eh, 64h, 4ch, 69h, 6eh, 65h, 41h, 00h, 74h, 01h, 47h, 65h, 74h, 56h
db 65h, 72h, 73h, 69h, 6fh, 6eh, 2 DUP (00h), 7dh, 00h, 45h, 78h, 69h, 74h, 50h, 72h, 6fh
db 63h, 65h, 2 DUP (73h), 00h, 9eh, 02h, 54h, 65h, 72h, 6dh, 69h, 6eh, 61h, 74h, 65h, 50h
db 72h, 6fh, 63h, 65h, 2 DUP (73h), 2 DUP (00h), 0f7h, 00h, 47h, 65h, 74h, 43h, 75h, 2 DUP (72h), 65h, 6eh
db 74h, 50h, 72h, 6fh, 63h, 65h, 2 DUP (73h), 00h, 0adh, 02h, 55h, 6eh, 68h, 61h, 6eh, 64h
db 6ch, 65h, 64h, 45h, 78h, 63h, 65h, 70h, 74h, 69h, 6fh, 6eh, 46h, 69h, 6ch, 74h
db 65h, 72h, 2 DUP (00h), 24h, 01h, 47h, 65h, 74h, 4dh, 6fh, 64h, 75h, 6ch, 65h, 46h, 69h
db 6ch, 65h, 4eh, 61h, 6dh, 65h, 41h, 2 DUP (00h), 0b2h, 00h, 46h, 72h, 2 DUP (65h), 45h, 6eh, 76h
db 69h, 72h, 6fh, 6eh, 6dh, 65h, 6eh, 74h, 53h, 74h, 72h, 69h, 6eh, 67h, 73h, 41h
db 00h, 0b3h, 00h, 46h, 72h, 2 DUP (65h), 45h, 6eh, 76h, 69h, 72h, 6fh, 6eh, 6dh, 65h, 6eh
db 74h, 53h, 74h, 72h, 69h, 6eh, 67h, 73h, 57h, 00h, 0d2h, 02h, 57h, 69h, 64h, 65h
db 43h, 68h, 61h, 72h, 54h, 6fh, 4dh, 75h, 6ch, 74h, 69h, 42h, 79h, 74h, 65h, 00h
db 06h, 01h, 47h, 65h, 74h, 45h, 6eh, 76h, 69h, 72h, 6fh, 6eh, 6dh, 65h, 6eh, 74h
db 53h, 74h, 72h, 69h, 6eh, 67h, 73h, 00h, 08h, 01h, 47h, 65h, 74h, 45h, 6eh, 76h
db 69h, 72h, 6fh, 6eh, 6dh, 65h, 6eh, 74h, 53h, 74h, 72h, 69h, 6eh, 67h, 73h, 57h
db 2 DUP (00h), 6dh, 02h, 53h, 65h, 74h, 48h, 61h, 6eh, 64h, 6ch, 65h, 43h, 6fh, 75h, 6eh
db 74h, 2 DUP (00h), 52h, 01h, 47h, 65h, 74h, 53h, 74h, 64h, 48h, 61h, 6eh, 64h, 6ch, 65h
db 2 DUP (00h), 15h, 01h, 47h, 65h, 74h, 46h, 69h, 6ch, 65h, 54h, 79h, 70h, 65h, 00h, 9dh
db 01h, 48h, 65h, 61h, 70h, 44h, 65h, 73h, 74h, 72h, 6fh, 79h, 00h, 9bh, 01h, 48h
db 65h, 61h, 70h, 43h, 72h, 65h, 61h, 74h, 65h, 2 DUP (00h), 0bfh, 02h, 56h, 69h, 72h, 74h
db 75h, 61h, 6ch, 46h, 72h, 2 DUP (65h), 00h, 9fh, 01h, 48h, 65h, 61h, 70h, 46h, 72h, 2 DUP (65h)
db 2 DUP (00h), 2fh, 02h, 52h, 74h, 6ch, 55h, 6eh, 77h, 69h, 6eh, 64h, 00h, 0dfh, 02h, 57h
db 72h, 69h, 74h, 65h, 46h, 69h, 6ch, 65h, 00h, 0e4h, 01h, 4dh, 75h, 6ch, 74h, 69h
db 42h, 79h, 74h, 65h, 54h, 6fh, 57h, 69h, 64h, 65h, 43h, 68h, 61h, 72h, 00h, 53h
db 01h, 47h, 65h, 74h, 53h, 74h, 72h, 69h, 6eh, 67h, 54h, 79h, 70h, 65h, 41h, 2 DUP (00h)
db 56h, 01h, 47h, 65h, 74h, 53h, 74h, 72h, 69h, 6eh, 67h, 54h, 79h, 70h, 65h, 57h
db 2 DUP (00h), 0bfh, 00h, 47h, 65h, 74h, 43h, 50h, 49h, 6eh, 66h, 6fh, 00h, 0b9h, 00h, 47h
db 65h, 74h, 41h, 43h, 50h, 2 DUP (00h), 31h, 01h, 47h, 65h, 74h, 4fh, 45h, 4dh, 43h, 50h
db 2 DUP (00h), 99h, 01h, 48h, 65h, 61h, 70h, 41h, 2 DUP (6ch), 6fh, 63h, 00h, 0bbh, 02h, 56h, 69h
db 72h, 74h, 75h, 61h, 6ch, 41h, 2 DUP (6ch), 6fh, 63h, 2 DUP (00h), 0a2h, 01h, 48h, 65h, 61h, 70h
db 52h, 65h, 41h, 2 DUP (6ch), 6fh, 63h, 00h, 3eh, 01h, 47h, 65h, 74h, 50h, 72h, 6fh, 63h
db 41h, 2 DUP (64h), 72h, 65h, 2 DUP (73h), 2 DUP (00h), 0c2h, 01h, 4ch, 6fh, 61h, 64h, 4ch, 69h, 62h, 72h
db 61h, 72h, 79h, 41h, 2 DUP (00h), 0bfh, 01h, 4ch, 43h, 4dh, 61h, 70h, 53h, 74h, 72h, 69h
db 6eh, 67h, 41h, 2 DUP (00h), 0c0h, 01h, 4ch, 43h, 4dh, 61h, 70h, 53h, 74h, 72h, 69h, 6eh
db 67h, 57h, 3858 DUP (00h)

END

