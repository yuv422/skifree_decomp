_resetGame proc
          push  esi
          call  dword ptr [__imp__GetTickCount@0]       ; <GetTickCount>
          mov   dword ptr [currentTickCount], eax       ; <c698>
          push  eax
          call  _srand
          add   esp, 000000004h
          call  _setupActorList
          xor   esi, esi
          mov   dword ptr [playerActorPtrMaybe_1], esi  ; <c64c>
          mov   dword ptr [playerActor], esi    ; <c72c>
          mov   dword ptr [totalAreaOfActorSprites], esi        ; <c6fc>
          call  _resetPermObjectCount
          mov   eax, 000000001h
          mov   dword ptr [isTurboMode], esi    ; <c670>
          mov   word ptr [playerY], si  ; <c5f2>
          mov   word ptr [playerX], si  ; <c640>
          mov   word ptr [DAT_0040c5d8], si     ; <c5d8>
          mov   word ptr [DAT_0040c714], si     ; <c714>
          mov   dword ptr [stylePoints], esi    ; <c6a8>
          mov   dword ptr [INT_0040c964], esi   ; <c964>
          mov   dword ptr [isSsGameMode], esi   ; <c95c>
          mov   dword ptr [INT_0040c960], esi   ; <c960>
          mov   dword ptr [isGsGameMode], esi   ; <c958>
          mov   dword ptr [elapsedTime], esi    ; <c944>
          mov   dword ptr [updateTimerDurationMillis], 000000028h       ; <c678>
          mov   dword ptr [redrawRequired], eax ; <c610>
          pop   esi
          ret
LAB_004049ff:
          db 090h
_resetGame endp