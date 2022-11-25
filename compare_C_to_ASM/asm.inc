_setupPermObjects proc
          sub   esp, 000000024h
          push  ebx
          push  ebp
          push  esi
          push  edi
          xor   edi, edi
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   word ptr [esp+02Eh], di
          mov   word ptr [esp+02Ch], di
          mov   word ptr [esp+02Ah], di
          mov   word ptr [esp+028h], di
          call  @setPointerToNull@4
          mov   eax, dword ptr [windowClientRect.left]  ; <c6b0>
          mov   edx, dword ptr [skierScreenXOffset]     ; <c704>
          mov   ecx, dword ptr [playerX]        ; <c640>
          sub   eax, edx
          mov   esi, 0FFFFFEC0h
          mov   dword ptr [esp+01Ch], 000000011h
          lea   eax, dword ptr [eax+ecx*1+03Ch]
          mov   word ptr [esp+018h], 0003Dh
          cmp   ax, si
          mov   word ptr [esp+024h], ax
          jge   LAB_00404bb1
          mov   word ptr [esp+024h], si
LAB_00404bb1:     mov   eax, dword ptr [windowClientRect.bottom]        ; <c6bc>
          mov   ebp, dword ptr [skierScreenYOffset]     ; <c5fc>
          sub   eax, ebp
          add   ax, word ptr [playerY]  ; <c5f2>
          sub   eax, 00000003Ch
          cmp   ax, 00280h
          mov   word ptr [esp+026h], ax
          jle   LAB_00404bda
          mov   word ptr [esp+026h], 00208h
LAB_00404bda:     lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          call  @addPermObject@8
          mov   ebp, 0FFFFFDC0h
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   word ptr [esp+018h], 00039h
          mov   word ptr [esp+024h], bp
          mov   word ptr [esp+026h], 00280h
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   word ptr [esp+018h], 0003Ah
          mov   word ptr [esp+024h], si
          call  @addPermObject@8
          mov   dword ptr [esp+01Ch], 00000000Ch
          mov   esi, 000000001h
          mov   dword ptr [firstSlalomFlagLeft], edi    ; <c94c>
          mov   ebx, 0000003C0h
LAB_00404c40:     mov   edx, esi
          mov   eax, esi
          neg   edx
          sbb   edx, edx
          mov   word ptr [esp+026h], bx
          add   edx, 000000018h
          neg   eax
          sbb   eax, eax
          xor   ecx, ecx
          and   al, 0A0h
          mov   word ptr [esp+018h], dx
          add   eax, 0FFFFFE70h
          cmp   esi, edi
          setz  cl
          mov   esi, ecx
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   word ptr [esp+024h], ax
          call  @addPermObject@8
          cmp   dword ptr [firstSlalomFlagLeft], edi    ; <c94c>
          jnz   LAB_00404c89
          mov   dword ptr [firstSlalomFlagLeft], eax    ; <c94c>
LAB_00404c89:     add   ebx, 000000140h
          cmp   bx, 021C0h
          jl    LAB_00404c40
          mov   esi, 000000011h
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   dword ptr [esp+01Ch], esi
          mov   word ptr [esp+018h], 0003Bh
          mov   word ptr [esp+024h], bp
          mov   word ptr [esp+026h], 021C0h
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          mov   word ptr [esp+018h], 0003Ch
          mov   word ptr [esp+024h], 0FEC0h
          call  @addPermObject@8
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          call  @setPointerToNull@4
          mov   edx, dword ptr [windowClientRect.right] ; <c6b8>
          mov   eax, dword ptr [playerX]        ; <c640>
          mov   dword ptr [esp+01Ch], esi
          mov   esi, dword ptr [skierScreenXOffset]     ; <c704>
          sub   edx, esi
          mov   esi, 000000140h
          mov   word ptr [esp+018h], 0003Eh
          lea   eax, dword ptr [edx+eax*1-03Ch]
          cmp   ax, si
          mov   word ptr [esp+024h], ax
          jle   LAB_00404d1c
          mov   word ptr [esp+024h], si
LAB_00404d1c:     mov   eax, dword ptr [windowClientRect.bottom]        ; <c6bc>
          mov   ebp, dword ptr [skierScreenYOffset]     ; <c5fc>
          sub   eax, ebp
          add   ax, word ptr [playerY]  ; <c5f2>
          sub   eax, 00000003Ch
          cmp   ax, 00280h
          mov   word ptr [esp+026h], ax
          jle   LAB_00404d45
          mov   word ptr [esp+026h], 00208h
LAB_00404d45:     lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          mov   word ptr [esp+018h], 00039h
          mov   word ptr [esp+024h], si
          mov   word ptr [esp+026h], 00280h
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          mov   word ptr [esp+018h], 0003Ah
          mov   word ptr [esp+024h], 00200h
          call  @addPermObject@8
          mov   esi, 000000001h
          mov   dword ptr [FirstSlalomFlagRight], edi   ; <c950>
          mov   ebx, 000000410h
          mov   ebp, 000004100h
LAB_00404da5:     mov   ecx, esi
          mov   edx, esi
          neg   ecx
          sbb   ecx, ecx
          mov   dword ptr [esp+01Ch], 00000000Ch
          add   ecx, 000000018h
          mov   word ptr [esp+026h], bx
          neg   edx
          sbb   edx, edx
          xor   eax, eax
          and   edx, 0FFFFFFE0h
          mov   word ptr [esp+018h], cx
          add   edx, 0000001B0h
          cmp   esi, edi
          mov   word ptr [esp+024h], dx
          lea   edx, dword ptr [esp+010h]
          setz  al
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          mov   esi, eax
          call  @addPermObject@8
          cmp   dword ptr [FirstSlalomFlagRight], edi   ; <c950>
          jnz   LAB_00404df8
          mov   dword ptr [FirstSlalomFlagRight], eax   ; <c950>
