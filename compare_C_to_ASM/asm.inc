@addPermObject@8 proc
          push  ebx
          push  esi
          push  edi
          mov   edi, ecx
          mov   cx, word ptr [permObjectCount]  ; <c702>
          xor   eax, eax
          mov   ax, cx
          mov   esi, edx
          mov   edx, dword ptr [PTR_0040c758]   ; <c758>
          inc   cx
          lea   eax, dword ptr [eax+eax*8]
          mov   word ptr [permObjectCount], cx  ; <c702>
          test  edi, edi
          lea   ebx, dword ptr [edx+eax*4]
          jnz   LAB_0040515b
          mov   edx, 000000A1Bh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040515b:     test  esi, esi
          jnz   LAB_0040516e
          mov   edx, 000000A1Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040516e:     cmp   word ptr [permObjectCount], 00100h      ; <c702>
          jbe   LAB_00405188
          mov   edx, 000000A1Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00405188:     cmp   dword ptr [edi], 000000000h
          jnz   LAB_00405195
          mov   dword ptr [edi+008h], ebx
          mov   dword ptr [edi+004h], ebx
          mov   dword ptr [edi], ebx
LAB_00405195:     cmp   dword ptr [edi+004h], ebx
          jz    LAB_004051a9
          mov   edx, 000000A20h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004051a9:     mov   eax, dword ptr [edi+004h]
          mov   ecx, 000000009h
          add   eax, 000000024h
          mov   dword ptr [edi+004h], eax
          mov   edi, ebx
          xor   eax, eax
          rep movsd     [esi], es:[edi]
          mov   ax, word ptr [ebx+008h]
          mov   dword ptr [ebx], 000000000h
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          pop   edi
          shl   eax, 004h
          add   eax, ecx
          pop   esi
          mov   dword ptr [ebx+004h], eax
          mov   eax, ebx
          pop   ebx
          ret
LAB_004051db:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@addPermObject@8 endp