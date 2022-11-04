_resetPlayerFrameNo proc
          mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_00402eb7
          mov   edx, dword ptr [ecx+01Ch]
          cmp   edx, 00000000Bh
          jz    LAB_00402ea7
          cmp   edx, 000000011h
          jz    LAB_00402ea7
          xor   edx, edx
          cmp   word ptr [ecx+044h], dx
          setle dl
          dec   edx
          and   edx, 00000000Bh
          add   edx, 000000003h
LAB_00402ea7:     call  @setActorFrameNo@8
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          jmp   @formatAndPrintStatusStrings@4
LAB_00402eb7:     ret
LAB_00402eb8:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_resetPlayerFrameNo endp