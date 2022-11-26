_updateGameState proc
          mov   ax, word ptr [playerX]  ; <c640>
          mov   cx, word ptr [playerY]  ; <c5f2>
          sub   word ptr [DAT_0040c714], ax     ; <c714>
          sub   word ptr [DAT_0040c5d8], cx     ; <c5d8>
          push  ebx
          push  esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          push  edi
          test  esi, esi
          jz    LAB_00401ef4
          mov   edi, 0FFFFFFDFh
          mov   ebx, 00000000Bh
LAB_00401e82:     test  byte ptr [esi+04Ch], 00Ah
          jnz   LAB_00401eee
          mov   ecx, dword ptr [esi+04Ch]
          mov   eax, dword ptr [esi+00Ch]
          and   ecx, edi
          test  eax, eax
          mov   dword ptr [esi+04Ch], ecx
          jnz   LAB_00401ea3
          cmp   dword ptr [esi+018h], ebx
          jge   LAB_00401ea3
          mov   ecx, esi
          call  @updateActor@4
LAB_00401ea3:     mov   eax, dword ptr [esi+04Ch]
          test  al, 001h
          jnz   LAB_00401eee
          cmp   esi, dword ptr [playerActor]    ; <c72c>
          jz    LAB_00401eee
          test  al, 004h
          jz    LAB_00401ebb
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00401ec2
LAB_00401ebb:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00401ec2:     mov   edx, offset windowClientRectWith120Margin.left  ; <c680>
          mov   ecx, eax
          call  @doRectsOverlap@8
          test  eax, eax
          jnz   LAB_00401eee
          mov   edx, dword ptr [esi+014h]
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          movsx eax, word ptr [edx+00Eh]
          sub   ecx, eax
          mov   dword ptr [totalAreaOfActorSprites], ecx        ; <c6fc>
          mov   ecx, esi
          call  @actorSetFlag8IfFlag1IsUnset@4
LAB_00401eee:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00401e82
LAB_00401ef4:     mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c738.startingObject      ; <c738>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          call  @updateAllPermObjectsInList@4
          call  _removeFlag8ActorsFromList
          mov   edi, dword ptr [actorListPtr]   ; <c618>
          test  edi, edi
          jz    LAB_00401fc5
          push  ebp
LAB_00401f3a:     mov   eax, dword ptr [edi+04Ch]
          test  al, 002h
          jnz   LAB_00401fba
          test  al, 004h
          jz    LAB_00401f4a
          lea   ebx, dword ptr [edi+020h]
          jmp   LAB_00401f53
LAB_00401f4a:     mov   ecx, edi
          call  @updateActorSpriteRect@4
          mov   ebx, eax
LAB_00401f53:     mov   ebp, dword ptr [edi+04Ch]
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          shl   ebp, 01Ah
          sar   ebp, 01Fh
          test  esi, esi
          jz    LAB_00401fba
LAB_00401f66:     cmp   edi, esi
          jz    LAB_00401fba
          mov   eax, dword ptr [esi+04Ch]
          test  al, 002h
          jnz   LAB_00401fb4
          test  ebp, ebp
          jnz   LAB_00401f79
          test  al, 020h
          jz    LAB_00401fb4
LAB_00401f79:     test  al, 004h
          jz    LAB_00401f82
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00401f89
LAB_00401f82:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00401f89:     mov   edx, eax
          mov   ecx, ebx
          call  @doRectsOverlap@8
          test  eax, eax
          jz    LAB_00401fb4
          mov   edx, esi
          mov   ecx, edi
          call  @handleActorCollision@8
          test  byte ptr [edi+04Ch], 008h
          jnz   LAB_00401fb4
          test  byte ptr [esi+04Ch], 008h
          jnz   LAB_00401fb4
          mov   edx, edi
          mov   ecx, esi
          call  @handleActorCollision@8
LAB_00401fb4:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00401f66
LAB_00401fba:     mov   edi, dword ptr [edi]
          test  edi, edi
          jnz   LAB_00401f3a
          pop   ebp
LAB_00401fc5:     mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          mov   cx, word ptr [playerX]  ; <c640>
          add   ax, word ptr [playerY]  ; <c5f2>
          add   word ptr [DAT_0040c714], cx     ; <c714>
          pop   edi
          pop   esi
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          pop   ebx
          jle   LAB_0040200f
LAB_00401fef:     mov   ecx, 000000003h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          add   ax, 0FFC4h
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          jg    LAB_00401fef
LAB_0040200f:     cmp   ax, 0FFC4h
          jge   LAB_00402035
LAB_00402015:     mov   ecx, 000000002h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          add   ax, 0003Ch
          cmp   ax, 0FFC4h
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          jl    LAB_00402015
LAB_00402035:     mov   ax, word ptr [DAT_0040c714]     ; <c714>
          cmp   ax, 0003Ch
          jle   LAB_00402061
LAB_00402041:     mov   ecx, 000000001h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c714]     ; <c714>
          add   ax, 0FFC4h
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c714], ax     ; <c714>
          jg    LAB_00402041
LAB_00402061:     cmp   ax, 0FFC4h
          jge   LAB_00402084
LAB_00402067:     xor   ecx, ecx
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c714]     ; <c714>
          add   ax, 0003Ch
          cmp   ax, 0FFC4h
          mov   word ptr [DAT_0040c714], ax     ; <c714>
          jl    LAB_00402067
LAB_00402084:     mov   ecx, 00000029Ah
          call  @random@4
          test  ax, ax
          jnz   LAB_004020ae
          mov   edx, 00000001Fh
          mov   ecx, 000000003h
          call  @addActorOfType@8
          mov   ecx, eax
          mov   edx, 000000002h
          jmp   @updateActorWithOffscreenStartingPosition@8
LAB_004020ae:     ret
LAB_004020af:
          db 090h
_updateGameState endp