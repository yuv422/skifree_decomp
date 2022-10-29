_randomActorType2 proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          cdq
          and   edx, 00000001Fh
          add   eax, edx
          sar   eax, 005h
          cmp   ecx, eax
          jle   LAB_004027fe
          mov   eax, 000000012h
          ret
LAB_004027fe:     mov   ecx, 000000064h
          call  @random@4
          cmp   ax, 00002h
          jae   LAB_00402814
          mov   eax, 00000000Ah
          ret
LAB_00402814:     cmp   ax, 00014h
          jae   LAB_00402820
          mov   eax, 00000000Dh
          ret
LAB_00402820:     cmp   ax, 00032h
          jae   LAB_0040282c
          mov   eax, 00000000Fh
          ret
LAB_0040282c:     cmp   ax, 0003Ch
          jae   LAB_00402838
          mov   eax, 00000000Bh
          ret
LAB_00402838:     cmp   ax, 00050h
          sbb   eax, eax
          and   al, 0FEh
          add   eax, 000000010h
          ret
LAB_00402844:
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
_randomActorType2 endp