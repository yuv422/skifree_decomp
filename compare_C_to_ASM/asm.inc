_allocateMemory proc
          push  esi
          mov   esi, dword ptr [__imp__LocalAlloc@8]    ; <LocalAlloc>
          push  000000050h
          push  000000000h
          call  esi
          mov   dword ptr [stringCache], eax    ; <c674>
          push  0000005A0h
          push  000000000h
          call  esi
          mov   dword ptr [sprites], eax        ; <c5f8>
          push  000001F40h
          push  000000000h
          call  esi
          mov   dword ptr [actors], eax ; <c648>
          push  000002400h
          push  000000000h
          call  esi
          mov   ecx, dword ptr [stringCache]    ; <c674>
          mov   dword ptr [permObjects], eax   ; <c758>
          test  ecx, ecx
          pop   esi
          jz    LAB_0040493d
          mov   ecx, dword ptr [actors] ; <c648>
          test  ecx, ecx
          jz    LAB_0040493d
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          test  ecx, ecx
          jz    LAB_0040493d
          test  eax, eax
          jz    LAB_0040493d
          xor   eax, eax
LAB_00404921:     mov   ecx, dword ptr [stringCache]    ; <c674>
          add   eax, 000000004h
          cmp   eax, 000000050h
          mov   dword ptr [eax+ecx*1-004h], 000000000h
          jl    LAB_00404921
          mov   eax, 000000001h
          ret
LAB_0040493d:     mov   ecx, offset s_insufficient_local_memory ; <c104>
          call  @showErrorMessage@4
          xor   eax, eax
          ret
LAB_0040494a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_allocateMemory endp