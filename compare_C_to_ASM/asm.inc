@updateActorPositionMaybe@16 proc
          push  ecx
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          mov   ebp, edx
          push  edi
          cmp   word ptr [esi+040h], bp
          jnz   LAB_004023ae
          mov   ax, word ptr [esi+042h]
          cmp   ax, word ptr [esp+018h]
          jnz   LAB_004023ae
          xor   edi, edi
          jmp   LAB_004023b3
LAB_004023ae:     mov   edi, 000000001h
LAB_004023b3:     mov   dx, word ptr [esi+044h]
          xor   ecx, ecx
          cmp   dx, word ptr [esp+01Ch]
          setnz cl
          mov   dword ptr [esp+010h], ecx
          mov   ecx, dword ptr [playerActorPtrMaybe_1]  ; <c64c>
          xor   ebx, ebx
          cmp   esi, ecx
          setz  bl
          test  esi, esi
          jnz   LAB_004023e5
          mov   edx, 00000040Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004023e5:     test  ebx, ebx
          jz    LAB_004023f8
          test  edi, edi
          jz    LAB_004023fc
          mov   edx, dword ptr [esp+018h]
          mov   ecx, ebp
          call  @updateActorRectsAfterPlayerMove@8
LAB_004023f8:     test  edi, edi
          jnz   LAB_00402404
LAB_004023fc:     mov   eax, dword ptr [esp+010h]
          test  eax, eax
          jz    LAB_0040245e
LAB_00402404:     mov   eax, dword ptr [esi+04Ch]
          mov   edi, eax
          shl   edi, 01Dh
          sar   edi, 01Fh
          test  al, 001h
          jz    LAB_0040241c
          mov   ecx, esi
          call  @duplicateAndLinkActor@4
          mov   esi, eax
LAB_0040241c:     test  edi, edi
          jz    LAB_00402433
          test  ebx, ebx
          jz    LAB_00402433
          mov   eax, dword ptr [esp+010h]
          test  eax, eax
          jnz   LAB_00402433
          mov   eax, 000000001h
          jmp   LAB_00402435
LAB_00402433:     xor   eax, eax
LAB_00402435:     mov   cx, word ptr [esp+018h]
          mov   dx, word ptr [esp+01Ch]
          and   eax, 000000001h
          mov   word ptr [esi+042h], cx
          mov   ecx, dword ptr [esi+04Ch]
          or    al, 008h
          shl   eax, 002h
          and   ecx, 0FFFFFFFBh
          mov   word ptr [esi+040h], bp
          or    eax, ecx
          mov   word ptr [esi+044h], dx
          mov   dword ptr [esi+04Ch], eax
LAB_0040245e:     mov   eax, esi
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          pop   ecx
          ret   00008h
LAB_00402468:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorPositionMaybe@16 endp