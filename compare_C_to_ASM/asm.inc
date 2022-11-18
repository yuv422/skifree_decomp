extern @updatePermObject@4: proc
extern @addActorForPermObject@4: proc

@updateAllPermObjectsInList@4 proc
          mov   eax, dword ptr [skierScreenYOffset]     ; <c5fc>
          push  ebx
          push  ebp
          mov   ebp, dword ptr [windowClientRectWith120Margin.bottom]   ; <c68c>
          push  esi
          push  edi
          mov   edi, dword ptr [windowClientRectWith120Margin.top]      ; <c684>
          sub   ebp, eax
          sub   edi, eax
          mov   ebx, ecx
          sub   edi, 00000003Ch
          add   ebp, 00000003Ch
          mov   esi, dword ptr [ebx]
          test  ebx, ebx
          jnz   LAB_004040d6
          mov   edx, 000000B0Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004040d6:     cmp   esi, dword ptr [ebx+004h]
          jbe   LAB_004040ed
          mov   edx, 000000B0Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          cmp   esi, dword ptr [ebx+004h]
LAB_004040ed:     jae   LAB_0040411c
LAB_004040ef:     mov   ecx, esi
          call  @updatePermObject@4
          mov   ax, word ptr [esi+016h]
          sub   ax, word ptr [playerY]  ; <c5f2>
          cmp   ax, di
          jl    LAB_00404112
          cmp   ax, bp
          jge   LAB_00404112
          mov   ecx, esi
          call  @addActorForPermObject@4
LAB_00404112:     mov   eax, dword ptr [ebx+004h]
          add   esi, 000000024h
          cmp   esi, eax
          jb    LAB_004040ef
LAB_0040411c:     pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret
LAB_00404121:
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
          db 090h
@updateAllPermObjectsInList@4 endp