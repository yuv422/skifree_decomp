@drawActor@8 proc
          sub   esp, 000000040h
          push  ebx
          push  ebp
          mov   ebx, edx
          push  esi
          push  edi
          mov   dword ptr [esp+030h], ebx
          mov   di, word ptr [ebx+030h]
          mov   ax, word ptr [ebx+034h]
          mov   bp, word ptr [ebx+038h]
          mov   si, word ptr [ebx+03Ch]
          sub   bp, di
          sub   si, ax
          test  ebx, ebx
          mov   dword ptr [esp+014h], ecx
          mov   dword ptr [esp+044h], 000000000h
          mov   dword ptr [esp+03Ch], edi
          mov   dword ptr [esp+018h], eax
          mov   dword ptr [esp+010h], ebp
          mov   dword ptr [esp+038h], esi
          jnz   LAB_00401592
          mov   edx, 00000046Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401592:     mov   eax, dword ptr [esp+014h]
          test  eax, eax
          jnz   LAB_004015a9
          mov   edx, 00000046Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004015a9:     test  byte ptr [ebx+04Ch], 010h
          jnz   LAB_004015be
          mov   edx, 00000046Fh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004015be:     test  ebx, ebx
          mov   ecx, ebx
          jz    LAB_0040195a
LAB_004015c8:     mov   eax, dword ptr [ecx+04Ch]
          mov   edx, eax
          and   eax, 000000002h
          and   edx, 000000001h
          shl   edx, 1h
          xor   edx, eax
          jz    LAB_004015e8
          mov   ecx, dword ptr [ecx+008h]
          test  ecx, ecx
          jnz   LAB_004015c8
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000040h
          ret
LAB_004015e8:     mov   edx, esi
          mov   ecx, ebp
          mov   dword ptr [esp+034h], 000000000h
          call  @changeScratchBitmapSize@8
          test  eax, eax
          jnz   LAB_00401696
          movsx edx, word ptr [esp+018h]
          movsx eax, si
          push  000FF0062h
          push  eax
          movsx ecx, bp
          movsx eax, di
          push  ecx
          mov   ecx, dword ptr [esp+020h]
          push  edx
          push  eax
          push  ecx
          call  dword ptr [__imp__PatBlt@24]    ; <PatBlt>
          mov   esi, ebx
          mov   ebx, dword ptr [__imp__BitBlt@36]       ; <BitBlt>
LAB_0040162b:     mov   eax, dword ptr [esi+04Ch]
          mov   ecx, eax
          and   ecx, 000000001h
          jz    LAB_0040163d
          test  al, 002h
          jz    LAB_0040163d
          and   al, 0FEh
          jmp   LAB_00401684
LAB_0040163d:     test  ecx, ecx
          jnz   LAB_00401687
          test  al, 002h
          jnz   LAB_00401687
          mov   edi, dword ptr [esi+014h]
          test  al, 004h
          jz    LAB_00401651
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00401658
LAB_00401651:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00401658:     movsx edx, word ptr [edi+008h]
          mov   ecx, dword ptr [edi]
          push  0008800C6h
          push  edx
          push  000000000h
          movsx edx, word ptr [edi+00Ch]
          push  ecx
          push  edx
          movsx ecx, word ptr [edi+00Ah]
          mov   edx, dword ptr [eax+004h]
          mov   eax, dword ptr [eax]
          push  ecx
          mov   ecx, dword ptr [esp+02Ch]
          push  edx
          push  eax
          push  ecx
          call  ebx
          mov   eax, dword ptr [esi+04Ch]
          or    al, 001h
LAB_00401684:     mov   dword ptr [esi+04Ch], eax
LAB_00401687:     mov   esi, dword ptr [esi+008h]
          test  esi, esi
          jnz   LAB_0040162b
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000040h
          ret
LAB_00401696:     xor   esi, esi
          lea   edi, dword ptr [esp+030h]
          test  ebx, ebx
          mov   dword ptr [esp+02Ch], esi
          mov   eax, ebx
          jz    LAB_004018ec
