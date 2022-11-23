@getSkierInAirSpriteFromMousePosition@8 proc
          test  cx, cx
          jge   LAB_0040669f
          test  dx, dx
          jge   LAB_0040668a
          xor   eax, eax
          cmp   dx, cx
          setge al
          dec   eax
          and   eax, 000000002h
          add   eax, 00000000Eh
          ret
LAB_0040668a:     movsx eax, dx
          movsx ecx, cx
          neg   eax
          xor   edx, edx
          cmp   eax, ecx
          setge dl
          add   edx, 00000000Dh
          mov   eax, edx
          ret
LAB_0040669f:     test  dx, dx
          jge   LAB_004066b9
          movsx eax, dx
          movsx ecx, cx
          neg   eax
          xor   edx, edx
          cmp   eax, ecx
          setg  dl
          add   edx, 00000000Fh
          mov   eax, edx
          ret
LAB_004066b9:     xor   eax, eax
          cmp   dx, cx
          setle al
          add   eax, 00000000Dh
          ret
LAB_004066c5:
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
@getSkierInAirSpriteFromMousePosition@8 endp