LAB_00404df8:     mov   ecx, 00000000Dh
          mov   dword ptr [esp+01Ch], ecx
          call  @getSpriteIdxForActorType@4
          mov   ecx, 000000020h
          mov   word ptr [esp+018h], ax
          call  @random@4
          add   eax, 000000190h
          mov   ecx, 000000190h
          mov   word ptr [esp+024h], ax
          call  @random@4
          add   ebx, 000000190h
          cmp   bx, bp
          jl    LAB_00404da5
          mov   esi, 000000011h
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          mov   dword ptr [esp+01Ch], esi
          mov   word ptr [esp+018h], 0003Bh
          mov   word ptr [esp+024h], 00140h
          mov   word ptr [esp+026h], bp
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          mov   word ptr [esp+018h], 0003Ch
          mov   word ptr [esp+024h], 00200h
          call  @addPermObject@8
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          call  @setPointerToNull@4
          mov   eax, dword ptr [windowClientRect.bottom]        ; <c6bc>
          mov   ebx, dword ptr [skierScreenYOffset]     ; <c5fc>
          sub   eax, ebx
          mov   dword ptr [esp+01Ch], esi
          add   ax, word ptr [playerY]  ; <c5f2>
          mov   word ptr [esp+018h], 0003Fh
          mov   word ptr [esp+024h], di
          sub   eax, 00000003Ch
          cmp   ax, 00280h
          mov   word ptr [esp+026h], ax
          jle   LAB_00404ec1
          mov   word ptr [esp+026h], 00208h
LAB_00404ec1:     lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          call  @addPermObject@8
          mov   ebx, 0FFFFFF60h
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          mov   word ptr [esp+018h], 00039h
          mov   word ptr [esp+024h], bx
          mov   word ptr [esp+026h], 00280h
          call  @addPermObject@8
          mov   esi, 0000000A0h
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          mov   word ptr [esp+018h], 0003Ah
          mov   word ptr [esp+024h], si
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          mov   word ptr [esp+018h], 0003Bh
          mov   word ptr [esp+024h], bx
          mov   word ptr [esp+026h], bp
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          mov   word ptr [esp+018h], 0003Ch
          mov   word ptr [esp+024h], si
          call  @addPermObject@8
          mov   ecx, offset PermObjectList_0040c738.startingObject      ; <c738>
          mov   dword ptr [INT_0040c968], edi   ; <c968>
          mov   dword ptr [isFsGameMode], edi   ; <c954>
          call  @setPointerToNull@4
          mov   esi, 0FFFFFC00h
          mov   ebp, 000000040h
          mov   ebx, 0FFFFFF80h
LAB_00404f72:     lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c738.startingObject      ; <c738>
          mov   dword ptr [esp+01Ch], 00000000Dh
          mov   word ptr [esp+018h], bp
          mov   word ptr [esp+024h], bx
          mov   word ptr [esp+026h], si
          mov   word ptr [esp+028h], di
          mov   word ptr [esp+02Eh], di
          mov   word ptr [esp+02Ch], di
          mov   word ptr [esp+02Ah], di
          call  @addPermObject@8
          add   esi, 000000800h
          cmp   si, 05C00h
          jle   LAB_00404f72
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          call  @setPointerToNull@4
          mov   esi, 0FFFFFC00h
          mov   ebx, 000000004h
          mov   ebp, 000000002h
LAB_00404fd1:     cmp   si, 0FC00h
          mov   dword ptr [esp+01Ch], ebx
          mov   word ptr [esp+018h], di
          mov   word ptr [esp+02Eh], di
          mov   word ptr [esp+02Ah], di
          mov   word ptr [esp+028h], 00020h
          mov   word ptr [esp+026h], si
          jle   LAB_0040501b
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+020h], 000000027h
          mov   word ptr [esp+024h], 0FF90h
          mov   word ptr [esp+02Ch], 0FFFEh
          call  @addPermObject@8
LAB_0040501b:     cmp   si, 05C00h
          jge   LAB_00405044
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+020h], 000000029h
          mov   word ptr [esp+024h], 0FF70h
          mov   word ptr [esp+02Ch], bp
          call  @addPermObject@8
LAB_00405044:     add   esi, 000000800h
          cmp   si, 05C00h
          jle   LAB_00404fd1
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+01Ch], 000000007h
          mov   dword ptr [esp+020h], 00000002Ah
          mov   word ptr [esp+018h], di
          mov   word ptr [esp+024h], 0C144h
          mov   word ptr [esp+028h], di
          mov   word ptr [esp+026h], di
          mov   word ptr [esp+02Eh], di
          mov   word ptr [esp+02Ch], di
          mov   word ptr [esp+02Ah], di
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+01Ch], 000000008h
          mov   word ptr [esp+024h], 03EBCh
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+01Ch], 000000005h
          mov   word ptr [esp+024h], di
          mov   word ptr [esp+026h], 0F7F4h
          call  @addPermObject@8
          lea   edx, dword ptr [esp+010h]
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          mov   dword ptr [esp+01Ch], 000000006h
          mov   word ptr [esp+026h], 07D3Ch
          call  @addPermObject@8
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000024h
          ret
LAB_004050f8:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_setupPermObjects endp