LAB_004016aa:     mov   ecx, dword ptr [eax+04Ch]
          lea   ebp, dword ptr [eax+008h]
          test  cl, 002h
          jz    LAB_004016d3
          test  cl, 001h
          jz    LAB_004016c8
          and   ecx, 0FFFFFFFEh
          mov   dword ptr [esp+044h], 000000001h
          mov   dword ptr [eax+04Ch], ecx
LAB_004016c8:     mov   edx, dword ptr [ebp+000h]
          mov   dword ptr [edi], edx
          mov   ebx, dword ptr [esp+030h]
          jmp   LAB_00401703
LAB_004016d3:     test  cl, 040h
          jz    LAB_004016e1
          mov   ecx, dword ptr [eax+014h]
          movsx edx, word ptr [ecx+00Ch]
          jmp   LAB_004016e3
LAB_004016e1:     xor   edx, edx
LAB_004016e3:     mov   cx, word ptr [eax+042h]
          sub   cx, dx
          test  esi, esi
          jz    LAB_004016f5
          cmp   cx, word ptr [esp+048h]
          jge   LAB_00401703
LAB_004016f5:     mov   dword ptr [esp+048h], ecx
          mov   dword ptr [esp+02Ch], eax
          mov   dword ptr [esp+04Ch], edi
          mov   esi, eax
LAB_00401703:     mov   eax, dword ptr [ebp+000h]
          mov   edi, ebp
          test  eax, eax
          jnz   LAB_004016aa
          test  esi, esi
          jz    LAB_004018e0
          mov   ebx, dword ptr [esi+014h]
          mov   ax, word ptr [ebx+00Ch]
          mov   dx, word ptr [ebx+00Ah]
          mov   cx, word ptr [ebx+008h]
          mov   word ptr [esp+020h], ax
          mov   al, byte ptr [esi+04Ch]
          mov   word ptr [esp+01Ch], dx
          test  al, 004h
          mov   word ptr [esp+040h], cx
          jz    LAB_0040173e
          add   esi, 000000020h
          jmp   LAB_00401747
LAB_0040173e:     mov   ecx, esi
          call  @updateActorSpriteRect@4
          mov   esi, eax
LAB_00401747:     movsx eax, word ptr [esp+01Ch]
          mov   edx, dword ptr [esi+008h]
          mov   ecx, dword ptr [esi]
          mov   bp, word ptr [esi]
          mov   di, word ptr [esi+004h]
          sub   bp, word ptr [esp+03Ch]
          sub   di, word ptr [esp+018h]
          sub   edx, ecx
          mov   dword ptr [esp+028h], eax
          cmp   edx, eax
          jz    LAB_0040177b
          mov   edx, 0000004B3h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040177b:     movsx eax, word ptr [esp+020h]
          mov   ecx, dword ptr [esi+00Ch]
          mov   edx, dword ptr [esi+004h]
          sub   ecx, edx
          mov   dword ptr [esp+024h], eax
          cmp   ecx, eax
          jz    LAB_0040179f
          mov   edx, 0000004B4h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040179f:     test  bp, bp
          jge   LAB_004017b3
          mov   edx, 0000004B5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004017b3:     test  di, di
          jge   LAB_004017c7
          mov   edx, 0000004B6h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004017c7:     mov   dx, word ptr [esp+01Ch]
          cmp   dx, word ptr [esp+010h]
          jle   LAB_004017e2
          mov   edx, 0000004B7h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004017e2:     mov   esi, dword ptr [esp+038h]
          cmp   word ptr [esp+020h], si
          jle   LAB_004017fc
          mov   edx, 0000004B8h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004017fc:     mov   eax, dword ptr [esp+034h]
          test  eax, eax
          jnz   LAB_00401873
          test  bp, bp
          mov   dword ptr [esp+034h], 000000001h
          jg    LAB_00401829
          test  di, di
          jg    LAB_00401829
          mov   ax, word ptr [esp+01Ch]
          cmp   ax, word ptr [esp+010h]
          jl    LAB_00401829
          cmp   word ptr [esp+020h], si
          jge   LAB_00401848
