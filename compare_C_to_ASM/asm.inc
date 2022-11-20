@FUN_00404350@4 proc
          sub   esp, 00000000Ch
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          xor   ebx, ebx
          push  edi
          mov   ebp, dword ptr [esi+010h]
          mov   edi, dword ptr [esi+00Ch]
          cmp   esi, ebx
          mov   dword ptr [esp+014h], ebp
          jnz   LAB_00404378
          mov   edx, 000000A68h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00404378:     cmp   word ptr [esi+018h], bx
          jle   LAB_00404384
          dec   word ptr [esi+01Eh]
          jmp   LAB_0040438c
LAB_00404384:     mov   word ptr [esi+01Eh], bx
          mov   word ptr [esi+018h], bx
LAB_0040438c:     cmp   word ptr [esi+018h], bx
          jnz   LAB_004046b8
          cmp   ebp, 000000032h
          jl    LAB_00404471
          cmp   ebp, 000000038h
          jge   LAB_00404471
          mov   eax, dword ptr [currentTickCount]       ; <c698>
          mov   edi, dword ptr [esi+020h]
          lea   ecx, dword ptr [ebp-032h]
          sub   eax, edi
          cmp   ecx, 000000005h
          ja    LAB_00404457
          jmp   dword ptr [ecx*4+LAB_004046c4]  ; <46c4>
LAB_004043c5:     mov   ebp, 000000033h
          pop   edi
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_004043d5:     xor   ecx, ecx
          cmp   eax, 0000001F4h
          setge cl
          dec   ecx
          pop   edi
          and   ecx, 0FFFFFFFEh
          add   ecx, 000000034h
          mov   ebp, ecx
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_004043f3:     cmp   eax, 0000002BCh
          jle   LAB_004046b8
          mov   ebp, 000000035h
          pop   edi
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_0040440e:     cmp   eax, 0000003E8h
          jle   LAB_004046b8
          mov   ebp, 000000036h
          pop   edi
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_00404429:     mov   ebp, 000000037h
          pop   edi
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_00404439:     xor   edx, edx
          cmp   eax, 000000BB8h
          setge dl
          dec   edx
          pop   edi
          and   edx, 00000000Ch
          add   edx, 00000002Ah
          mov   ebp, edx
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_00404457:     mov   edx, 000000A76h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          mov   dword ptr [esi+010h], ebp
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_00404471:     mov   ax, word ptr [esi+016h]
          mov   bp, word ptr [esi+014h]
          cmp   edi, 000000005h
          mov   dword ptr [esp+018h], eax
          mov   dword ptr [esp+010h], ebx
          jnz   LAB_00404496
          cmp   ax, 0F830h
          jle   LAB_004044dd
          mov   ebx, 0FFFFFFF6h
          jmp   LAB_004045d8
LAB_00404496:     cmp   edi, 000000006h
          jnz   LAB_004044ab
          cmp   ax, 07D00h
          jge   LAB_004044dd
          mov   ebx, 00000001Ah
          jmp   LAB_004045d8
LAB_004044ab:     cmp   edi, 000000007h
          jnz   LAB_004044c4
          cmp   bp, 0C180h
          jle   LAB_004044dd
          mov   dword ptr [esp+010h], 0FFFFFFF0h
          jmp   LAB_004045d8
LAB_004044c4:     cmp   edi, 000000008h
          jnz   LAB_004044dd
          cmp   bp, 03E80h
          jge   LAB_004044dd
          mov   dword ptr [esp+010h], 000000010h
          jmp   LAB_004045d8
LAB_004044dd:     mov   eax, dword ptr [playerActor]    ; <c72c>
          cmp   eax, ebx
          jz    LAB_004045d8
          mov   dx, word ptr [eax+040h]
          mov   cx, word ptr [eax+042h]
          cmp   edi, 000000005h
          jnz   LAB_00404503
          cmp   cx, 0F830h
          jl    LAB_00404539
          jmp   LAB_004045d8
LAB_00404503:     cmp   edi, 000000006h
          jnz   LAB_00404514
          cmp   cx, 07D00h
          jg    LAB_00404539
          jmp   LAB_004045d8
LAB_00404514:     cmp   edi, 000000007h
          jnz   LAB_00404525
          cmp   dx, 0C180h
          jl    LAB_00404539
          jmp   LAB_004045d8
LAB_00404525:     cmp   edi, 000000008h
          jnz   LAB_004045d8
          cmp   dx, 03E80h
          jle   LAB_004045d8
LAB_00404539:     movsx eax, dx
          movsx edi, bp
          mov   ebx, dword ptr [windowWidth]    ; <c5f0>
          sub   eax, edi
          movsx edi, word ptr [esp+018h]
          movsx ecx, cx
          sub   ecx, edi
          movsx edi, bx
          cmp   eax, edi
          jle   LAB_0040455c
          sub   edx, ebx
          jmp   LAB_00404564
