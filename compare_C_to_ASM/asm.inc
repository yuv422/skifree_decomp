@createBitmapSheets@4 proc
          sub   esp, 000000034h
          mov   eax, dword ptr [sprites]        ; <c5f8>
          push  ebx
          push  ebp
          xor   ebx, ebx
          mov   ebp, ecx
          mov   dword ptr [eax], ebx
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          push  esi
          push  edi
          mov   dword ptr [esp+028h], ebp
          mov   dword ptr [ecx+004h], ebx
          mov   edx, dword ptr [sprites]        ; <c5f8>
          mov   dword ptr [esp+010h], ebx
          mov   dword ptr [esp+024h], ebx
          mov   word ptr [edx+008h], bx
          mov   eax, dword ptr [sprites]        ; <c5f8>
          mov   dword ptr [esp+018h], ebx
          mov   dword ptr [esp+014h], ebx
          mov   word ptr [eax+00Ah], bx
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          mov   dword ptr [esp+020h], ebx
          mov   dword ptr [esp+01Ch], ebx
          mov   word ptr [ecx+00Ch], bx
          mov   edx, dword ptr [sprites]        ; <c5f8>
          mov   edi, 000000001h
          mov   word ptr [edx+00Eh], bx
LAB_00405b13:     mov   ecx, edi
          call  @loadBitmapResource@4
          mov   esi, eax
          cmp   esi, ebx
          jz    LAB_00405e7d
          lea   eax, dword ptr [esp+02Ch]
          push  eax
          push  000000018h
          push  esi
          call  dword ptr [__imp__GetObjectA@12]        ; <GetObjectA>
          movsx edx, word ptr [esp+010h]
          mov   ecx, dword ptr [esp+030h]
          cmp   ecx, edx
          jle   LAB_00405b43
          mov   dword ptr [esp+010h], ecx
LAB_00405b43:     movsx edx, word ptr [esp+024h]
          mov   eax, dword ptr [esp+034h]
          cmp   eax, edx
          jle   LAB_00405b54
          mov   dword ptr [esp+024h], eax
LAB_00405b54:     cmp   ecx, 000000020h
          jle   LAB_00405b5f
          add   dword ptr [esp+018h], eax
          jmp   LAB_00405b63
LAB_00405b5f:     add   dword ptr [esp+014h], eax
LAB_00405b63:     push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          inc   edi
          cmp   di, 00000005Ah
          jb    LAB_00405b13
          push  ebp
          call  dword ptr [__imp__CreateCompatibleDC@4] ; <CreateCompatibleDC>
          cmp   eax, ebx
          mov   dword ptr [smallBitmapDC], eax  ; <c710>
          jnz   LAB_00405b8b
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405b8b:     movsx edi, word ptr [esp+014h]
          push  edi
          push  000000020h
          push  ebp
          call  dword ptr [__imp__CreateCompatibleBitmap@12]    ; <CreateCompatibleBitmap>
          mov   esi, eax
          cmp   esi, ebx
          jnz   LAB_00405baa
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405baa:     mov   eax, dword ptr [smallBitmapDC]  ; <c710>
          push  esi
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          cmp   eax, ebx
          mov   dword ptr [smallBitmapSheet], eax       ; <c620>
          jnz   LAB_00405bd1
          push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          xor   eax, eax
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405bd1:     push  ebp
          call  dword ptr [__imp__CreateCompatibleDC@4] ; <CreateCompatibleDC>
          cmp   eax, ebx
          mov   dword ptr [smallBitmapDC_1bpp], eax     ; <c6a4>
          jnz   LAB_00405beb
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405beb:     push  ebx
          push  000000001h
          push  000000001h
          push  edi
          push  000000020h
          call  dword ptr [__imp__CreateBitmap@20]      ; <CreateBitmap>
          mov   esi, eax
          cmp   esi, ebx
          jnz   LAB_00405c09
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405c09:     mov   ecx, dword ptr [smallBitmapDC_1bpp]     ; <c6a4>
          push  esi
          push  ecx
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          cmp   eax, ebx
          mov   dword ptr [smallBitmapSheet_1bpp], eax  ; <c6d4>
          jnz   LAB_00405c31
          push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          xor   eax, eax
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405c31:     push  ebp
          call  dword ptr [__imp__CreateCompatibleDC@4] ; <CreateCompatibleDC>
          cmp   eax, ebx
          mov   dword ptr [largeBitmapDC], eax  ; <c730>
          jnz   LAB_00405c4b
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405c4b:     movsx edi, word ptr [esp+018h]
          movsx ebx, word ptr [esp+010h]
          push  edi
          push  ebx
          push  ebp
          call  dword ptr [__imp__CreateCompatibleBitmap@12]    ; <CreateCompatibleBitmap>
          mov   esi, eax
          test  esi, esi
          jnz   LAB_00405c6c
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405c6c:     mov   edx, dword ptr [largeBitmapDC]  ; <c730>
          push  esi
          push  edx
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          test  eax, eax
          mov   dword ptr [largeBitmapSheet], eax       ; <c644>
          jnz   LAB_00405c94
          push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          xor   eax, eax
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405c94:     push  ebp
          call  dword ptr [__imp__CreateCompatibleDC@4] ; <CreateCompatibleDC>
          test  eax, eax
          mov   dword ptr [largeBitmapDC_1bpp], eax     ; <c6ec>
          jnz   LAB_00405cac
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405cac:     push  000000000h
          push  000000001h
          push  000000001h
          push  edi
          push  ebx
          call  dword ptr [__imp__CreateBitmap@20]      ; <CreateBitmap>
          mov   esi, eax
          test  esi, esi
          jnz   LAB_00405cc8
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405cc8:     mov   eax, dword ptr [largeBitmapDC_1bpp]     ; <c6ec>
          push  esi
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          test  eax, eax
          mov   dword ptr [largeBitmapSheet_1bpp], eax  ; <c75c>
          jnz   LAB_00405cef
          push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          xor   eax, eax
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405cef:     push  ebp
          call  dword ptr [__imp__CreateCompatibleDC@4] ; <CreateCompatibleDC>
          mov   dword ptr [bitmapSourceDC], eax ; <c5ec>
          mov   ebx, 000000001h
