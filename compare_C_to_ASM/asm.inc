@handleKeydownMessage@4 proc
          lea   eax, dword ptr [ecx-00Dh]
          push  esi
          cmp   eax, 000000065h
          ja    LAB_004061b1
          xor   edx, edx
          mov   dl, byte ptr [eax+LAB_004063bc] ; <63bc>
          jmp   dword ptr [edx*4+LAB_004063a8]  ; <63a8>
LAB_00406188:     mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  000000006h
          push  eax
          call  dword ptr [__imp__ShowWindow@8] ; <ShowWindow>
          pop   esi
          ret
LAB_00406198:     pop   esi
          jmp   _togglePausedState
LAB_0040619e:     mov   eax, dword ptr [playerActor]    ; <c72c>
          test  eax, eax
          jnz   LAB_004063a3
LAB_004061ab:     pop   esi
          jmp   _handleGameReset
LAB_004061b1:     mov   eax, dword ptr [playerActor]    ; <c72c>
          test  eax, eax
          jz    LAB_004063a3
          mov   esi, dword ptr [eax+01Ch]
          mov   dx, word ptr [eax+044h]
          cmp   esi, 00000000Bh
          push  edi
          jz    LAB_0040636f
          cmp   esi, 000000011h
          jz    LAB_0040636f
          lea   edi, dword ptr [ecx-021h]
          cmp   edi, 000000048h
          ja    LAB_0040636f
          xor   ecx, ecx
          mov   cl, byte ptr [edi+LAB_0040644c] ; <644c>
          jmp   dword ptr [ecx*4+LAB_00406424]  ; <6424>
LAB_004061f3:     cmp   esi, 000000016h
          jb    LAB_0040620c
          mov   edx, 000000F63h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          mov   eax, dword ptr [playerActor]    ; <c72c>
LAB_0040620c:     mov   esi, dword ptr [esi*8+playerTurnFrameNoTbl.leftFrameNo] ; <a258>
          cmp   esi, 000000007h
          jnz   LAB_0040636f
          movsx ecx, word ptr [eax+046h]
          add   ecx, 0FFFFFFF8h
          cmp   ecx, 0FFFFFFF8h
          jg    LAB_0040622d
          mov   ecx, 0FFFFFFF8h
LAB_0040622d:     mov   word ptr [eax+046h], cx
          jmp   LAB_0040636a
LAB_00406236:     cmp   esi, 000000016h
          jb    LAB_0040624f
          mov   edx, 000000F6Bh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          mov   eax, dword ptr [playerActor]    ; <c72c>
LAB_0040624f:     mov   esi, dword ptr [esi*8+playerTurnFrameNoTbl.rightFrameNo]        ; <a25c>
          cmp   esi, 000000008h
          jnz   LAB_0040636f
          movsx ecx, word ptr [eax+046h]
          add   ecx, esi
          cmp   ecx, esi
          jl    LAB_0040626b
          mov   ecx, esi
LAB_0040626b:     mov   word ptr [eax+046h], cx
          jmp   LAB_0040636a
LAB_00406274:     test  dx, dx
          jnz   LAB_00406280
          xor   esi, esi
          jmp   LAB_0040636f
LAB_00406280:     lea   ecx, dword ptr [esi-00Dh]
          cmp   ecx, 000000008h
          ja    LAB_0040636f
          jmp   dword ptr [ecx*4+LAB_00406498]  ; <6498>
LAB_00406293:     mov   esi, 000000013h
          jmp   LAB_0040636f
LAB_0040629d:     mov   esi, 00000000Eh
          jmp   LAB_0040636f
LAB_004062a7:     mov   esi, 00000000Fh
          jmp   LAB_0040636f
LAB_004062b1:     lea   ecx, dword ptr [esi-003h]
          cmp   ecx, 000000010h
          ja    LAB_0040636f
          jmp   dword ptr [ecx*4+LAB_004064bc]  ; <64bc>
LAB_004062c4:     mov   esi, 000000012h
          jmp   LAB_0040636f
LAB_004062ce:     mov   esi, 00000000Dh
          jmp   LAB_0040636f
LAB_004062d8:     mov   esi, 000000014h
          jmp   LAB_0040636f
LAB_004062e2:     mov   esi, 000000015h
          jmp   LAB_0040636f
LAB_004062ec:     cmp   word ptr [eax+048h], 000000000h
          jnz   LAB_0040636f
          mov   esi, 000000009h
          mov   word ptr [eax+048h], 0FFFCh
          jmp   LAB_0040636a
LAB_00406300:     cmp   word ptr [eax+048h], 000000000h
          jnz   LAB_0040636f
          mov   esi, 00000000Ah
          mov   word ptr [eax+048h], 0FFFCh
          jmp   LAB_0040636a