LAB_0040455c:     neg   edi
          cmp   eax, edi
          jge   LAB_00404568
          add   edx, ebx
LAB_00404564:     mov   word ptr [esi+014h], dx
LAB_00404568:     mov   di, word ptr [windowHeight]     ; <c6d8>
          movsx edx, di
          cmp   ecx, edx
          jle   LAB_00404585
          mov   edx, dword ptr [playerActor]    ; <c72c>
          mov   dx, word ptr [edx+042h]
          sub   dx, di
          jmp   LAB_00404598
LAB_00404585:     neg   edx
          cmp   ecx, edx
          jge   LAB_0040459c
          mov   edx, dword ptr [playerActor]    ; <c72c>
          mov   dx, word ptr [edx+042h]
          add   dx, di
LAB_00404598:     mov   word ptr [esi+016h], dx
LAB_0040459c:     cmp   eax, 000000010h
          jl    LAB_004045a8
          mov   eax, 000000010h
          jmp   LAB_004045b2
LAB_004045a8:     cmp   eax, 0FFFFFFF0h
          jg    LAB_004045b2
          mov   eax, 0FFFFFFF0h
LAB_004045b2:     cmp   ecx, 00000001Ah
          jl    LAB_004045be
          mov   ecx, 00000001Ah
          jmp   LAB_004045c8
LAB_004045be:     cmp   ecx, 0FFFFFFF6h
          jg    LAB_004045c8
          mov   ecx, 0FFFFFFF6h
LAB_004045c8:     mov   ebx, ecx
          mov   ecx, offset sound_9.soundResource       ; <c6f0>
          mov   dword ptr [esp+010h], eax
          call  @playSound@4
LAB_004045d8:     movsx edi, word ptr [esp+010h]
          mov   eax, edi
          cdq
          movsx ecx, bx
          mov   ebp, eax
          mov   eax, ecx
          xor   ebp, edx
          sub   ebp, edx
          cdq
          xor   eax, edx
          sub   eax, edx
          cmp   ebp, eax
          jle   LAB_00404604
          movsx eax, word ptr [esi+01Ah]
          imul  eax, ecx
          cdq
          idiv  edi
          mov   word ptr [esi+01Ch], ax
          jmp   LAB_00404617
LAB_00404604:     test  bx, bx
          jz    LAB_0040461d
          movsx eax, word ptr [esi+01Ch]
          imul  eax, edi
          cdq
          idiv  ecx
          mov   word ptr [esi+01Ah], ax
LAB_00404617:     mov   word ptr [esi+01Eh], 00001h
LAB_0040461d:     mov   eax, dword ptr [esp+010h]
          mov   word ptr [esi+01Ch], bx
          test  bx, bx
          mov   word ptr [esi+01Ah], ax
          jge   LAB_0040464a
          mov   edx, dword ptr [esp+014h]
          xor   eax, eax
          cmp   edx, 000000030h
          pop   edi
          setz  al
          add   eax, 000000030h
          mov   ebp, eax
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_0040464a:     test  ax, ax
          jge   LAB_0040466b
          mov   edx, dword ptr [esp+014h]
          xor   ecx, ecx
          cmp   edx, 00000002Ch
          pop   edi
          setz  cl
          add   ecx, 00000002Ch
          mov   ebp, ecx
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_0040466b:     jg    LAB_004046a7
          test  bx, bx
          jg    LAB_004046a7
          mov   ecx, 00000000Ah
          call  @random@4
          test  ax, ax
          jz    LAB_00404691
          mov   ebp, 00000002Ah
          pop   edi
          mov   dword ptr [esi+010h], ebp
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_00404691:     mov   ebp, 00000002Bh
          mov   word ptr [esi+01Eh], 00004h
          mov   dword ptr [esi+010h], ebp
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_004046a7:     mov   ecx, dword ptr [esp+014h]
          xor   edx, edx
          cmp   ecx, 00000002Eh
          setz  dl
          add   edx, 00000002Eh
          mov   ebp, edx
LAB_004046b8:     mov   dword ptr [esi+010h], ebp
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000000Ch
          ret
LAB_004046c3:
          db 090h
LAB_004046c4:
DAT_004046c4  dword offset LAB_004043c5
DAT_004046c8  dword offset LAB_004043d5
DAT_004046cc  dword offset LAB_004043f3
DAT_004046d0  dword offset LAB_0040440e
DAT_004046d4  dword offset LAB_00404429
DAT_004046d8  dword offset LAB_00404439
          db 090h
          db 090h
          db 090h
          db 090h
@FUN_00404350@4 endp