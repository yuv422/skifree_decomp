@enlargeRect@8 proc
          push  esi
          push  edi
          mov   edi, edx
          mov   esi, ecx
          test  edi, edi
          jnz   LAB_00401b39
          mov   edx, 00000016Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401b39:     test  esi, esi
          jnz   LAB_00401b4c
          mov   edx, 00000016Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401b4c:     mov   eax, dword ptr [edi]
          mov   ecx, dword ptr [esi]
          cmp   eax, ecx
          jge   LAB_00401b56
          mov   dword ptr [esi], eax
LAB_00401b56:     mov   eax, dword ptr [edi+008h]
          mov   ecx, dword ptr [esi+008h]
          cmp   eax, ecx
          jle   LAB_00401b63
          mov   dword ptr [esi+008h], eax
LAB_00401b63:     mov   eax, dword ptr [edi+004h]
          mov   ecx, dword ptr [esi+004h]
          cmp   eax, ecx
          jge   LAB_00401b70
          mov   dword ptr [esi+004h], eax
LAB_00401b70:     mov   edi, dword ptr [edi+00Ch]
          mov   eax, dword ptr [esi+00Ch]
          cmp   edi, eax
          jle   LAB_00401b7d
          mov   dword ptr [esi+00Ch], edi
LAB_00401b7d:     pop   edi
          pop   esi
          ret
@enlargeRect@8 endp