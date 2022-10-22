@updateActorSpriteRect@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          push  edi
          jnz   LAB_00401427
          mov   edx, 0000003A3h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401427:     test  byte ptr [esi+04Ch], 004h
          jz    LAB_0040143c
          mov   edx, 0000003A4h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040143c:     cmp   word ptr [esi+010h], 000000000h
          jnz   LAB_00401452
          mov   edx, 0000003A5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401452:     mov   edx, dword ptr [sprites]        ; <c5f8>
          mov   ecx, dword ptr [esi+014h]
          xor   eax, eax
          mov   ax, word ptr [esi+010h]
          shl   eax, 004h
          add   eax, edx
          cmp   eax, ecx
          jz    LAB_00401479
          mov   edx, 0000003A6h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401479:     mov   cx, word ptr [esi+044h]
          mov   dx, word ptr [esi+042h]
          mov   ax, word ptr [esi+040h]
          lea   edi, dword ptr [esi+020h]
          push  ecx
          push  edx
          mov   edx, dword ptr [esi+014h]
          push  eax
          mov   ecx, edi
          call  @updateRectForSpriteAtLocation@20
          mov   eax, dword ptr [esi+04Ch]
          or    al, 004h
          mov   dword ptr [esi+04Ch], eax
          mov   eax, edi
          pop   edi
          pop   esi
          ret
LAB_004014a2:
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
          db 090h
          db 090h
          db 090h
@updateActorSpriteRect@4 endp