LAB_00405d00:     mov   edx, dword ptr [sprites]        ; <c5f8>
          mov   esi, ebx
          and   esi, 00000FFFFh
          mov   ecx, ebx
          shl   esi, 004h
          add   esi, edx
          call  @loadBitmapResource@4
          test  eax, eax
          mov   dword ptr [esp+018h], eax
          jz    LAB_00405e7d
          lea   ecx, dword ptr [esp+02Ch]
          push  ecx
          push  000000018h
          push  eax
          call  dword ptr [__imp__GetObjectA@12]        ; <GetObjectA>
          mov   edi, dword ptr [esp+030h]
          mov   word ptr [esi+00Ah], di
          mov   eax, dword ptr [esp+034h]
          mov   edx, eax
          mov   word ptr [esi+00Ch], ax
          imul  edx, edi
          cmp   di, 000000020h
          mov   word ptr [esi+00Eh], dx
          jle   LAB_00405d61
          mov   ebp, dword ptr [esp+01Ch]
          mov   ecx, ebp
          add   ecx, eax
          mov   dword ptr [esp+01Ch], ecx
          jmp   LAB_00405d6d
LAB_00405d61:     mov   ebp, dword ptr [esp+020h]
          mov   ecx, ebp
          add   ecx, eax
          mov   dword ptr [esp+020h], ecx
LAB_00405d6d:     mov   eax, dword ptr [esp+018h]
          mov   word ptr [esi+008h], bp
          mov   ecx, dword ptr [bitmapSourceDC] ; <c5ec>
          push  eax
          push  ecx
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          cmp   di, 000000020h
          mov   dword ptr [esp+018h], eax
          mov   eax, dword ptr [largeBitmapDC]  ; <c730>
          jg    LAB_00405d97
          mov   eax, dword ptr [smallBitmapDC]  ; <c710>
LAB_00405d97:     mov   dword ptr [esi], eax
          mov   ecx, dword ptr [largeBitmapDC_1bpp]     ; <c6ec>
          cmp   di, 000000020h
          jg    LAB_00405dab
          mov   ecx, dword ptr [smallBitmapDC_1bpp]     ; <c6a4>
LAB_00405dab:     mov   dword ptr [esi+004h], ecx
          mov   edx, dword ptr [bitmapSourceDC] ; <c5ec>
          mov   ecx, dword ptr [esp+034h]
          push  000CC0020h
          push  000000000h
          push  000000000h
          movsx edi, bp
          mov   ebp, dword ptr [__imp__BitBlt@36]       ; <BitBlt>
          push  edx
          mov   edx, dword ptr [esp+040h]
          push  ecx
          push  edx
          push  edi
          push  000000000h
          push  eax
          call  ebp
          mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          mov   ecx, dword ptr [esp+034h]
          mov   edx, dword ptr [esp+030h]
          push  000330008h
          push  000000000h
          push  000000000h
          push  eax
          mov   eax, dword ptr [esi+004h]
          push  ecx
          push  edx
          push  edi
          push  000000000h
          push  eax
          call  ebp
          mov   edx, dword ptr [bitmapSourceDC] ; <c5ec>
          mov   ecx, dword ptr [esp+018h]
          push  ecx
          push  edx
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          push  eax
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          inc   ebx
          cmp   bx, 00000005Ah
          jb    LAB_00405d00
          mov   eax, dword ptr [esp+010h]
          mov   edx, dword ptr [esp+028h]
          and   al, 0C0h
          add   eax, 000000040h
          mov   cx, ax
          mov   eax, dword ptr [esp+024h]
          and   al, 0C0h
          mov   word ptr [scratchBitmapWidth], cx       ; <c690>
          add   eax, 000000040h
          mov   word ptr [scratchBitmapHeight], ax      ; <c6e8>
          movsx eax, ax
          movsx ecx, cx
          push  eax
          push  ecx
          push  edx
          call  dword ptr [__imp__CreateCompatibleBitmap@12]    ; <CreateCompatibleBitmap>
          mov   esi, eax
          test  esi, esi
          jnz   LAB_00405e60
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405e60:     mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          push  esi
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          test  eax, eax
          mov   dword ptr [scratchBitmap], eax  ; <c614>
          jnz   LAB_00405e87
          push  esi
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
LAB_00405e7d:     pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405e87:     pop   edi
          pop   esi
          pop   ebp
          mov   eax, 000000001h
          pop   ebx
          add   esp, 000000034h
          ret
LAB_00405e94:
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
@createBitmapSheets@4 endp