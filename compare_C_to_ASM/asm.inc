_randomActorType3 proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          cdq
          and   edx, 00000000Fh
          add   eax, edx
          sar   eax, 004h
          cmp   ecx, eax
          jle   LAB_004027be
          mov   eax, 000000012h
          ret
LAB_004027be:     mov   ecx, 000000040h
          call  @random@4
          neg   ax
          sbb   eax, eax
          and   eax, 00000000Bh
          add   eax, 000000002h
          ret
LAB_004027d4:
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
_randomActorType3 endp