@actorSetFlag8IfFlag1IsUnset@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_00401366
          mov   edx, 000000361h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401366:     test  byte ptr [esi+04Ch], 001h
          jnz   LAB_00401382
          mov   eax, dword ptr [esi+004h]
          test  eax, eax
          jz    LAB_0040137a
          mov   dword ptr [eax+004h], 000000000h
LAB_0040137a:     mov   eax, dword ptr [esi+04Ch]
          or    al, 008h
          mov   dword ptr [esi+04Ch], eax
LAB_00401382:     pop   esi
          ret
LAB_00401384:
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
@actorSetFlag8IfFlag1IsUnset@4 endp