LAB_00401829:     movsx edx, word ptr [esp+010h]
          mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          push  000FF0062h
          movsx ecx, si
          push  ecx
          push  edx
          push  000000000h
          push  000000000h
          push  eax
          call  dword ptr [__imp__PatBlt@24]    ; <PatBlt>
LAB_00401848:     movsx ecx, word ptr [esp+040h]
          mov   edx, dword ptr [ebx]
          mov   eax, dword ptr [esp+024h]
          push  000CC0020h
          push  ecx
          mov   ecx, dword ptr [esp+030h]
          push  000000000h
          push  edx
          push  eax
          movsx edx, di
          movsx eax, bp
          push  ecx
          mov   ecx, dword ptr [bitmapSourceDC] ; <c5ec>
          push  edx
          push  eax
          push  ecx
          jmp   LAB_004018c0
LAB_00401873:     movsx esi, word ptr [esp+040h]
          mov   edx, dword ptr [ebx+004h]
          mov   eax, dword ptr [esp+024h]
          mov   ecx, dword ptr [esp+028h]
          push  000EE0086h
          push  esi
          push  000000000h
          movsx edi, di
          movsx ebp, bp
          push  edx
          mov   edx, dword ptr [bitmapSourceDC] ; <c5ec>
          push  eax
          push  ecx
          push  edi
          push  ebp
          push  edx
          call  dword ptr [__imp__BitBlt@36]    ; <BitBlt>
          mov   eax, dword ptr [ebx]
          mov   ecx, dword ptr [esp+024h]
          mov   edx, dword ptr [esp+028h]
          push  0008800C6h
          push  esi
          push  000000000h
          push  eax
          mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          push  ecx
          push  edx
          push  edi
          push  ebp
          push  eax
LAB_004018c0:     call  dword ptr [__imp__BitBlt@36]    ; <BitBlt>
          mov   eax, dword ptr [esp+02Ch]
          mov   edx, dword ptr [esp+04Ch]
          mov   ecx, dword ptr [eax+04Ch]
          or    ecx, 000000001h
          mov   dword ptr [eax+04Ch], ecx
          mov   ecx, dword ptr [eax+008h]
          mov   dword ptr [edx], ecx
          mov   ebx, dword ptr [esp+030h]
LAB_004018e0:     mov   ebp, dword ptr [esp+010h]
          test  ebx, ebx
          jnz   LAB_00401696
LAB_004018ec:     mov   eax, dword ptr [esp+034h]
          test  eax, eax
          jz    LAB_0040192c
          movsx ecx, word ptr [esp+038h]
          mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          push  000CC0020h
          push  000000000h
          push  000000000h
          push  eax
          push  ecx
          movsx eax, word ptr [esp+02Ch]
          movsx ecx, word ptr [esp+050h]
          movsx edx, bp
          push  edx
          mov   edx, dword ptr [esp+02Ch]
          push  eax
          push  ecx
          push  edx
          call  dword ptr [__imp__BitBlt@36]    ; <BitBlt>
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000040h
          ret
LAB_0040192c:     mov   eax, dword ptr [esp+044h]
          test  eax, eax
          jz    LAB_0040195a
          movsx eax, word ptr [esp+038h]
          movsx edx, word ptr [esp+018h]
          push  000FF0062h
          push  eax
          movsx eax, word ptr [esp+044h]
          movsx ecx, bp
          push  ecx
          mov   ecx, dword ptr [esp+020h]
          push  edx
          push  eax
          push  ecx
          call  dword ptr [__imp__PatBlt@24]    ; <PatBlt>
LAB_0040195a:     pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000040h
          ret
LAB_00401962:
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
@drawActor@8 endp
