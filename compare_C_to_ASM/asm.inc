@isSlowTile@4 proc
          cmp   cx, 00000001Bh
          jz    LAB_0040231f
          cmp   cx, 000000052h
          jz    LAB_0040231f
          xor   eax, eax
          ret
LAB_0040231f:     mov   eax, 000000001h
          ret
LAB_00402325:
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
@isSlowTile@4 endp