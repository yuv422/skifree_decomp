_removeFlag8ActorsFromList proc
          push  ebp
          push  esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          xor   ebp, ebp
          push  edi
          cmp   esi, ebp
          mov   edi, offset actorListPtr        ; <c618>
          jz    LAB_00401401
LAB_004013a4:     test  byte ptr [esi+04Ch], 008h
          jz    LAB_004013f9
          mov   eax, dword ptr [esi+00Ch]
          cmp   eax, ebp
          jz    LAB_004013c9
          cmp   dword ptr [eax], esi
          jz    LAB_004013c4
          mov   edx, 000000376h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004013c4:     mov   eax, dword ptr [esi+00Ch]
          mov   dword ptr [eax], ebp
LAB_004013c9:     cmp   esi, dword ptr [playerActor]    ; <c72c>
          jnz   LAB_004013d7
          mov   dword ptr [playerActor], ebp    ; <c72c>
LAB_004013d7:     cmp   esi, dword ptr [playerActorPtrMaybe_1]  ; <c64c>
          jnz   LAB_004013e5
          mov   dword ptr [playerActorPtrMaybe_1], ebp  ; <c64c>
LAB_004013e5:     mov   ecx, dword ptr [esi]
          mov   dword ptr [edi], ecx
          mov   edx, dword ptr [currentFreeActor]       ; <c744>
          mov   dword ptr [esi], edx
          mov   dword ptr [currentFreeActor], esi       ; <c744>
          jmp   LAB_004013fb
LAB_004013f9:     mov   edi, esi
LAB_004013fb:     mov   esi, dword ptr [edi]
          cmp   esi, ebp
          jnz   LAB_004013a4
LAB_00401401:     pop   edi
          pop   esi
          pop   ebp
          ret
LAB_00401405:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_removeFlag8ActorsFromList endp
