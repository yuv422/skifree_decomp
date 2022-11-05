@permObjectSetSpriteIdx@8 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_00403149
          mov   edx, 0000006EDh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403149:     mov   eax, edi
          mov   word ptr [esi+008h], di
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          and   eax, 00000FFFFh
          shl   eax, 004h
          add   eax, ecx
          mov   ecx, dword ptr [esi]
          test  ecx, ecx
          mov   dword ptr [esi+004h], eax
          jz    LAB_0040316f
          mov   edx, edi
          call  @actorSetSpriteIdx@8
LAB_0040316f:     pop   edi
          pop   esi
          ret
LAB_00403172:
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
@permObjectSetSpriteIdx@8 endp