LAB_00406314:     test  dx, dx
          jnz   LAB_0040636f
          mov   esi, 000000003h
          jmp   LAB_0040636f
LAB_00406320:     test  dx, dx
          jnz   LAB_0040636f
          mov   esi, 000000006h
          jmp   LAB_0040636f
LAB_0040632c:     test  dx, dx
          jnz   LAB_0040636f
          mov   esi, 000000001h
          jmp   LAB_0040636f
LAB_00406338:     test  dx, dx
          jnz   LAB_0040636f
          mov   esi, 000000004h
          jmp   LAB_0040636f
LAB_00406344:     test  dx, dx
          jnz   LAB_0040636f
          mov   word ptr [eax+04Ah], 00002h
          mov   eax, dword ptr [playerActor]    ; <c72c>
          mov   esi, 00000000Dh
          mov   cx, word ptr [eax+048h]
          cmp   cx, 000000004h
          jle   LAB_0040636f
          add   ecx, 0FFFFFFFCh
          mov   word ptr [eax+048h], cx
LAB_0040636a:     mov   eax, dword ptr [playerActor]    ; <c72c>
LAB_0040636f:     mov   ecx, dword ptr [eax+01Ch]
          pop   edi
          cmp   esi, ecx
          jz    LAB_004063a3
          mov   edx, esi
          mov   ecx, eax
          call  @setActorFrameNo@8
          mov   eax, dword ptr [redrawRequired] ; <c610>
          test  eax, eax
          jz    LAB_004063a3
          mov   ecx, dword ptr [mainWindowDC]   ; <c63c>
          mov   edx, offset windowClientRect.left       ; <c6b0>
          call  @drawWindow@8
          mov   dword ptr [redrawRequired], 000000000h  ; <c610>
LAB_004063a3:     pop   esi
          ret
LAB_004063a5:
          db 08Dh
          db 049h
          db 000h
LAB_004063a8:
DAT_004063a8  dword offset LAB_0040619e
DAT_004063ac  dword offset LAB_00406188
DAT_004063b0  dword offset LAB_004061ab
DAT_004063b4  dword offset LAB_00406198
DAT_004063b8  dword offset LAB_004061b1
LAB_004063bc:
          db 000h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 001h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 002h
          db 003h
          db 08Bh
          db 0FFh
LAB_00406424:
DAT_00406424  dword offset LAB_00406320
DAT_00406428  dword offset LAB_00406338
DAT_0040642c  dword offset LAB_0040632c
DAT_00406430  dword offset LAB_00406314
DAT_00406434  dword offset LAB_004061f3
DAT_00406438  dword offset LAB_004062b1
DAT_0040643c  dword offset LAB_00406236
DAT_00406440  dword offset LAB_00406274
DAT_00406444  dword offset LAB_00406344
DAT_00406448  dword offset LAB_0040636f
LAB_0040644c:
          db 000h
          db 001h
          db 002h
          db 003h
          db 004h
          db 005h
          db 006h
          db 007h
          db 009h
          db 009h
          db 009h
          db 009h
          db 008h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 009h
          db 008h
          db 002h
          db 007h
          db 001h
          db 004h
          db 009h
          db 006h
          db 003h
          db 005h
          db 000h
          db 08Dh
          db 049h
          db 000h
LAB_00406498:
DAT_00406498  dword offset LAB_00406293
DAT_0040649c  dword offset LAB_0040636f
DAT_004064a0  dword offset LAB_0040636f
DAT_004064a4  dword offset LAB_0040636f
DAT_004064a8  dword offset LAB_0040636f
DAT_004064ac  dword offset LAB_004062ce
DAT_004064b0  dword offset LAB_004062c4
DAT_004064b4  dword offset LAB_0040629d
DAT_004064b8  dword offset LAB_004062a7
LAB_004064bc:
DAT_004064bc  dword offset LAB_004062ec
DAT_004064c0  dword offset LAB_0040636f
DAT_004064c4  dword offset LAB_0040636f
DAT_004064c8  dword offset LAB_00406300
DAT_004064cc  dword offset LAB_004062ec
DAT_004064d0  dword offset LAB_00406300
DAT_004064d4  dword offset LAB_0040636f
DAT_004064d8  dword offset LAB_0040636f
DAT_004064dc  dword offset LAB_0040636f
DAT_004064e0  dword offset LAB_004062ec
DAT_004064e4  dword offset LAB_004062c4
DAT_004064e8  dword offset LAB_004062d8
DAT_004064ec  dword offset LAB_004062e2
DAT_004064f0  dword offset LAB_0040636f
DAT_004064f4  dword offset LAB_0040636f
DAT_004064f8  dword offset LAB_00406293
DAT_004064fc  dword offset LAB_004062ce
@handleKeydownMessage@4 endp