.386
.model flat
.code
include structs.inc
include data_extern.inc
include c_funcs.inc
assume fs:nothing
option noscoped
COMMENT ~
_timerUpdateFunc proc
          call  dword ptr [__imp__GetTickCount@0]       ; <GetTickCount>
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          mov   edx, eax
          sub   edx, ecx
          mov   dword ptr [prevTickCount], ecx  ; <c708>
          mov   dword ptr [timerFrameDurationInMillis], edx     ; <c5f4>
          mov   dword ptr [currentTickCount], eax       ; <c698>
          call  _updateGameState
          mov   ecx, dword ptr [mainWindowDC]   ; <c63c>
          mov   edx, offset windowClientRect.left       ; <c6b0>
          call  @drawWindow@8
          mov   eax, dword ptr [currentTickCount]       ; <c698>
          mov   edx, dword ptr [statusWindowLastUpdateTime]     ; <c5dc>
          sub   eax, edx
          mov   dword ptr [redrawRequired], 000000001h  ; <c610>
          cmp   eax, 000000147h
          jle   LAB_0040105f
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          jmp   @formatAndPrintStatusStrings@4
LAB_0040105f:     ret
_timerUpdateFunc endp
~

@drawWindow@8 proc
          sub   esp, 000000008h
          push  ebx
          push  ebp
          mov   ebp, edx
          push  esi
          test  ecx, ecx
          push  edi
          mov   dword ptr [esp+010h], ebp
          mov   dword ptr [esp+014h], ecx
          jnz   LAB_00401084
          mov   edx, 0000004F8h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401084:     test  ebp, ebp
          jnz   LAB_00401097
          mov   edx, 0000004F9h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401097:     mov   esi, dword ptr [actorListPtr]   ; <c618>
          test  esi, esi
          jz    LAB_00401125
          mov   ebx, 0FFFFFFFEh
LAB_004010aa:     test  byte ptr [esi+04Ch], 00Bh
          jnz   LAB_00401115
          mov   edi, dword ptr [esi+004h]
          test  edi, edi
          jz    LAB_00401115
          mov   eax, dword ptr [edi+04Ch]
          test  al, 001h
          jz    LAB_00401115
          test  al, 002h
          jz    LAB_00401115
          mov   cx, word ptr [esi+010h]
          cmp   cx, word ptr [edi+010h]
          jnz   LAB_00401115
          test  al, 004h
          jz    LAB_004010d5
          lea   ebp, dword ptr [edi+020h]
          jmp   LAB_004010de
LAB_004010d5:     mov   ecx, edi
          call  @updateActorSpriteRect@4
          mov   ebp, eax
LAB_004010de:     test  byte ptr [esi+04Ch], 004h
          jz    LAB_004010e9
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_004010f0
LAB_004010e9:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_004010f0:     mov   edx, ebp
          mov   ecx, eax
          call  @areRectanglesEqual@8
          test  eax, eax
          jz    LAB_00401115
          mov   ecx, dword ptr [esi+04Ch]
          or    ecx, 000000001h
          mov   dword ptr [esi+04Ch], ecx
          mov   eax, dword ptr [edi+04Ch]
          and   eax, ebx
          mov   ecx, edi
          mov   dword ptr [edi+04Ch], eax
          call  @actorSetFlag8IfFlag1IsUnset@4
LAB_00401115:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_004010aa
          mov   ebp, dword ptr [esp+010h]
          mov   esi, dword ptr [actorListPtr]   ; <c618>
LAB_00401125:     test  esi, esi
          mov   bl, 010h
          jz    LAB_00401190
LAB_0040112b:     mov   eax, dword ptr [esi+04Ch]
          test  al, 008h
          jz    LAB_00401139
          and   al, 0EFh
          mov   dword ptr [esi+04Ch], eax
          jmp   LAB_0040118a
LAB_00401139:     test  al, 004h
          jz    LAB_00401142
          lea   edi, dword ptr [esi+020h]
          jmp   LAB_0040114b
LAB_00401142:     mov   ecx, esi
          call  @updateActorSpriteRect@4
          mov   edi, eax
LAB_0040114b:     mov   edx, ebp
          mov   ecx, edi
          call  @doRectsOverlap@8
          mov   edx, dword ptr [esi+04Ch]
          and   eax, 000000001h
          shl   eax, 004h
          and   edx, 0FFFFFFEFh
          or    eax, edx
          test  bl, al
          mov   dword ptr [esi+04Ch], eax
          jz    LAB_0040118a
          mov   ecx, dword ptr [edi]
          lea   eax, dword ptr [esi+030h]
          mov   dword ptr [esi+030h], ecx
          mov   edx, dword ptr [edi+004h]
          mov   dword ptr [eax+004h], edx
          mov   ecx, dword ptr [edi+008h]
          mov   dword ptr [eax+008h], ecx
          mov   edx, dword ptr [edi+00Ch]
          mov   dword ptr [esi+008h], 000000000h
          mov   dword ptr [eax+00Ch], edx
LAB_0040118a:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_0040112b
LAB_00401190:     mov   esi, dword ptr [actorListPtr]   ; <c618>
          test  esi, esi
          mov   edi, esi
          jz    LAB_00401212
LAB_0040119c:     test  byte ptr [edi+04Ch], bl
          jz    LAB_004011f2
          mov   esi, dword ptr [edi+004h]
          lea   ebp, dword ptr [edi+030h]
          test  esi, esi
          jz    LAB_004011c7
          test  byte ptr [esi+04Ch], bl
          jz    LAB_004011c7
          lea   edx, dword ptr [esi+030h]
          mov   ecx, ebp
          call  @doRectsOverlap@8
          test  eax, eax
          jz    LAB_004011c7
LAB_004011be:     mov   edx, esi
          mov   ecx, edi
          call  @actorClearFlag10@8
LAB_004011c7:     mov   esi, dword ptr [actorListPtr]   ; <c618>
LAB_004011cd:     test  esi, esi
          jz    LAB_004011ec
          cmp   edi, esi
          jz    LAB_004011ec
          test  byte ptr [esi+04Ch], bl
          jz    LAB_004011e8
          lea   edx, dword ptr [esi+030h]
          mov   ecx, ebp
          call  @doRectsOverlap@8
          test  eax, eax
          jnz   LAB_004011be
LAB_004011e8:     mov   esi, dword ptr [esi]
          jmp   LAB_004011cd
LAB_004011ec:     mov   esi, dword ptr [actorListPtr]   ; <c618>
LAB_004011f2:     mov   edi, dword ptr [edi]
          test  edi, edi
          jnz   LAB_0040119c
          test  esi, esi
          jz    LAB_00401212
LAB_004011fc:     test  byte ptr [esi+04Ch], bl
          jz    LAB_0040120c
          mov   ecx, dword ptr [esp+014h]
          mov   edx, esi
          call  @drawActor@8
LAB_0040120c:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_004011fc
LAB_00401212:     mov   esi, dword ptr [actorListPtr]   ; <c618>
          test  esi, esi
          jz    LAB_0040122f
LAB_0040121c:     test  byte ptr [esi+04Ch], 002h
          jz    LAB_00401229
          mov   ecx, esi
          call  @actorSetFlag8IfFlag1IsUnset@4
LAB_00401229:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_0040121c
LAB_0040122f:     call  _removeFlag8ActorsFromList
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000008h
          ret
LAB_0040123c:
          db 090h
          db 090h
          db 090h
          db 090h
@drawWindow@8 endp

COMMENT ~
@assertFailed@8 proc
          sub   esp, 000000020h
          lea   eax, dword ptr [esp+000h]
          push  edx
          push  ecx
          push  offset s_assertErrorFormat      ; <c0bc>
          push  eax
          call  dword ptr [__imp__wsprintfA]    ; <wsprintfA>
          add   esp, 000000010h
          lea   edx, dword ptr [esp+000h]
          mov   ecx, offset s_Assertion_Failed_0040c0a8 ; <c0a8>
          call  @assertFailedDialog@8
          call  _togglePausedState
          add   esp, 000000020h
          ret
LAB_0040126f:
          db 090h
@assertFailed@8 endp
~

COMMENT ~
@assertFailedDialog@8 proc
          push  000000031h
          push  ecx
          push  edx
          push  000000000h
          call  dword ptr [__imp__MessageBoxA@16]       ; <MessageBoxA>
          cmp   eax, 000000002h
          jnz   LAB_0040128d
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  eax
          call  dword ptr [__imp__DestroyWindow@4]      ; <DestroyWindow>
LAB_0040128d:     ret
LAB_0040128e:
          db 090h
          db 090h
@assertFailedDialog@8 endp
~

COMMENT ~
@doRectsOverlap@8 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_004012a9
          mov   edx, 000000160h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004012a9:     test  edi, edi
          jnz   LAB_004012bc
          mov   edx, 000000161h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004012bc:     mov   eax, dword ptr [esi+008h]
          mov   ecx, dword ptr [edi]
          cmp   eax, ecx
          jle   LAB_004012ea
          mov   ecx, dword ptr [esi]
          mov   eax, dword ptr [edi+008h]
          cmp   ecx, eax
          jge   LAB_004012ea
          mov   edx, dword ptr [esi+00Ch]
          mov   eax, dword ptr [edi+004h]
          cmp   edx, eax
          jle   LAB_004012ea
          mov   eax, dword ptr [esi+004h]
          mov   ecx, dword ptr [edi+00Ch]
          cmp   eax, ecx
          jge   LAB_004012ea
          pop   edi
          mov   eax, 000000001h
          pop   esi
          ret
LAB_004012ea:     pop   edi
          xor   eax, eax
          pop   esi
          ret
LAB_004012ef:
          db 090h
@doRectsOverlap@8 endp
~

COMMENT ~
@areRectanglesEqual@8 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_00401309
          mov   edx, 00000017Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401309:     test  edi, edi
          jnz   LAB_0040131c
          mov   edx, 00000017Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040131c:     mov   eax, dword ptr [esi+004h]
          mov   ecx, dword ptr [edi+004h]
          cmp   eax, ecx
          jnz   LAB_0040134a
          mov   ecx, dword ptr [esi]
          mov   eax, dword ptr [edi]
          cmp   ecx, eax
          jnz   LAB_0040134a
          mov   edx, dword ptr [esi+008h]
          mov   eax, dword ptr [edi+008h]
          cmp   edx, eax
          jnz   LAB_0040134a
          mov   eax, dword ptr [esi+00Ch]
          mov   ecx, dword ptr [edi+00Ch]
          cmp   eax, ecx
          jnz   LAB_0040134a
          pop   edi
          mov   eax, 000000001h
          pop   esi
          ret
LAB_0040134a:     pop   edi
          xor   eax, eax
          pop   esi
          ret
LAB_0040134f:
          db 090h
@areRectanglesEqual@8 endp
~

COMMENT ~
@actorSetFlag8IfFlag1IsUnset@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_00401366
          mov   edx, 000000361h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401366:     test  byte ptr [esi+04Ch], 001h
          jnz   LAB_00401382
          mov   eax, dword ptr [esi+004h]
          test  eax, eax
          jz    LAB_0040137a
          mov   dword ptr [eax+004h], 000000000h
LAB_0040137a:     mov   eax, dword ptr [esi+04Ch]
          or    al, 008h
          mov   dword ptr [esi+04Ch], eax
LAB_00401382:     pop   esi
          ret
LAB_00401384:
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
@actorSetFlag8IfFlag1IsUnset@4 endp
~

COMMENT ~
_removeFlag8ActorsFromList proc
          push  ebp
          push  esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          xor   ebp, ebp
          push  edi
          cmp   esi, ebp
          mov   edi, offset actorListPtr        ; <c618>
          jz    LAB_00401401
LAB_004013a4:     test  byte ptr [esi+04Ch], 008h
          jz    LAB_004013f9
          mov   eax, dword ptr [esi+00Ch]
          cmp   eax, ebp
          jz    LAB_004013c9
          cmp   dword ptr [eax], esi
          jz    LAB_004013c4
          mov   edx, 000000376h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004013c4:     mov   eax, dword ptr [esi+00Ch]
          mov   dword ptr [eax], ebp
LAB_004013c9:     cmp   esi, dword ptr [playerActor]    ; <c72c>
          jnz   LAB_004013d7
          mov   dword ptr [playerActor], ebp    ; <c72c>
LAB_004013d7:     cmp   esi, dword ptr [playerActorPtrMaybe_1]  ; <c64c>
          jnz   LAB_004013e5
          mov   dword ptr [playerActorPtrMaybe_1], ebp  ; <c64c>
LAB_004013e5:     mov   ecx, dword ptr [esi]
          mov   dword ptr [edi], ecx
          mov   edx, dword ptr [currentFreeActor]       ; <c744>
          mov   dword ptr [esi], edx
          mov   dword ptr [currentFreeActor], esi       ; <c744>
          jmp   LAB_004013fb
LAB_004013f9:     mov   edi, esi
LAB_004013fb:     mov   esi, dword ptr [edi]
          cmp   esi, ebp
          jnz   LAB_004013a4
LAB_00401401:     pop   edi
          pop   esi
          pop   ebp
          ret
LAB_00401405:
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
_removeFlag8ActorsFromList endp
~

COMMENT ~
@updateActorSpriteRect@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          push  edi
          jnz   LAB_00401427
          mov   edx, 0000003A3h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401427:     test  byte ptr [esi+04Ch], 004h
          jz    LAB_0040143c
          mov   edx, 0000003A4h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040143c:     cmp   word ptr [esi+010h], 000000000h
          jnz   LAB_00401452
          mov   edx, 0000003A5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401452:     mov   edx, dword ptr [sprites]        ; <c5f8>
          mov   ecx, dword ptr [esi+014h]
          xor   eax, eax
          mov   ax, word ptr [esi+010h]
          shl   eax, 004h
          add   eax, edx
          cmp   eax, ecx
          jz    LAB_00401479
          mov   edx, 0000003A6h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401479:     mov   cx, word ptr [esi+044h]
          mov   dx, word ptr [esi+042h]
          mov   ax, word ptr [esi+040h]
          lea   edi, dword ptr [esi+020h]
          push  ecx
          push  edx
          mov   edx, dword ptr [esi+014h]
          push  eax
          mov   ecx, edi
          call  @updateRectForSpriteAtLocation@20
          mov   eax, dword ptr [esi+04Ch]
          or    al, 004h
          mov   dword ptr [esi+04Ch], eax
          mov   eax, edi
          pop   edi
          pop   esi
          ret
LAB_004014a2:
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
@updateActorSpriteRect@4 endp
~

@updateRectForSpriteAtLocation@20 proc
          push  ebx
          push  ebp
          push  esi
          push  edi
          mov   edi, edx
          mov   esi, ecx
          test  esi, esi
          mov   bp, word ptr [edi+00Ah]
          mov   bx, word ptr [edi+00Ch]
          jnz   LAB_004014d3
          mov   edx, 00000038Bh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004014d3:     test  edi, edi
          jnz   LAB_004014e6
          mov   edx, 00000038Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004014e6:     mov   ax, word ptr [skierScreenYOffset]       ; <c5fc>
          mov   edi, dword ptr [esp+01Ch]
          sub   ax, word ptr [playerY]  ; <c5f2>
          mov   ecx, dword ptr [esp+018h]
          sub   eax, edi
          movsx edi, bp
          add   ecx, eax
          mov   eax, edi
          cdq
          sub   eax, edx
          mov   edx, dword ptr [skierScreenXOffset]     ; <c704>
          sar   eax, 1h
          sub   edx, eax
          mov   eax, dword ptr [playerX]        ; <c640>
          sub   edx, eax
          mov   eax, dword ptr [esp+014h]
          add   eax, edx
          sub   ecx, ebx
          movsx eax, ax
          mov   dword ptr [esi], eax
          add   eax, edi
          mov   dword ptr [esi+008h], eax
          pop   edi
          movsx ecx, cx
          movsx eax, bx
          add   eax, ecx
          mov   dword ptr [esi+004h], ecx
          mov   dword ptr [esi+00Ch], eax
          pop   esi
          pop   ebp
          pop   ebx
          ret   0000Ch
LAB_0040153f:
          db 090h
@updateRectForSpriteAtLocation@20 endp

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

COMMENT ~
@changeScratchBitmapSize@8 proc
          push  ebx
          push  esi
          mov   esi, ecx
          push  edi
          cmp   si, word ptr [scratchBitmapWidth]       ; <c690>
          mov   edi, edx
          jg    LAB_0040198d
          cmp   di, word ptr [scratchBitmapHeight]      ; <c6e8>
          jle   LAB_00401a3f
LAB_0040198d:     mov   edx, dword ptr [scratchBitmap]  ; <c614>
          mov   eax, esi
          mov   ecx, edi
          and   al, 0C0h
          and   ecx, 0FFFFFFC0h
          add   eax, 000000040h
          add   ecx, 000000040h
          mov   word ptr [scratchBitmapWidth], ax       ; <c690>
          test  edx, edx
          mov   word ptr [scratchBitmapHeight], cx      ; <c6e8>
          jz    LAB_004019de
          mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          push  edx
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          push  eax
          call  dword ptr [__imp__DeleteObject@4]       ; <DeleteObject>
          mov   ax, word ptr [scratchBitmapWidth]       ; <c690>
          mov   cx, word ptr [scratchBitmapHeight]      ; <c6e8>
          mov   dword ptr [scratchBitmap], 000000000h   ; <c614>
LAB_004019de:     mov   ebx, dword ptr [__imp__CreateCompatibleBitmap@12]       ; <CreateCompatibleBitmap>
          movsx ecx, cx
          movsx edx, ax
          mov   eax, dword ptr [mainWindowDC]   ; <c63c>
          push  ecx
          push  edx
          push  eax
          call  ebx
          test  eax, eax
          jnz   LAB_00401a2c
LAB_004019f8:     cmp   word ptr [scratchBitmapWidth], si       ; <c690>
          jnz   LAB_00401a0a
          cmp   word ptr [scratchBitmapHeight], di      ; <c6e8>
          jz    LAB_00401a48
LAB_00401a0a:     mov   eax, dword ptr [mainWindowDC]   ; <c63c>
          mov   word ptr [scratchBitmapWidth], si       ; <c690>
          movsx ecx, di
          movsx edx, si
          push  ecx
          push  edx
          push  eax
          mov   word ptr [scratchBitmapHeight], di      ; <c6e8>
          call  ebx
          test  eax, eax
          jz    LAB_004019f8
LAB_00401a2c:     mov   ecx, dword ptr [bitmapSourceDC] ; <c5ec>
          push  eax
          push  ecx
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          mov   dword ptr [scratchBitmap], eax  ; <c614>
LAB_00401a3f:     pop   edi
          pop   esi
          mov   eax, 000000001h
          pop   ebx
          ret
LAB_00401a48:     pop   edi
          pop   esi
          mov   word ptr [scratchBitmapHeight], 00000h  ; <c6e8>
          mov   word ptr [scratchBitmapWidth], 00000h   ; <c690>
          xor   eax, eax
          pop   ebx
          ret
@changeScratchBitmapSize@8 endp
~

COMMENT ~
@actorClearFlag10@8 proc
          push  ebx
          push  ebp
          push  esi
          push  edi
          mov   edi, ecx
          mov   ebp, edx
          test  edi, edi
          mov   esi, edi
          jnz   LAB_00401a7d
          mov   edx, 0000004E4h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401a7d:     test  ebp, ebp
          jnz   LAB_00401a90
          mov   edx, 0000004E5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401a90:     mov   al, byte ptr [edi+04Ch]
          mov   bl, 010h
          test  bl, al
          jnz   LAB_00401aa8
          mov   edx, 0000004E6h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401aa8:     test  byte ptr [ebp+04Ch], bl
          jnz   LAB_00401abc
          mov   edx, 0000004E7h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401abc:     cmp   edi, ebp
          jnz   LAB_00401acf
          mov   edx, 0000004E8h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401acf:     mov   ecx, dword ptr [edi+008h]
          lea   eax, dword ptr [edi+008h]
          test  ecx, ecx
          jz    LAB_00401af9
LAB_00401ad9:     mov   esi, dword ptr [eax]
          test  byte ptr [esi+04Ch], bl
          jz    LAB_00401aef
          mov   edx, 0000004ECh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00401aef:     mov   ecx, dword ptr [esi+008h]
          lea   eax, dword ptr [esi+008h]
          test  ecx, ecx
          jnz   LAB_00401ad9
LAB_00401af9:     lea   edx, dword ptr [ebp+030h]
          lea   ecx, dword ptr [edi+030h]
          mov   dword ptr [esi+008h], ebp
          call  @enlargeRect@8
          mov   eax, dword ptr [ebp+04Ch]
          and   al, 0EFh
          pop   edi
          mov   dword ptr [ebp+04Ch], eax
          pop   esi
          pop   ebp
          pop   ebx
          ret
LAB_00401b14:
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
@actorClearFlag10@8 endp
~

COMMENT ~
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
~

@formatAndPrintStatusStrings@4 proc
          sub   esp, 000000018h
          mov   eax, dword ptr [playerActor]    ; <c72c>
          push  ebx
          push  ebp
          push  esi
          mov   si, word ptr [statusWindowLabelWidth]   ; <c66e>
          push  edi
          add   si, 000000002h
          xor   ebp, ebp
          xor   edi, edi
          mov   ebx, ecx
          test  eax, eax
          mov   dword ptr [esp+010h], 000000002h
          jz    LAB_00401c12
          mov   ecx, dword ptr [timerFrameDurationInMillis]     ; <c5f4>
          test  ecx, ecx
          jz    LAB_00401bd2
          movsx eax, word ptr [eax+048h]
          shl   ecx, 004h
          lea   eax, dword ptr [eax+eax*4]
          lea   eax, dword ptr [eax+eax*4]
          lea   eax, dword ptr [eax+eax*4]
          shl   eax, 003h
          cdq
          idiv  ecx
          mov   ebp, eax
          mov   eax, dword ptr [playerActor]    ; <c72c>
          jmp   LAB_00401bd4
LAB_00401bd2:     xor   ebp, ebp
LAB_00401bd4:     mov   di, word ptr [eax+042h]
          mov   eax, dword ptr [isSsGameMode]   ; <c95c>
          test  eax, eax
          jz    LAB_00401bec
          mov   eax, 0000021C0h
          sub   eax, edi
          mov   edi, eax
          jmp   LAB_00401c12
LAB_00401bec:     mov   eax, dword ptr [isFsGameMode]   ; <c954>
          test  eax, eax
          jz    LAB_00401c00
          mov   ecx, 000004100h
          sub   ecx, edi
          mov   edi, ecx
          jmp   LAB_00401c12
LAB_00401c00:     mov   eax, dword ptr [isGsGameMode]   ; <c958>
          test  eax, eax
          jz    LAB_00401c12
          mov   edx, 000004100h
          sub   edx, edi
          mov   edi, edx
LAB_00401c12:     mov   ecx, dword ptr [elapsedTime]    ; <c944>
          lea   edx, dword ptr [esp+014h]
          call  @formatElapsedTime@8
          and   eax, 00000FFFFh
          lea   edx, dword ptr [esp+014h]
          push  eax
          lea   eax, dword ptr [esp+014h]
          push  eax
          push  esi
          mov   ecx, ebx
          call  @drawText@20
          movsx eax, di
          cdq
          and   edx, 00000000Fh
          add   eax, edx
          sar   eax, 004h
          movsx ecx, ax
          push  ecx
          mov   ecx, 00000000Ch
          call  @getCachedString@4
          mov   edi, dword ptr [__imp__wsprintfA]       ; <wsprintfA>
          lea   edx, dword ptr [esp+018h]
          push  eax
          push  edx
          call  edi
          add   esp, 00000000Ch
          lea   edx, dword ptr [esp+014h]
          mov   ecx, ebx
          push  eax
          lea   eax, dword ptr [esp+014h]
          push  eax
          push  esi
          call  @drawText@20
          movsx ecx, bp
          push  ecx
          mov   ecx, 00000000Dh
          call  @getCachedString@4
          lea   edx, dword ptr [esp+018h]
          push  eax
          push  edx
          call  edi
          add   esp, 00000000Ch
          lea   edx, dword ptr [esp+014h]
          mov   ecx, ebx
          push  eax
          lea   eax, dword ptr [esp+014h]
          push  eax
          push  esi
          call  @drawText@20
          mov   ecx, dword ptr [stylePoints]    ; <c6a8>
          push  ecx
          mov   ecx, 00000000Eh
          call  @getCachedString@4
          lea   edx, dword ptr [esp+018h]
          push  eax
          push  edx
          call  edi
          add   esp, 00000000Ch
          lea   edx, dword ptr [esp+014h]
          mov   ecx, ebx
          push  eax
          lea   eax, dword ptr [esp+014h]
          push  eax
          push  esi
          call  @drawText@20
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          pop   edi
          pop   esi
          pop   ebp
          mov   dword ptr [statusWindowLastUpdateTime], ecx     ; <c5dc>
          pop   ebx
          add   esp, 000000018h
          ret
LAB_00401ce2:
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
@formatAndPrintStatusStrings@4 endp

COMMENT ~
@getCachedString@4 proc
          mov   eax, dword ptr [stringCache]    ; <c674>
          sub   esp, 000000100h
          push  esi
          mov   esi, ecx
          cmp   dword ptr [eax+esi*4], 000000000h
          jnz   LAB_00401d5a
          mov   edx, dword ptr [skiFreeHInstance]       ; <c61c>
          lea   ecx, dword ptr [esp+004h]
          push  0000000FFh
          push  ecx
          push  esi
          push  edx
          call  dword ptr [__imp__LoadStringA@16]       ; <LoadStringA>
          mov   byte ptr [esp+eax*1+004h], 000h
          inc   eax
          push  eax
          push  000000000h
          call  dword ptr [__imp__LocalAlloc@8] ; <LocalAlloc>
          mov   ecx, dword ptr [stringCache]    ; <c674>
          mov   dword ptr [ecx+esi*4], eax
          mov   edx, dword ptr [stringCache]    ; <c674>
          mov   eax, dword ptr [edx+esi*4]
          test  eax, eax
          jnz   LAB_00401d4e
          mov   eax, offset s_out_o_memory      ; <c0c8>
          pop   esi
          add   esp, 000000100h
          ret
LAB_00401d4e:     lea   ecx, dword ptr [esp+004h]
          push  ecx
          push  eax
          call  dword ptr [__imp__lstrcpyA@8]   ; <lstrcpyA>
LAB_00401d5a:     mov   edx, dword ptr [stringCache]    ; <c674>
          mov   eax, dword ptr [edx+esi*4]
          pop   esi
          add   esp, 000000100h
          ret
LAB_00401d6b:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@getCachedString@4 endp
~

COMMENT ~
@formatElapsedTime@8 proc
          push  ebx
          mov   ebx, edx
          mov   eax, ecx
          push  esi
          cdq
          mov   esi, 0000003E8h
          push  edi
          idiv  esi
          mov   eax, 066666667h
          mov   edi, 00000003Ch
          and   edx, 00000FFFFh
          imul  edx
          sar   edx, 002h
          mov   eax, edx
          shr   eax, 01Fh
          add   edx, eax
          mov   eax, 010624DD3h
          mov   esi, edx
          imul  ecx
          sar   edx, 006h
          mov   ecx, edx
          and   esi, 00000FFFFh
          shr   ecx, 01Fh
          add   edx, ecx
          push  esi
          mov   ecx, edx
          mov   esi, 00000003Ch
          mov   eax, ecx
          cdq
          idiv  edi
          mov   eax, 088888889h
          mov   edi, edx
          imul  ecx
          add   edx, ecx
          and   edi, 00000FFFFh
          sar   edx, 005h
          mov   eax, edx
          push  edi
          shr   eax, 01Fh
          add   edx, eax
          mov   ecx, edx
          mov   eax, ecx
          cdq
          idiv  esi
          mov   eax, 088888889h
          and   edx, 00000FFFFh
          push  edx
          imul  ecx
          add   edx, ecx
          sar   edx, 005h
          mov   ecx, edx
          shr   ecx, 01Fh
          add   edx, ecx
          mov   ecx, 00000000Bh
          and   edx, 00000FFFFh
          push  edx
          call  @getCachedString@4
          push  eax
          push  ebx
          call  dword ptr [__imp__wsprintfA]    ; <wsprintfA>
          add   esp, 000000018h
          pop   edi
          pop   esi
          pop   ebx
          ret
LAB_00401e1e:
          db 090h
          db 090h
@formatElapsedTime@8 endp
~

COMMENT ~
@drawText@20 proc
          mov   eax, dword ptr [esp+00Ch]
          push  esi
          mov   esi, dword ptr [esp+00Ch]
          push  eax
          movsx eax, word ptr [esp+00Ch]
          push  edx
          movsx edx, word ptr [esi]
          push  edx
          push  eax
          push  ecx
          call  dword ptr [__imp__TextOutA@20]  ; <TextOutA>
          mov   cx, word ptr [textLineHeight]   ; <c668>
          add   word ptr [esi], cx
          pop   esi
          ret   0000Ch
LAB_00401e4a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@drawText@20 endp
~

_updateGameState proc
          mov   ax, word ptr [playerX]  ; <c640>
          mov   cx, word ptr [playerY]  ; <c5f2>
          sub   word ptr [DAT_0040c714], ax     ; <c714>
          sub   word ptr [DAT_0040c5d8], cx     ; <c5d8>
          push  ebx
          push  esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          push  edi
          test  esi, esi
          jz    LAB_00401ef4
          mov   edi, 0FFFFFFDFh
          mov   ebx, 00000000Bh
LAB_00401e82:     test  byte ptr [esi+04Ch], 00Ah
          jnz   LAB_00401eee
          mov   ecx, dword ptr [esi+04Ch]
          mov   eax, dword ptr [esi+00Ch]
          and   ecx, edi
          test  eax, eax
          mov   dword ptr [esi+04Ch], ecx
          jnz   LAB_00401ea3
          cmp   dword ptr [esi+018h], ebx
          jge   LAB_00401ea3
          mov   ecx, esi
          call  @updateActor@4
LAB_00401ea3:     mov   eax, dword ptr [esi+04Ch]
          test  al, 001h
          jnz   LAB_00401eee
          cmp   esi, dword ptr [playerActor]    ; <c72c>
          jz    LAB_00401eee
          test  al, 004h
          jz    LAB_00401ebb
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00401ec2
LAB_00401ebb:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00401ec2:     mov   edx, offset windowClientRectWith120Margin.left  ; <c680>
          mov   ecx, eax
          call  @doRectsOverlap@8
          test  eax, eax
          jnz   LAB_00401eee
          mov   edx, dword ptr [esi+014h]
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          movsx eax, word ptr [edx+00Eh]
          sub   ecx, eax
          mov   dword ptr [totalAreaOfActorSprites], ecx        ; <c6fc>
          mov   ecx, esi
          call  @actorSetFlag8IfFlag1IsUnset@4
LAB_00401eee:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00401e82
LAB_00401ef4:     mov   ecx, offset PermObjectList_0040c630.startingObject      ; <c630>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c5e0.startingObject      ; <c5e0>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c658.startingObject      ; <c658>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c738.startingObject      ; <c738>
          call  @FUN_004046e0@4
          mov   ecx, offset PermObjectList_0040c720.startingObject      ; <c720>
          call  @updateAllPermObjectsInList@4
          call  _removeFlag8ActorsFromList
          mov   edi, dword ptr [actorListPtr]   ; <c618>
          test  edi, edi
          jz    LAB_00401fc5
          push  ebp
LAB_00401f3a:     mov   eax, dword ptr [edi+04Ch]
          test  al, 002h
          jnz   LAB_00401fba
          test  al, 004h
          jz    LAB_00401f4a
          lea   ebx, dword ptr [edi+020h]
          jmp   LAB_00401f53
LAB_00401f4a:     mov   ecx, edi
          call  @updateActorSpriteRect@4
          mov   ebx, eax
LAB_00401f53:     mov   ebp, dword ptr [edi+04Ch]
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          shl   ebp, 01Ah
          sar   ebp, 01Fh
          test  esi, esi
          jz    LAB_00401fba
LAB_00401f66:     cmp   edi, esi
          jz    LAB_00401fba
          mov   eax, dword ptr [esi+04Ch]
          test  al, 002h
          jnz   LAB_00401fb4
          test  ebp, ebp
          jnz   LAB_00401f79
          test  al, 020h
          jz    LAB_00401fb4
LAB_00401f79:     test  al, 004h
          jz    LAB_00401f82
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00401f89
LAB_00401f82:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00401f89:     mov   edx, eax
          mov   ecx, ebx
          call  @doRectsOverlap@8
          test  eax, eax
          jz    LAB_00401fb4
          mov   edx, esi
          mov   ecx, edi
          call  @handleActorCollision@8
          test  byte ptr [edi+04Ch], 008h
          jnz   LAB_00401fb4
          test  byte ptr [esi+04Ch], 008h
          jnz   LAB_00401fb4
          mov   edx, edi
          mov   ecx, esi
          call  @handleActorCollision@8
LAB_00401fb4:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00401f66
LAB_00401fba:     mov   edi, dword ptr [edi]
          test  edi, edi
          jnz   LAB_00401f3a
          pop   ebp
LAB_00401fc5:     mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          mov   cx, word ptr [playerX]  ; <c640>
          add   ax, word ptr [playerY]  ; <c5f2>
          add   word ptr [DAT_0040c714], cx     ; <c714>
          pop   edi
          pop   esi
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          pop   ebx
          jle   LAB_0040200f
LAB_00401fef:     mov   ecx, 000000003h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          add   ax, 0FFC4h
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          jg    LAB_00401fef
LAB_0040200f:     cmp   ax, 0FFC4h
          jge   LAB_00402035
LAB_00402015:     mov   ecx, 000000002h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c5d8]     ; <c5d8>
          add   ax, 0003Ch
          cmp   ax, 0FFC4h
          mov   word ptr [DAT_0040c5d8], ax     ; <c5d8>
          jl    LAB_00402015
LAB_00402035:     mov   ax, word ptr [DAT_0040c714]     ; <c714>
          cmp   ax, 0003Ch
          jle   LAB_00402061
LAB_00402041:     mov   ecx, 000000001h
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c714]     ; <c714>
          add   ax, 0FFC4h
          cmp   ax, 0003Ch
          mov   word ptr [DAT_0040c714], ax     ; <c714>
          jg    LAB_00402041
LAB_00402061:     cmp   ax, 0FFC4h
          jge   LAB_00402084
LAB_00402067:     xor   ecx, ecx
          call  @addRandomActor@4
          mov   ax, word ptr [DAT_0040c714]     ; <c714>
          add   ax, 0003Ch
          cmp   ax, 0FFC4h
          mov   word ptr [DAT_0040c714], ax     ; <c714>
          jl    LAB_00402067
LAB_00402084:     mov   ecx, 00000029Ah
          call  @random@4
          test  ax, ax
          jnz   LAB_004020ae
          mov   edx, 00000001Fh
          mov   ecx, 000000003h
          call  @addActorOfType@8
          mov   ecx, eax
          mov   edx, 000000002h
          jmp   @updateActorWithOffscreenStartingPosition@8
LAB_004020ae:     ret
LAB_004020af:
          db 090h
_updateGameState endp

COMMENT ~
@random@4 proc
          push  esi
          mov   si, cx
          call  _rand
          movsx eax, ax
          movsx ecx, si
          cdq
          idiv  ecx
          pop   esi
          mov   ax, dx
          ret
LAB_004020c7:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@random@4 endp
~

COMMENT ~
@addActorOfType@8 proc
          push  ebx
          push  esi
          push  edi
          mov   ebx, edx
          mov   edi, ecx
          call  _getFreeActor
          mov   esi, eax
          test  esi, esi
          jz    LAB_00402118
          test  edi, edi
          jge   LAB_004020f5
          mov   edx, 00000056Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004020f5:     cmp   edi, 000000012h
          jl    LAB_00402109
          mov   edx, 00000056Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402109:     mov   dword ptr [esi+018h], edi
          mov   ecx, esi
          pop   edi
          mov   edx, ebx
          pop   esi
          pop   ebx
          jmp   @setActorFrameNo@8
LAB_00402118:     mov   eax, esi
          pop   edi
          pop   esi
          pop   ebx
          ret
LAB_0040211e:
          db 090h
          db 090h
@addActorOfType@8 endp
~

COMMENT ~
@setActorFrameNo@8 proc
          push  esi
          push  edi
          mov   edi, ecx
          mov   esi, edx
          test  edi, edi
          jnz   LAB_00402139
          mov   edx, 00000043Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402139:     cmp   esi, 000000040h
          jl    LAB_0040214d
          mov   edx, 00000043Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040214d:     cmp   dword ptr [edi+01Ch], esi
          jz    LAB_0040217b
          cmp   esi, 000000040h
          jb    LAB_00402166
          mov   edx, 000000440h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402166:     mov   dx, word ptr [esi*2+actorFrameToSpriteTbl]      ; <a1ac>
          mov   ecx, edi
          call  @actorSetSpriteIdx@8
          mov   dword ptr [eax+01Ch], esi
          pop   edi
          pop   esi
          ret
LAB_0040217b:     mov   eax, edi
          pop   edi
          pop   esi
          ret
@setActorFrameNo@8 endp
~

COMMENT ~
@actorSetSpriteIdx@8 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_00402199
          mov   edx, 0000003D3h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402199:     cmp   di, word ptr [esi+010h]
          jz    LAB_00402213
          mov   eax, dword ptr [esi+014h]
          mov   edx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          movsx ecx, word ptr [eax+00Eh]
          sub   edx, ecx
          mov   dword ptr [totalAreaOfActorSprites], edx        ; <c6fc>
          mov   al, byte ptr [esi+04Ch]
          test  al, 001h
          jz    LAB_004021c4
          mov   ecx, esi
          call  @duplicateAndLinkActor@4
          mov   esi, eax
LAB_004021c4:     mov   edx, edi
          mov   word ptr [esi+010h], di
          mov   eax, dword ptr [sprites]        ; <c5f8>
          and   edx, 00000FFFFh
          shl   edx, 004h
          add   eax, edx
          mov   dword ptr [esi+014h], eax
          mov   edx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          movsx ecx, word ptr [eax+00Eh]
          add   edx, ecx
          mov   ecx, edi
          mov   dword ptr [totalAreaOfActorSprites], edx        ; <c6fc>
          mov   edx, dword ptr [esi+04Ch]
          and   edx, 0FFFFFFFBh
          or    edx, 000000020h
          mov   dword ptr [esi+04Ch], edx
          call  @isSlowTile@4
          mov   ecx, dword ptr [esi+04Ch]
          and   eax, 000000001h
          shl   eax, 006h
          and   ecx, 0FFFFFFBFh
          or    eax, ecx
          mov   dword ptr [esi+04Ch], eax
LAB_00402213:     mov   eax, esi
          pop   edi
          pop   esi
          ret
LAB_00402218:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@actorSetSpriteIdx@8 endp
~

COMMENT ~
@duplicateAndLinkActor@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_00402236
          mov   edx, 0000003B3h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402236:     test  byte ptr [esi+04Ch], 001h
          jnz   LAB_0040224b
          mov   edx, 0000003B5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040224b:     mov   edx, 000000001h
          mov   ecx, esi
          call  @addActor@8
          test  eax, eax
          mov   dword ptr [esi+004h], eax
          jz    LAB_00402272
          mov   ecx, dword ptr [eax+04Ch]
          mov   dword ptr [eax+004h], esi
          or    ecx, 000000002h
          mov   dword ptr [eax+04Ch], ecx
          mov   eax, dword ptr [esi+04Ch]
          and   al, 0FEh
          mov   dword ptr [esi+04Ch], eax
LAB_00402272:     mov   eax, esi
          pop   esi
          ret
LAB_00402276:
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
@duplicateAndLinkActor@4 endp
~

COMMENT ~
@addActor@8 proc
          push  ecx
          push  ebx
          mov   ebx, dword ptr [currentFreeActor]       ; <c744>
          push  ebp
          mov   ebp, ecx
          test  ebp, ebp
          mov   dword ptr [esp+008h], edx
          jnz   LAB_004022a2
          mov   edx, 000000348h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004022a2:     test  ebx, ebx
          jz    LAB_004022ed
          mov   eax, dword ptr [ebx]
          push  esi
          push  edi
          mov   ecx, 000000014h
          mov   esi, ebp
          mov   edi, ebx
          mov   dword ptr [currentFreeActor], eax       ; <c744>
          mov   eax, dword ptr [esp+010h]
          rep movsd     [esi], es:[edi]
          pop   edi
          mov   dword ptr [ebx+00Ch], 000000000h
          test  eax, eax
          pop   esi
          jz    LAB_004022d9
          mov   ecx, dword ptr [ebp+000h]
          mov   eax, ebx
          mov   dword ptr [ebx], ecx
          mov   dword ptr [ebp+000h], ebx
          pop   ebp
          pop   ebx
          pop   ecx
          ret
LAB_004022d9:     mov   edx, dword ptr [actorListPtr]   ; <c618>
          mov   eax, ebx
          mov   dword ptr [ebx], edx
          mov   dword ptr [actorListPtr], ebx   ; <c618>
          pop   ebp
          pop   ebx
          pop   ecx
          ret
LAB_004022ed:     mov   edx, 000000359h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          mov   eax, ebx
          pop   ebp
          pop   ebx
          pop   ecx
          ret
LAB_00402302:
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
@addActor@8 endp
~

COMMENT ~
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
~

COMMENT ~
_getFreeActor proc
          mov   eax, dword ptr [sprites]        ; <c5f8>
          xor   edx, edx
          mov   dword ptr [blankTemplateActor.spritePtr], eax   ; <c044>
          mov   ecx, offset blankTemplateActor.next     ; <c030>
          jmp   @addActor@8
LAB_00402346:
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
_getFreeActor endp
~

COMMENT ~
@updateActorWithOffscreenStartingPosition@8 proc
          sub   esp, 000000008h
          mov   eax, edx
          push  esi
          mov   esi, ecx
          test  esi, esi
          jz    LAB_00402383
          lea   ecx, dword ptr [esp+004h]
          lea   edx, dword ptr [esp+008h]
          push  ecx
          mov   ecx, eax
          call  @getRandomOffscreenStartingPosition@12
          mov   ecx, esi
          mov   edx, dword ptr [esp+004h]
          push  000000000h
          push  edx
          mov   edx, dword ptr [esp+010h]
          call  @updateActorPositionMaybe@16
          pop   esi
          add   esp, 000000008h
          ret
LAB_00402383:     mov   eax, esi
          pop   esi
          add   esp, 000000008h
          ret
LAB_0040238a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorWithOffscreenStartingPosition@8 endp
~

COMMENT ~
@updateActorPositionMaybe@16 proc
          push  ecx
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          mov   ebp, edx
          push  edi
          cmp   word ptr [esi+040h], bp
          jnz   LAB_004023ae
          mov   ax, word ptr [esi+042h]
          cmp   ax, word ptr [esp+018h]
          jnz   LAB_004023ae
          xor   edi, edi
          jmp   LAB_004023b3
LAB_004023ae:     mov   edi, 000000001h
LAB_004023b3:     mov   dx, word ptr [esi+044h]
          xor   ecx, ecx
          cmp   dx, word ptr [esp+01Ch]
          setnz cl
          mov   dword ptr [esp+010h], ecx
          mov   ecx, dword ptr [playerActorPtrMaybe_1]  ; <c64c>
          xor   ebx, ebx
          cmp   esi, ecx
          setz  bl
          test  esi, esi
          jnz   LAB_004023e5
          mov   edx, 00000040Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004023e5:     test  ebx, ebx
          jz    LAB_004023f8
          test  edi, edi
          jz    LAB_004023fc
          mov   edx, dword ptr [esp+018h]
          mov   ecx, ebp
          call  @updateActorRectsAfterPlayerMove@8
LAB_004023f8:     test  edi, edi
          jnz   LAB_00402404
LAB_004023fc:     mov   eax, dword ptr [esp+010h]
          test  eax, eax
          jz    LAB_0040245e
LAB_00402404:     mov   eax, dword ptr [esi+04Ch]
          mov   edi, eax
          shl   edi, 01Dh
          sar   edi, 01Fh
          test  al, 001h
          jz    LAB_0040241c
          mov   ecx, esi
          call  @duplicateAndLinkActor@4
          mov   esi, eax
LAB_0040241c:     test  edi, edi
          jz    LAB_00402433
          test  ebx, ebx
          jz    LAB_00402433
          mov   eax, dword ptr [esp+010h]
          test  eax, eax
          jnz   LAB_00402433
          mov   eax, 000000001h
          jmp   LAB_00402435
LAB_00402433:     xor   eax, eax
LAB_00402435:     mov   cx, word ptr [esp+018h]
          mov   dx, word ptr [esp+01Ch]
          and   eax, 000000001h
          mov   word ptr [esi+042h], cx
          mov   ecx, dword ptr [esi+04Ch]
          or    al, 008h
          shl   eax, 002h
          and   ecx, 0FFFFFFFBh
          mov   word ptr [esi+040h], bp
          or    eax, ecx
          mov   word ptr [esi+044h], dx
          mov   dword ptr [esi+04Ch], eax
LAB_0040245e:     mov   eax, esi
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          pop   ecx
          ret   00008h
LAB_00402468:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorPositionMaybe@16 endp
~

COMMENT ~
@updateActorRectsAfterPlayerMove@8 proc
          push  ecx
          push  ebx
          push  ebp
          mov   bp, dx
          push  esi
          mov   esi, dword ptr [playerX]        ; <c640>
          mov   edx, ecx
          push  edi
          mov   edi, edx
          sub   edi, esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          mov   bx, bp
          mov   dword ptr [esp+010h], edx
          sub   bx, word ptr [playerY]  ; <c5f2>
          test  esi, esi
          jz    LAB_004024da
LAB_0040249c:     cmp   esi, dword ptr [playerActorPtrMaybe_1]  ; <c64c>
          jz    LAB_004024d4
          mov   eax, dword ptr [esi+04Ch]
          test  al, 004h
          jz    LAB_004024d4
          test  al, 002h
          jnz   LAB_004024d4
          test  al, 001h
          jz    LAB_004024c0
          mov   ecx, esi
          call  @duplicateAndLinkActor@4
          mov   edx, dword ptr [esp+010h]
          jmp   LAB_004024c2
LAB_004024c0:     mov   eax, esi
LAB_004024c2:     movsx ecx, di
          sub   dword ptr [eax+020h], ecx
          sub   dword ptr [eax+028h], ecx
          movsx ecx, bx
          sub   dword ptr [eax+024h], ecx
          sub   dword ptr [eax+02Ch], ecx
LAB_004024d4:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_0040249c
LAB_004024da:     pop   edi
          mov   word ptr [playerY], bp  ; <c5f2>
          pop   esi
          pop   ebp
          mov   word ptr [playerX], dx  ; <c640>
          pop   ebx
          pop   ecx
          ret
LAB_004024ee:
          db 090h
          db 090h
@updateActorRectsAfterPlayerMove@8 endp
~

COMMENT ~
@getRandomOffscreenStartingPosition@12 proc
          mov   eax, dword ptr [playerX]        ; <c640>
          push  ebx
          mov   ebx, dword ptr [skierScreenXOffset]     ; <c704>
          push  esi
          mov   esi, edx
          push  edi
          sub   eax, ebx
          mov   ebx, dword ptr [esp+010h]
          mov   edi, ecx
          mov   word ptr [esi], ax
          mov   cx, word ptr [playerY]  ; <c5f2>
          sub   cx, word ptr [skierScreenYOffset]       ; <c5fc>
          cmp   edi, 000000003h
          mov   word ptr [ebx], cx
          ja    LAB_0040259b
          jmp   dword ptr [edi*4+LAB_004025b0]  ; <25b0>
LAB_00402528:     test  edi, edi
          jnz   LAB_00402537
          mov   edx, dword ptr [windowClientRect.left]  ; <c6b0>
          lea   eax, dword ptr [edx-03Ch]
          jmp   LAB_0040253f
LAB_00402537:     mov   eax, dword ptr [windowClientRect.right] ; <c6b8>
          add   eax, 00000003Ch
LAB_0040253f:     add   word ptr [esi], ax
          mov   ecx, dword ptr [windowHeight]   ; <c6d8>
          call  @random@4
          mov   edx, dword ptr [windowClientRect.top]   ; <c6b4>
          add   eax, edx
          pop   edi
          add   word ptr [ebx], ax
          pop   esi
          pop   ebx
          ret   00004h
LAB_0040255e:     mov   ecx, dword ptr [windowWidth]    ; <c5f0>
          call  @random@4
          add   eax, dword ptr [windowClientRect.left]  ; <c6b0>
          add   word ptr [esi], ax
          cmp   edi, 000000002h
          jnz   LAB_00402589
          mov   ecx, dword ptr [windowClientRect.top]   ; <c6b4>
          pop   edi
          pop   esi
          lea   eax, dword ptr [ecx-03Ch]
          add   word ptr [ebx], ax
          pop   ebx
          ret   00004h
LAB_00402589:     mov   edx, dword ptr [windowClientRect.bottom]        ; <c6bc>
          pop   edi
          pop   esi
          lea   eax, dword ptr [edx+03Ch]
          add   word ptr [ebx], ax
          pop   ebx
          ret   00004h
LAB_0040259b:     mov   edx, 0000005AEh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          pop   edi
          pop   esi
          pop   ebx
          ret   00004h
LAB_004025b0:
DAT_004025b0  dword offset LAB_00402528
DAT_004025b4  dword offset LAB_00402528
DAT_004025b8  dword offset LAB_0040255e
DAT_004025bc  dword offset LAB_0040255e
@getRandomOffscreenStartingPosition@12 endp
~

COMMENT ~
@addRandomActor@4 proc
          sub   esp, 000000008h
          lea   eax, dword ptr [esp+000h]
          lea   edx, dword ptr [esp+004h]
          push  esi
          push  edi
          push  eax
          xor   edi, edi
          call  @getRandomOffscreenStartingPosition@12
          mov   eax, dword ptr [esp+00Ch]
          mov   ecx, dword ptr [esp+008h]
          cmp   ax, 0FDC0h
          jl    LAB_004025fe
          cmp   ax, 0FEC0h
          jg    LAB_004025fe
          cmp   cx, 00280h
          jl    LAB_004025fe
          cmp   cx, 021C0h
          jg    LAB_004025fe
          call  _areaBasedActorType
          jmp   LAB_00402645
LAB_004025fe:     cmp   ax, 00140h
          jl    LAB_0040261f
          cmp   ax, 00200h
          jg    LAB_0040261f
          cmp   cx, 00280h
          jl    LAB_0040261f
          cmp   cx, 04100h
          jg    LAB_0040261f
          call  _randomActorType3
          jmp   LAB_00402645
LAB_0040261f:     cmp   ax, 0FF60h
          jl    LAB_00402640
          cmp   ax, 000A0h
          jg    LAB_00402640
          cmp   cx, 00280h
          jl    LAB_00402640
          cmp   cx, 04100h
          jg    LAB_00402640
          call  _randomActorType2
          jmp   LAB_00402645
LAB_00402640:     call  _randomActorType1
LAB_00402645:     mov   esi, eax
          cmp   esi, 000000012h
          jz    LAB_0040268d
          cmp   esi, 00000000Bh
          jge   LAB_00402661
          mov   edx, dword ptr [esi*4+UINT_ARRAY_0040a22c]      ; <a22c>
          mov   ecx, esi
          call  @addActorOfType@8
          jmp   LAB_00402671
LAB_00402661:     mov   ecx, esi
          call  @getSpriteIdxForActorType@4
          mov   edx, eax
          mov   ecx, esi
          call  @addActorOfTypeWithSpriteIdx@8
LAB_00402671:     test  eax, eax
          jz    LAB_0040268f
          mov   ecx, dword ptr [esp+008h]
          mov   edx, dword ptr [esp+00Ch]
          push  000000000h
          push  ecx
          mov   ecx, eax
          call  @updateActorPositionMaybe@16
          pop   edi
          pop   esi
          add   esp, 000000008h
          ret
LAB_0040268d:     mov   eax, edi
LAB_0040268f:     pop   edi
          pop   esi
          add   esp, 000000008h
          ret
LAB_00402695:
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
@addRandomActor@4 endp
~

COMMENT ~
@addActorOfTypeWithSpriteIdx@8 proc
          push  ebx
          push  esi
          push  edi
          mov   ebx, edx
          mov   edi, ecx
          call  _getFreeActor
          mov   esi, eax
          test  esi, esi
          jz    LAB_004026e8
          test  edi, edi
          jge   LAB_004026c5
          mov   edx, 00000057Bh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004026c5:     cmp   edi, 000000012h
          jl    LAB_004026d9
          mov   edx, 00000057Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004026d9:     mov   dword ptr [esi+018h], edi
          mov   ecx, esi
          pop   edi
          mov   edx, ebx
          pop   esi
          pop   ebx
          jmp   @actorSetSpriteIdx@8
LAB_004026e8:     mov   eax, esi
          pop   edi
          pop   esi
          pop   ebx
          ret
LAB_004026ee:
          db 090h
          db 090h
@addActorOfTypeWithSpriteIdx@8 endp
~

COMMENT ~
_randomActorType1 proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          cdq
          and   edx, 00000001Fh
          add   eax, edx
          sar   eax, 005h
          cmp   ecx, eax
          jle   LAB_0040270e
          mov   eax, 000000012h
          ret
LAB_0040270e:     mov   ecx, 0000003E8h
          call  @random@4
          cmp   ax, 00032h
          jae   LAB_00402724
          mov   eax, 00000000Ah
          ret
LAB_00402724:     cmp   ax, 001F4h
          jae   LAB_00402730
          mov   eax, 00000000Dh
          ret
LAB_00402730:     cmp   ax, 002BCh
          jae   LAB_0040273c
          mov   eax, 00000000Fh
          ret
LAB_0040273c:     cmp   ax, 002EEh
          jae   LAB_00402748
          mov   eax, 00000000Bh
          ret
LAB_00402748:     cmp   ax, 003B6h
          jae   LAB_00402754
          mov   eax, 00000000Eh
          ret
LAB_00402754:     cmp   ax, 003CAh
          jae   LAB_00402760
          mov   eax, 000000010h
          ret
LAB_00402760:     cmp   ax, 003DEh
          sbb   eax, eax
          add   eax, 000000002h
          ret
LAB_0040276a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_randomActorType1 endp
~

COMMENT ~
_areaBasedActorType proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          xor   ecx, ecx
          cdq
          and   edx, 00000003Fh
          add   eax, edx
          mov   edx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          sar   eax, 006h
          cmp   edx, eax
          setle cl
          dec   ecx
          and   ecx, 000000007h
          add   ecx, 00000000Bh
          mov   eax, ecx
          ret
LAB_00402795:
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
_areaBasedActorType endp
~

COMMENT ~
_randomActorType3 proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          cdq
          and   edx, 00000000Fh
          add   eax, edx
          sar   eax, 004h
          cmp   ecx, eax
          jle   LAB_004027be
          mov   eax, 000000012h
          ret
LAB_004027be:     mov   ecx, 000000040h
          call  @random@4
          neg   ax
          sbb   eax, eax
          and   eax, 00000000Bh
          add   eax, 000000002h
          ret
LAB_004027d4:
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
_randomActorType3 endp
~

COMMENT ~
_randomActorType2 proc
          mov   eax, dword ptr [windowWithMarginTotalArea]      ; <c748>
          mov   ecx, dword ptr [totalAreaOfActorSprites]        ; <c6fc>
          cdq
          and   edx, 00000001Fh
          add   eax, edx
          sar   eax, 005h
          cmp   ecx, eax
          jle   LAB_004027fe
          mov   eax, 000000012h
          ret
LAB_004027fe:     mov   ecx, 000000064h
          call  @random@4
          cmp   ax, 00002h
          jae   LAB_00402814
          mov   eax, 00000000Ah
          ret
LAB_00402814:     cmp   ax, 00014h
          jae   LAB_00402820
          mov   eax, 00000000Dh
          ret
LAB_00402820:     cmp   ax, 00032h
          jae   LAB_0040282c
          mov   eax, 00000000Fh
          ret
LAB_0040282c:     cmp   ax, 0003Ch
          jae   LAB_00402838
          mov   eax, 00000000Bh
          ret
LAB_00402838:     cmp   ax, 00050h
          sbb   eax, eax
          and   al, 0FEh
          add   eax, 000000010h
          ret
LAB_00402844:
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
_randomActorType2 endp
~

COMMENT ~
@getSpriteIdxForActorType@4 proc
          lea   eax, dword ptr [ecx-00Bh]
          cmp   eax, 000000005h
          ja    LAB_004028b3
          jmp   dword ptr [eax*4+LAB_004028c8]  ; <28c8>
LAB_0040285f:     mov   ax, 0001Bh
          ret
LAB_00402864:     mov   ecx, 000000008h
          call  @random@4
          movsx eax, ax
          sub   eax, 000000000h
          jz    LAB_00402883
          dec   eax
          jz    LAB_0040287e
          mov   ax, 00031h
          ret
LAB_0040287e:     mov   ax, 00033h
          ret
LAB_00402883:     mov   ax, 00032h
          ret
LAB_00402888:     mov   ecx, 000000004h
          call  @random@4
          neg   ax
          sbb   eax, eax
          add   eax, 00000002Eh
          ret
LAB_0040289b:     mov   ecx, 000000003h
          call  @random@4
          neg   ax
          sbb   eax, eax
          add   eax, 000000030h
          ret
LAB_004028ae:     mov   ax, 00034h
          ret
LAB_004028b3:     mov   edx, 000000623h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          xor   ax, ax
          ret
LAB_004028c6:
          db 08Bh
          db 0FFh
LAB_004028c8:
DAT_004028c8  dword offset LAB_0040285f
DAT_004028cc  dword offset LAB_004028b3
DAT_004028d0  dword offset LAB_00402864
DAT_004028d4  dword offset LAB_00402888
DAT_004028d8  dword offset LAB_0040289b
DAT_004028dc  dword offset LAB_004028ae
@getSpriteIdxForActorType@4 endp
~

COMMENT ~
@updateActor@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_004028f6
          mov   edx, 000000907h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004028f6:     cmp   dword ptr [esi+018h], 00000000Bh
          jge   LAB_00402903
          mov   eax, dword ptr [esi+00Ch]
          test  eax, eax
          jz    LAB_00402912
LAB_00402903:     mov   edx, 000000908h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402912:     mov   eax, dword ptr [esi+018h]
          cmp   eax, 00000000Ah
          ja    LAB_00402951
          jmp   dword ptr [eax*4+LAB_00402964]  ; <2964>
LAB_00402921:     mov   ecx, esi
          pop   esi
          jmp   @updatePlayerActor@4
LAB_00402929:     mov   ecx, esi
          pop   esi
          jmp   @updateActorType3_snowboarder@4
LAB_00402931:     mov   ecx, esi
          pop   esi
          jmp   @updateActorType2_dog@4
LAB_00402939:     mov   ecx, esi
          pop   esi
          jmp   @updateActorType1_Beginner@4
LAB_00402941:     mov   ecx, esi
          pop   esi
          jmp   @updateActorType9_treeOnFire@4
LAB_00402949:     mov   ecx, esi
          pop   esi
          jmp   @updateActorTypeA_walkingTree@4
LAB_00402951:     mov   edx, 00000091Fh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          mov   eax, esi
          pop   esi
          ret
LAB_00402964:
DAT_00402964  dword offset LAB_00402921
DAT_00402968  dword offset LAB_00402939
DAT_0040296c  dword offset LAB_00402931
DAT_00402970  dword offset LAB_00402929
DAT_00402974  dword offset LAB_00402951
DAT_00402978  dword offset LAB_00402951
DAT_0040297c  dword offset LAB_00402951
DAT_00402980  dword offset LAB_00402951
DAT_00402984  dword offset LAB_00402951
DAT_00402988  dword offset LAB_00402941
DAT_0040298c  dword offset LAB_00402949
@updateActor@4 endp
~

COMMENT ~
@updatePlayerActor@4 proc
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          push  edi
          mov   bx, word ptr [esi+040h]
          mov   bp, word ptr [esi+042h]
          mov   edi, dword ptr [esi+01Ch]
          test  esi, esi
          jnz   LAB_004029b4
          mov   edx, 0000007E6h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004029b4:     mov   eax, dword ptr [esi+018h]
          test  eax, eax
          jz    LAB_004029ca
          mov   edx, 0000007E7h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004029ca:     cmp   edi, 00000000Bh
          jnz   LAB_00402a55
          cmp   word ptr [esi+044h], 000000000h
          jz    LAB_004029e9
          mov   edx, 0000007EBh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004029e9:     cmp   word ptr [esi+04Ah], 000000000h
          jz    LAB_004029ff
          mov   edx, 0000007ECh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004029ff:     mov   ax, word ptr [esi+046h]
          test  ax, ax
          jnz   LAB_00402a16
          cmp   word ptr [esi+048h], ax
          jnz   LAB_00402a13
          mov   edi, 00000000Ch
LAB_00402a13:     test  ax, ax
LAB_00402a16:     jge   LAB_00402a1d
          or    ecx, 0FFFFFFFFh
          jmp   LAB_00402a25
LAB_00402a1d:     xor   ecx, ecx
          test  ax, ax
          setg  cl
LAB_00402a25:     sub   eax, ecx
          mov   word ptr [esi+046h], ax
          mov   ax, word ptr [esi+048h]
          test  ax, ax
          jge   LAB_00402a42
          or    ecx, 0FFFFFFFFh
          sub   eax, ecx
          mov   word ptr [esi+048h], ax
          jmp   LAB_00402af0
LAB_00402a42:     xor   ecx, ecx
          test  ax, ax
          setg  cl
          sub   eax, ecx
          mov   word ptr [esi+048h], ax
          jmp   LAB_00402af0
LAB_00402a55:     mov   ecx, esi
          call  @updateActorPositionWithVelocityMaybe@4
          cmp   edi, 000000016h
          mov   esi, eax
          jb    LAB_00402a72
          mov   edx, 0000007F8h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402a72:     mov   edx, edi
          mov   ecx, esi
          shl   edx, 004h
          add   edx, offset ActorVelStruct_ARRAY_0040a308       ; <a308>
          call  @updateActorVelMaybe@8
          mov   esi, eax
          lea   eax, dword ptr [edi-007h]
          cmp   eax, 00000000Eh
          ja    LAB_00402af0
          xor   ecx, ecx
          mov   cl, byte ptr [eax+LAB_00402b64] ; <2b64>
          jmp   dword ptr [ecx*4+LAB_00402b54]  ; <2b54>
LAB_00402a9d:     mov   edi, 000000006h
          jmp   LAB_00402af0
LAB_00402aa4:     mov   edi, 000000003h
          jmp   LAB_00402af0
LAB_00402aab:     cmp   word ptr [esi+044h], 000000000h
          jnz   LAB_00402af0
          lea   edx, dword ptr [edi-00Dh]
          cmp   edx, 000000009h
          jb    LAB_00402ac9
          mov   edx, 000000812h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402ac9:     mov   edi, dword ptr [edi*4+UINT_ARRAY_0040a434]      ; <a434>
          cmp   edi, 000000011h
          jnz   LAB_00402ae6
          mov   ecx, 0FFFFFFC0h
          call  @addStylePoints@4
          mov   ecx, offset sound_1.soundResource       ; <c6c0>
          jmp   LAB_00402aeb
LAB_00402ae6:     mov   ecx, offset sound_4.soundResource       ; <c718>
LAB_00402aeb:     call  @playSound@4
LAB_00402af0:     mov   edx, edi
          mov   ecx, esi
          call  @setActorFrameNo@8
          mov   esi, eax
          lea   eax, dword ptr [edi-007h]
          cmp   eax, 00000000Eh
          ja    LAB_00402b2f
          xor   ecx, ecx
          mov   cl, byte ptr [eax+LAB_00402b88] ; <2b88>
          jmp   dword ptr [ecx*4+LAB_00402b74]  ; <2b74>
LAB_00402b12:     or    ecx, 0FFFFFFFFh
          jmp   LAB_00402b2a
LAB_00402b17:     mov   ecx, 000000008h
          jmp   LAB_00402b2a
LAB_00402b1e:     mov   ecx, 000000004h
          jmp   LAB_00402b2a
LAB_00402b25:     mov   ecx, 000000002h
LAB_00402b2a:     call  @addStylePoints@4
LAB_00402b2f:     push  ebp
          mov   edx, ebx
          mov   ecx, esi
          call  @updateSsGameMode@12
          mov   edx, ebx
          mov   ecx, esi
          push  ebp
          call  @updateFsGameMode@12
          mov   edx, ebx
          mov   ecx, esi
          push  ebp
          call  @updateGsGameMode@12
          mov   eax, esi
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret
LAB_00402b54:
DAT_00402b54  dword offset LAB_00402aa4
DAT_00402b58  dword offset LAB_00402a9d
DAT_00402b5c  dword offset LAB_00402aab
DAT_00402b60  dword offset LAB_00402af0
LAB_00402b64:
          db 000h
          db 001h
          db 000h
          db 001h
          db 003h
          db 003h
          db 002h
          db 002h
          db 002h
          db 002h
          db 002h
          db 002h
          db 002h
          db 002h
          db 002h
          db 090h
LAB_00402b74:
DAT_00402b74  dword offset LAB_00402b12
DAT_00402b78  dword offset LAB_00402b25
DAT_00402b7c  dword offset LAB_00402b1e
DAT_00402b80  dword offset LAB_00402b17
DAT_00402b84  dword offset LAB_00402b2f
LAB_00402b88:
          db 000h
          db 000h
          db 000h
          db 000h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 001h
          db 004h
          db 002h
          db 002h
          db 003h
          db 003h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updatePlayerActor@4 endp
~

COMMENT ~
@playSound@4 proc
          mov   eax, dword ptr [isSoundDisabled]        ; <c794>
          push  esi
          test  eax, eax
          mov   esi, ecx
          jnz   LAB_00402bd8
          mov   eax, dword ptr [esi+004h]
          test  eax, eax
          jnz   LAB_00402bc3
          mov   eax, dword ptr [esi]
          test  eax, eax
          jz    LAB_00402bc3
          push  eax
          call  dword ptr [__imp__LockResource@4]       ; <LockResource>
          mov   dword ptr [esi+004h], eax
LAB_00402bc3:     mov   esi, dword ptr [esi+004h]
          test  esi, esi
          jz    LAB_00402bd8
          mov   eax, dword ptr [sndPlaySoundAFuncPtr]   ; <c790>
          test  eax, eax
          jz    LAB_00402bd8
          push  000000005h
          push  esi
          call  eax
LAB_00402bd8:     pop   esi
          ret
LAB_00402bda:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@playSound@4 endp
~

COMMENT ~
@updateActorPositionWithVelocityMaybe@4 proc
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          push  edi
          mov   bx, word ptr [esi+040h]
          mov   bp, word ptr [esi+042h]
          mov   di, word ptr [esi+044h]
          add   bx, word ptr [esi+046h]
          add   bp, word ptr [esi+048h]
          add   di, word ptr [esi+04Ah]
          test  esi, esi
          jnz   LAB_00402c11
          mov   edx, 000000425h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402c11:     mov   eax, dword ptr [isTurboMode]    ; <c670>
          test  eax, eax
          jz    LAB_00402c2c
          mov   ax, word ptr [esi+046h]
          mov   cx, word ptr [esi+048h]
          mov   dx, word ptr [esi+04Ah]
          add   ebx, eax
          add   ebp, ecx
          add   edi, edx
LAB_00402c2c:     test  di, di
          jle   LAB_00402c45
          dec   word ptr [esi+04Ah]
          push  edi
          push  ebp
          mov   edx, ebx
          mov   ecx, esi
          call  @updateActorPositionMaybe@16
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret
LAB_00402c45:     xor   edi, edi
          mov   edx, ebx
          push  edi
          push  ebp
          mov   ecx, esi
          mov   word ptr [esi+04Ah], 00000h
          call  @updateActorPositionMaybe@16
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret
LAB_00402c5d:
          db 090h
          db 090h
          db 090h
@updateActorPositionWithVelocityMaybe@4 endp
~

COMMENT ~
@updateSsGameMode@12 proc
          mov   eax, dword ptr [playerActor]    ; <c72c>
          push  ebx
          push  ebp
          push  esi
          cmp   ecx, eax
          push  edi
          mov   bp, dx
          jnz   LAB_00402e1d
          mov   eax, dword ptr [ecx+018h]
          mov   bx, word ptr [ecx+040h]
          mov   si, word ptr [ecx+042h]
          xor   edi, edi
          cmp   eax, edi
          jz    LAB_00402c94
          mov   edx, 0000006FCh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402c94:     cmp   dword ptr [isSsGameMode], edi   ; <c95c>
          jz    LAB_00402da7
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          mov   edx, dword ptr [timedGameRelated]       ; <c948>
          mov   eax, ecx
          sub   eax, edx
          cmp   si, 021C0h
          mov   dword ptr [elapsedTime], eax    ; <c944>
          jle   LAB_00402d11
          movsx edx, word ptr [esp+014h]
          movsx eax, si
          push  0000021C0h
          push  edx
          mov   edx, dword ptr [prevTickCount]  ; <c708>
          push  eax
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [timedGameRelated]       ; <c948>
          mov   dword ptr [isSsGameMode], edi   ; <c95c>
          sub   eax, ecx
          mov   dword ptr [INT_0040c964], 000000001h    ; <c964>
          mov   dword ptr [elapsedTime], eax    ; <c944>
          call  _resetPlayerFrameNo
          mov   edx, dword ptr [elapsedTime]    ; <c944>
          mov   ecx, offset iniSsConfigKey      ; <c0d8>
          push  000000001h
          call  @updateEntPackIniKeyValue@12
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00402d11:     cmp   si, 00280h
          jg    LAB_00402d25
          mov   dword ptr [isSsGameMode], edi   ; <c95c>
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00402d25:     mov   ecx, dword ptr [currentSlalomFlag]      ; <c6f8>
          mov   ax, word ptr [ecx+016h]
          cmp   si, ax
          jle   LAB_00402e1d
          movsx edx, ax
          movsx eax, word ptr [esp+014h]
          movsx ecx, si
          push  edx
          push  eax
          push  ecx
          mov   edi, 000000019h
          movsx edx, bp
          movsx ecx, bx
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [currentSlalomFlag]      ; <c6f8>
          mov   dx, word ptr [ecx+008h]
          cmp   dx, 000000017h
          jnz   LAB_00402d6c
          cmp   ax, word ptr [ecx+014h]
          jg    LAB_00402d78
LAB_00402d6c:     cmp   dx, 000000018h
          jnz   LAB_00402d8c
          cmp   ax, word ptr [ecx+014h]
          jge   LAB_00402d8c
LAB_00402d78:     mov   eax, dword ptr [timedGameRelated]       ; <c948>
          mov   edi, 00000001Ah
          sub   eax, 000001388h
          mov   dword ptr [timedGameRelated], eax       ; <c948>
LAB_00402d8c:     mov   edx, edi
          call  @permObjectSetSpriteIdx@8
          mov   eax, dword ptr [currentSlalomFlag]      ; <c6f8>
          pop   edi
          add   eax, 000000024h
          pop   esi
          pop   ebp
          mov   dword ptr [currentSlalomFlag], eax      ; <c6f8>
          pop   ebx
          ret   00004h
LAB_00402da7:     mov   ax, word ptr [esp+014h]
          cmp   ax, 00280h
          jg    LAB_00402e1d
          cmp   si, 00280h
          jle   LAB_00402e1d
          movsx edi, ax
          movsx esi, si
          push  000000280h
          push  edi
          movsx edx, bp
          movsx ecx, bx
          push  esi
          call  @FUN_00402e30@20
          cmp   ax, 0FDC0h
          jl    LAB_00402e1d
          cmp   ax, 0FEC0h
          jg    LAB_00402e1d
          mov   edx, dword ptr [prevTickCount]  ; <c708>
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          push  000000280h
          push  edi
          push  esi
          mov   dword ptr [isSsGameMode], 000000001h    ; <c95c>
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          mov   edx, dword ptr [firstSlalomFlagLeft]    ; <c94c>
          mov   dword ptr [timedGameRelated], eax       ; <c948>
          sub   eax, ecx
          mov   dword ptr [elapsedTime], eax    ; <c944>
          mov   dword ptr [currentSlalomFlag], edx      ; <c6f8>
LAB_00402e1d:     pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00402e24:
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
@updateSsGameMode@12 endp
~

COMMENT ~
@FUN_00402e30@20 proc
          push  ebx
          push  ebp
          mov   ebp, dword ptr [esp+010h]
          push  esi
          push  edi
          mov   edi, dword ptr [esp+014h]
          cmp   edi, ebp
          mov   ebx, edx
          mov   esi, ecx
          jnz   LAB_00402e53
          mov   edx, 00000064Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00402e53:     mov   eax, esi
          mov   ecx, edi
          sub   eax, ebx
          mov   ebx, dword ptr [esp+01Ch]
          sub   ecx, ebx
          sub   edi, ebp
          imul  eax, ecx
          cdq
          idiv  edi
          pop   edi
          sub   esi, eax
          mov   eax, esi
          pop   esi
          pop   ebp
          pop   ebx
          ret   0000Ch
LAB_00402e72:
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
@FUN_00402e30@20 endp
~

COMMENT ~
_resetPlayerFrameNo proc
          mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_00402eb7
          mov   edx, dword ptr [ecx+01Ch]
          cmp   edx, 00000000Bh
          jz    LAB_00402ea7
          cmp   edx, 000000011h
          jz    LAB_00402ea7
          xor   edx, edx
          cmp   word ptr [ecx+044h], dx
          setle dl
          dec   edx
          and   edx, 00000000Bh
          add   edx, 000000003h
LAB_00402ea7:     call  @setActorFrameNo@8
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          jmp   @formatAndPrintStatusStrings@4
LAB_00402eb7:     ret
LAB_00402eb8:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_resetPlayerFrameNo endp
~

COMMENT ~
@updateEntPackIniKeyValue@12 proc
          sub   esp, 000000138h
          mov   eax, dword ptr [esp+00000013Ch]
          push  ebx
          push  ebp
          push  esi
          mov   ebp, edx
          xor   ebx, ebx
          push  edi
          mov   dword ptr [esp+014h], ebp
          test  eax, eax
          mov   dword ptr [esp+01Ch], ecx
          mov   dword ptr [esp+010h], ebx
          lea   edi, dword ptr [esp+048h]
          jz    LAB_00402eef
          neg   ebp
          mov   dword ptr [esp+014h], ebp
LAB_00402eef:     push  offset s_entpack_ini    ; <c084>
          lea   eax, dword ptr [esp+04Ch]
          push  000000100h
          push  eax
          push  offset statusWindowNameStrPtr   ; <c788>
          push  ecx
          push  offset entpack_ini_section_name_ski     ; <c080>
          call  dword ptr [__imp__GetPrivateProfileStringA@24]  ; <GetPrivateProfileStringA>
          mov   al, byte ptr [esp+048h]
          test  al, al
          jz    LAB_00402f6c
LAB_00402f17:     cmp   bx, 00000000Ah
          jae   LAB_00402f68
          cmp   byte ptr [edi], 020h
          jnz   LAB_00402f2a
LAB_00402f22:     mov   al, byte ptr [edi+001h]
          inc   edi
          cmp   al, 020h
          jz    LAB_00402f22
LAB_00402f2a:     mov   al, byte ptr [edi]
          mov   esi, edi
          cmp   al, 020h
          jz    LAB_00402f63
LAB_00402f32:     test  al, al
          jz    LAB_00402f3e
          mov   al, byte ptr [esi+001h]
          inc   esi
          cmp   al, 020h
          jnz   LAB_00402f32
LAB_00402f3e:     cmp   esi, edi
          jz    LAB_00402f63
          cmp   byte ptr [esi], 000h
          jz    LAB_00402f4b
          mov   byte ptr [esi], 000h
          inc   esi
LAB_00402f4b:     push  edi
          call  _atol
          mov   ecx, ebx
          add   esp, 000000004h
          and   ecx, 00000FFFFh
          inc   ebx
          mov   edi, esi
          mov   dword ptr [esp+ecx*4+020h], eax
LAB_00402f63:     cmp   byte ptr [edi], 000h
          jnz   LAB_00402f17
LAB_00402f68:     mov   dword ptr [esp+010h], ebx
LAB_00402f6c:     xor   esi, esi
          test  bx, bx
          mov   dword ptr [esp+018h], esi
          jbe   LAB_00402f95
LAB_00402f77:     mov   edx, esi
          and   edx, 00000FFFFh
          cmp   ebp, dword ptr [esp+edx*4+020h]
          jg    LAB_00402f8b
          inc   esi
          cmp   si, bx
          jb    LAB_00402f77
LAB_00402f8b:     cmp   si, 00000000Ah
          mov   dword ptr [esp+018h], esi
          jae   LAB_00402fe2
LAB_00402f95:     cmp   bx, 00000000Ah
          jnz   LAB_00402fa7
          mov   dword ptr [esp+010h], 000000009h
          mov   ebx, dword ptr [esp+010h]
LAB_00402fa7:     cmp   bx, si
          mov   edx, ebx
          jbe   LAB_00402fd3
          mov   ecx, ebx
          and   esi, 00000FFFFh
          and   ecx, 00000FFFFh
          lea   eax, dword ptr [esp+ecx*4+020h]
          sub   ecx, esi
LAB_00402fc2:     mov   esi, dword ptr [eax-004h]
          add   edx, 00000FFFFh
          mov   dword ptr [eax], esi
          sub   eax, 000000004h
          dec   ecx
          jnz   LAB_00402fc2
LAB_00402fd3:     and   edx, 00000FFFFh
          inc   ebx
          mov   dword ptr [esp+010h], ebx
          mov   dword ptr [esp+edx*4+020h], ebp
LAB_00402fe2:     mov   ebp, dword ptr [__imp__wsprintfA]       ; <wsprintfA>
          lea   edi, dword ptr [esp+048h]
          test  bx, bx
          jbe   LAB_00403015
          lea   esi, dword ptr [esp+020h]
          and   ebx, 00000FFFFh
LAB_00402ffb:     mov   eax, dword ptr [esi]
          push  eax
          push  offset scoreFormatString        ; <c0ec>
          push  edi
          call  ebp
          add   esp, 00000000Ch
          add   edi, eax
          add   esi, 000000004h
          dec   ebx
          jnz   LAB_00402ffb
          mov   ebx, dword ptr [esp+010h]
LAB_00403015:     mov   edx, dword ptr [esp+01Ch]
          lea   ecx, dword ptr [esp+048h]
          push  offset s_entpack_ini    ; <c084>
          push  ecx
          push  edx
          push  offset entpack_ini_section_name_ski     ; <c080>
          call  dword ptr [__imp__WritePrivateProfileStringA@16]        ; <WritePrivateProfileStringA>
          xor   edi, edi
          lea   esi, dword ptr [esp+048h]
          test  bx, bx
          jbe   LAB_0040309e
          lea   ebx, dword ptr [esp+020h]
LAB_0040303e:     test  di, di
          jbe   LAB_00403047
          mov   byte ptr [esi], 00Ah
          inc   esi
LAB_00403047:     mov   eax, dword ptr [esp+00000014Ch]
          test  eax, eax
          jz    LAB_00403064
          mov   ecx, dword ptr [ebx]
          mov   edx, esi
          neg   ecx
          call  @formatElapsedTime@8
          and   eax, 00000FFFFh
          jmp   LAB_00403072
LAB_00403064:     mov   eax, dword ptr [ebx]
          push  eax
          push  offset stylePointsFormatString  ; <c0e4>
          push  esi
          call  ebp
          add   esp, 00000000Ch
LAB_00403072:     add   esi, eax
          cmp   di, word ptr [esp+018h]
          jnz   LAB_00403093
          mov   ecx, 000000010h
          call  @getCachedString@4
          push  eax
          push  offset scoreStringFormatString  ; <c0e0>
          push  esi
          call  ebp
          add   esp, 00000000Ch
          add   esi, eax
LAB_00403093:     inc   edi
          add   ebx, 000000004h
          cmp   di, word ptr [esp+010h]
          jb    LAB_0040303e
LAB_0040309e:     cmp   word ptr [esp+018h], 00000000Ah
          jnz   LAB_00403100
          push  offset newlineString    ; <c0dc>
          push  esi
          call  ebp
          add   esi, eax
          mov   eax, dword ptr [esp+000000154h]
          add   esp, 000000008h
          test  eax, eax
          jz    LAB_004030d6
          mov   ecx, dword ptr [esp+014h]
          mov   edx, esi
          neg   ecx
          call  @formatElapsedTime@8
          mov   di, ax
          and   edi, 00000FFFFh
          jmp   LAB_004030e8
LAB_004030d6:     mov   ecx, dword ptr [esp+014h]
          push  ecx
          push  offset stylePointsFormatString  ; <c0e4>
          push  esi
          call  ebp
          add   esp, 00000000Ch
          mov   edi, eax
LAB_004030e8:     mov   ecx, 000000011h
          call  @getCachedString@4
          add   edi, esi
          push  eax
          push  offset scoreStringFormatString  ; <c0e0>
          push  edi
          call  ebp
          add   esp, 00000000Ch
LAB_00403100:     push  000000000h
          mov   ecx, 00000000Fh
          call  @getCachedString@4
          lea   edx, dword ptr [esp+04Ch]
          push  eax
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  edx
          push  eax
          call  dword ptr [__imp__MessageBoxA@16]       ; <MessageBoxA>
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000138h
          ret   00004h
LAB_0040312b:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateEntPackIniKeyValue@12 endp
~

COMMENT ~
@permObjectSetSpriteIdx@8 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_00403149
          mov   edx, 0000006EDh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403149:     mov   eax, edi
          mov   word ptr [esi+008h], di
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          and   eax, 00000FFFFh
          shl   eax, 004h
          add   eax, ecx
          mov   ecx, dword ptr [esi]
          test  ecx, ecx
          mov   dword ptr [esi+004h], eax
          jz    LAB_0040316f
          mov   edx, edi
          call  @actorSetSpriteIdx@8
LAB_0040316f:     pop   edi
          pop   esi
          ret
LAB_00403172:
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
@permObjectSetSpriteIdx@8 endp
~

COMMENT ~
@updateFsGameMode@12 proc
          mov   eax, dword ptr [playerActor]    ; <c72c>
          push  ebx
          push  esi
          cmp   ecx, eax
          push  edi
          mov   bx, dx
          jnz   LAB_00403249
          mov   eax, dword ptr [ecx+018h]
          mov   di, word ptr [ecx+040h]
          mov   si, word ptr [ecx+042h]
          test  eax, eax
          jz    LAB_004031b1
          mov   edx, 00000072Fh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004031b1:     mov   eax, dword ptr [isFsGameMode]   ; <c954>
          test  eax, eax
          jz    LAB_00403209
          cmp   si, 04100h
          jle   LAB_004031f2
          mov   dword ptr [isFsGameMode], 000000000h    ; <c954>
          mov   dword ptr [INT_0040c968], 000000001h    ; <c968>
          call  _resetPlayerFrameNo
          mov   edx, dword ptr [stylePoints]    ; <c6a8>
          mov   ecx, offset iniFsConfigKey      ; <c0f4>
          push  000000000h
          call  @updateEntPackIniKeyValue@12
          pop   edi
          pop   esi
          pop   ebx
          ret   00004h
LAB_004031f2:     cmp   si, 00280h
          jg    LAB_00403249
          pop   edi
          pop   esi
          mov   dword ptr [isFsGameMode], 000000000h    ; <c954>
          pop   ebx
          ret   00004h
LAB_00403209:     mov   ax, word ptr [esp+010h]
          cmp   ax, 00280h
          jg    LAB_00403249
          cmp   si, 00280h
          jle   LAB_00403249
          movsx eax, ax
          movsx ecx, si
          push  000000280h
          push  eax
          push  ecx
          movsx edx, bx
          movsx ecx, di
          call  @FUN_00402e30@20
          cmp   ax, 0FF60h
          jl    LAB_00403249
          cmp   ax, 000A0h
          jg    LAB_00403249
          mov   dword ptr [isFsGameMode], 000000001h    ; <c954>
LAB_00403249:     pop   edi
          pop   esi
          pop   ebx
          ret   00004h
LAB_0040324f:
          db 090h
@updateFsGameMode@12 endp
~

COMMENT ~
@updateGsGameMode@12 proc
          mov   eax, dword ptr [playerActor]    ; <c72c>
          push  ebx
          push  ebp
          push  esi
          cmp   ecx, eax
          push  edi
          mov   bp, dx
          jnz   LAB_0040340d
          mov   eax, dword ptr [ecx+018h]
          mov   bx, word ptr [ecx+040h]
          mov   si, word ptr [ecx+042h]
          xor   edi, edi
          cmp   eax, edi
          jz    LAB_00403284
          mov   edx, 00000074Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403284:     cmp   dword ptr [isGsGameMode], edi   ; <c958>
          jz    LAB_00403397
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          mov   edx, dword ptr [timedGameRelated]       ; <c948>
          mov   eax, ecx
          sub   eax, edx
          cmp   si, 04100h
          mov   dword ptr [elapsedTime], eax    ; <c944>
          jle   LAB_00403301
          movsx edx, word ptr [esp+014h]
          movsx eax, si
          push  000004100h
          push  edx
          mov   edx, dword ptr [prevTickCount]  ; <c708>
          push  eax
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [timedGameRelated]       ; <c948>
          mov   dword ptr [isGsGameMode], edi   ; <c958>
          sub   eax, ecx
          mov   dword ptr [INT_0040c960], 000000001h    ; <c960>
          mov   dword ptr [elapsedTime], eax    ; <c944>
          call  _resetPlayerFrameNo
          mov   edx, dword ptr [elapsedTime]    ; <c944>
          mov   ecx, offset iniGsConfigKey      ; <c0f8>
          push  000000001h
          call  @updateEntPackIniKeyValue@12
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00403301:     cmp   si, 00280h
          jg    LAB_00403315
          mov   dword ptr [isGsGameMode], edi   ; <c958>
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00403315:     mov   ecx, dword ptr [currentSlalomFlag]      ; <c6f8>
          mov   ax, word ptr [ecx+016h]
          cmp   si, ax
          jle   LAB_0040340d
          movsx edx, ax
          movsx eax, word ptr [esp+014h]
          movsx ecx, si
          push  edx
          push  eax
          push  ecx
          mov   edi, 000000019h
          movsx edx, bp
          movsx ecx, bx
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [currentSlalomFlag]      ; <c6f8>
          mov   dx, word ptr [ecx+008h]
          cmp   dx, 000000017h
          jnz   LAB_0040335c
          cmp   ax, word ptr [ecx+014h]
          jg    LAB_00403368
LAB_0040335c:     cmp   dx, 000000018h
          jnz   LAB_0040337c
          cmp   ax, word ptr [ecx+014h]
          jge   LAB_0040337c
LAB_00403368:     mov   eax, dword ptr [timedGameRelated]       ; <c948>
          mov   edi, 00000001Ah
          sub   eax, 000001388h
          mov   dword ptr [timedGameRelated], eax       ; <c948>
LAB_0040337c:     mov   edx, edi
          call  @permObjectSetSpriteIdx@8
          mov   eax, dword ptr [currentSlalomFlag]      ; <c6f8>
          pop   edi
          add   eax, 000000024h
          pop   esi
          pop   ebp
          mov   dword ptr [currentSlalomFlag], eax      ; <c6f8>
          pop   ebx
          ret   00004h
LAB_00403397:     mov   ax, word ptr [esp+014h]
          cmp   ax, 00280h
          jg    LAB_0040340d
          cmp   si, 00280h
          jle   LAB_0040340d
          movsx edi, ax
          movsx esi, si
          push  000000280h
          push  edi
          movsx edx, bp
          movsx ecx, bx
          push  esi
          call  @FUN_00402e30@20
          cmp   ax, 00140h
          jl    LAB_0040340d
          cmp   ax, 00200h
          jg    LAB_0040340d
          mov   edx, dword ptr [prevTickCount]  ; <c708>
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          push  000000280h
          push  edi
          push  esi
          mov   dword ptr [isGsGameMode], 000000001h    ; <c958>
          call  @FUN_00402e30@20
          mov   ecx, dword ptr [currentTickCount]       ; <c698>
          mov   edx, dword ptr [FirstSlalomFlagRight]   ; <c950>
          mov   dword ptr [timedGameRelated], eax       ; <c948>
          sub   eax, ecx
          mov   dword ptr [elapsedTime], eax    ; <c944>
          mov   dword ptr [currentSlalomFlag], edx      ; <c6f8>
LAB_0040340d:     pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          ret   00004h
LAB_00403414:
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
@updateGsGameMode@12 endp
~

COMMENT ~
@addStylePoints@4 proc
          mov   eax, dword ptr [isFsGameMode]   ; <c954>
          test  eax, eax
          jz    LAB_0040342f
          add   dword ptr [stylePoints], ecx    ; <c6a8>
LAB_0040342f:     ret
@addStylePoints@4 endp
~

COMMENT ~
@updateActorVelMaybe@8 proc
          push  ecx
          push  ebx
          push  ebp
          mov   ebp, ecx
          push  esi
          push  edi
          mov   esi, edx
          mov   di, word ptr [ebp+046h]
          mov   bx, word ptr [ebp+048h]
          test  ebp, ebp
          jnz   LAB_00403454
          mov   edx, 00000079Fh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403454:     test  esi, esi
          jnz   LAB_00403467
          mov   edx, 0000007A0h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403467:     mov   eax, dword ptr [ebp+01Ch]
          mov   ecx, dword ptr [esi+00Ch]
          cmp   eax, ecx
          jz    LAB_00403480
          mov   edx, 0000007A1h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403480:     mov   ax, word ptr [esi+008h]
          test  ax, ax
          mov   dword ptr [esp+010h], eax
          jnz   LAB_004034a8
          test  di, di
          jge   LAB_0040349c
          mov   dword ptr [esp+010h], 0FFFFFFFFh
          jmp   LAB_004034a8
LAB_0040349c:     xor   ecx, ecx
          test  di, di
          setg  cl
          mov   dword ptr [esp+010h], ecx
LAB_004034a8:     mov   ecx, dword ptr [esp+010h]
          imul  ecx, edi
          test  bx, bx
          jle   LAB_004034b9
          movsx edx, bx
          jmp   LAB_004034bb
LAB_004034b9:     xor   edx, edx
LAB_004034bb:     movsx eax, word ptr [esi+006h]
          imul  eax, edx
          cdq
          sub   eax, edx
          sar   eax, 1h
          cmp   cx, ax
          jle   LAB_004034dd
          movsx ecx, cx
          movsx eax, ax
          add   ecx, 0FFFFFFFEh
          cmp   eax, ecx
          jle   LAB_004034f1
          mov   edx, eax
          jmp   LAB_004034f3
LAB_004034dd:     movsx edx, word ptr [esi+004h]
          movsx ecx, cx
          movsx eax, ax
          add   ecx, edx
          cmp   eax, ecx
          jge   LAB_004034f1
          mov   edx, eax
          jmp   LAB_004034f3
LAB_004034f1:     mov   edx, ecx
LAB_004034f3:     mov   ax, word ptr [esi+002h]
          cmp   bx, ax
          jle   LAB_0040350b
          movsx ecx, bx
          movsx eax, ax
          add   ecx, 0FFFFFFFEh
          cmp   eax, ecx
          jg    LAB_0040351c
          jmp   LAB_0040351a
LAB_0040350b:     movsx ecx, word ptr [esi]
          movsx esi, bx
          movsx eax, ax
          add   ecx, esi
          cmp   eax, ecx
          jl    LAB_0040351c
LAB_0040351a:     mov   eax, ecx
LAB_0040351c:     mov   ecx, dword ptr [esp+010h]
          mov   word ptr [ebp+048h], ax
          imul  ecx, edx
          pop   edi
          mov   word ptr [ebp+046h], cx
          mov   eax, ebp
          pop   esi
          pop   ebp
          pop   ebx
          pop   ecx
          ret
LAB_00403533:
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
@updateActorVelMaybe@8 endp
~

COMMENT ~
@updateActorType1_Beginner@4 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, dword ptr [esi+01Ch]
          test  esi, esi
          jnz   LAB_0040355a
          mov   edx, 000000852h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040355a:     cmp   dword ptr [esi+018h], 000000001h
          jz    LAB_0040356f
          mov   edx, 000000853h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040356f:     cmp   edi, 000000019h
          jge   LAB_00403604
          mov   ecx, esi
          call  @updateActorPositionWithVelocityMaybe@4
          mov   esi, eax
          lea   eax, dword ptr [edi-016h]
          cmp   eax, 000000005h
          jb    LAB_00403598
          mov   edx, 000000857h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403598:     lea   edx, dword ptr [edi-016h]
          mov   ecx, esi
          shl   edx, 004h
          add   edx, offset beginnerActorMovementTbl    ; <a490>
          call  @updateActorVelMaybe@8
          mov   ecx, 00000000Ch
          mov   esi, eax
          call  @random@4
          test  ax, ax
          jnz   LAB_004035f9
          mov   ecx, 000000003h
          call  @random@4
          movsx eax, ax
          sub   eax, 000000000h
          jz    LAB_004035f4
          dec   eax
          jz    LAB_004035e4
          dec   eax
          jnz   LAB_004035f9
          mov   edi, 000000018h
          mov   ecx, esi
          mov   edx, edi
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_004035e4:     mov   edi, 000000017h
          mov   ecx, esi
          mov   edx, edi
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_004035f4:     mov   edi, 000000016h
LAB_004035f9:     mov   edx, edi
          mov   ecx, esi
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_00403604:     mov   eax, esi
          pop   edi
          pop   esi
          ret
LAB_00403609:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorType1_Beginner@4 endp
~

COMMENT ~
@updateActorType2_dog@4 proc
          push  esi
          push  edi
          mov   edi, ecx
          mov   eax, dword ptr [edi+018h]
          mov   esi, dword ptr [edi+01Ch]
          cmp   eax, 000000002h
          jz    LAB_0040362e
          mov   edx, 000000872h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040362e:     lea   eax, dword ptr [esi-01Bh]
          cmp   eax, 000000003h
          ja    LAB_0040371f
          jmp   dword ptr [eax*4+LAB_00403734]  ; <3734>
LAB_00403641:     mov   ecx, 000000003h
          mov   esi, 00000001Ch
          call  @random@4
          dec   eax
          mov   ecx, edi
          mov   word ptr [edi+048h], ax
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_00403668:     mov   ecx, edi
          mov   esi, 00000001Bh
          mov   word ptr [edi+046h], 00004h
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_00403686:     xor   eax, eax
          mov   ecx, 000000020h
          mov   word ptr [edi+048h], ax
          mov   word ptr [edi+046h], ax
          call  @random@4
          mov   si, ax
          mov   ecx, edi
          neg   si
          sbb   esi, esi
          and   esi, 000000003h
          add   esi, 00000001Bh
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004036bb:     mov   ecx, 000000064h
          call  @random@4
          test  ax, ax
          jz    LAB_004036e2
          mov   ecx, edi
          mov   esi, 00000001Dh
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004036e2:     mov   cx, word ptr [edi+042h]
          mov   ax, word ptr [edi+044h]
          mov   si, word ptr [edi+040h]
          sub   cx, 000000002h
          push  eax
          push  ecx
          mov   edx, 000000052h
          mov   ecx, 000000011h
          sub   si, 000000004h
          call  @addActorOfTypeWithSpriteIdx@8
          mov   ecx, eax
          mov   edx, esi
          call  @updateActorPositionMaybe@16
          mov   ecx, offset sound_8.soundResource       ; <c608>
          mov   esi, 00000001Bh
          call  @playSound@4
LAB_0040371f:     mov   ecx, edi
          call  @updateActorPositionWithVelocityMaybe@4
          mov   edx, esi
          mov   ecx, eax
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_00403731:
          db 08Dh
          db 049h
          db 000h
LAB_00403734:
DAT_00403734  dword offset LAB_00403641
DAT_00403738  dword offset LAB_00403668
DAT_0040373c  dword offset LAB_00403686
DAT_00403740  dword offset LAB_004036bb
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
@updateActorType2_dog@4 endp
~

COMMENT ~
@updateActorType9_treeOnFire@4 proc
          push  esi
          push  edi
          mov   edi, ecx
          mov   eax, dword ptr [edi+018h]
          mov   esi, dword ptr [edi+01Ch]
          cmp   eax, 000000009h
          jz    LAB_0040376e
          mov   edx, 00000089Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040376e:     cmp   esi, 000000038h
          jge   LAB_00403782
          mov   edx, 00000089Dh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403782:     cmp   esi, 00000003Ch
          jl    LAB_00403796
          mov   edx, 00000089Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403796:     inc   esi
          cmp   esi, 00000003Ch
          jl    LAB_004037a1
          mov   esi, 000000038h
LAB_004037a1:     mov   ecx, edi
          mov   edx, esi
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_004037ac:
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorType9_treeOnFire@4 endp
~

COMMENT ~
@updateActorTypeA_walkingTree@4 proc
          push  esi
          mov   esi, ecx
          push  edi
          mov   eax, dword ptr [esi+018h]
          mov   edi, dword ptr [esi+01Ch]
          cmp   eax, 00000000Ah
          jz    LAB_004037ce
          mov   edx, 0000008A9h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004037ce:     cmp   edi, 00000003Ch
          jge   LAB_004037e2
          mov   edx, 0000008AAh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004037e2:     cmp   edi, 000000040h
          jl    LAB_004037f6
          mov   edx, 0000008ABh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004037f6:     lea   eax, dword ptr [edi-03Ch]
          cmp   eax, 000000003h
          ja    LAB_004038e9
          jmp   dword ptr [eax*4+LAB_004038fc]  ; <38fc>
LAB_00403809:     cmp   word ptr [esi+046h], 000000000h
          jz    LAB_0040381f
          mov   edx, 0000008AFh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040381f:     mov   ecx, 000000064h
          call  @random@4
          test  ax, ax
          jnz   LAB_004038e9
          mov   ecx, 000000002h
          mov   edi, 00000003Dh
          call  @random@4
          lea   eax, dword ptr [eax+eax*1-001h]
          mov   ecx, esi
          mov   word ptr [esi+046h], ax
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, edi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_0040385c:     cmp   word ptr [esi+046h], 000000000h
          jnz   LAB_00403872
          mov   edx, 0000008B8h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403872:     mov   ecx, 00000000Ah
          call  @random@4
          test  ax, ax
          jz    LAB_004038a2
          xor   ecx, ecx
          cmp   word ptr [esi+046h], cx
          setge cl
          add   ecx, 00000003Eh
          mov   edi, ecx
          mov   ecx, esi
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, edi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004038a2:     mov   ecx, esi
          mov   edi, 00000003Ch
          mov   word ptr [esi+046h], 00000h
          call  @updateActorPositionWithVelocityMaybe@4
          mov   ecx, eax
          mov   edx, edi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004038c0:     cmp   word ptr [esi+046h], 000000000h
          jl    LAB_004038e4
          mov   edx, 0000008C3h
          jmp   LAB_004038da
LAB_004038ce:     cmp   word ptr [esi+046h], 000000000h
          jg    LAB_004038e4
          mov   edx, 0000008C8h
LAB_004038da:     mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004038e4:     mov   edi, 00000003Dh
LAB_004038e9:     mov   ecx, esi
          call  @updateActorPositionWithVelocityMaybe@4
          mov   edx, edi
          mov   ecx, eax
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_004038fb:
          db 090h
LAB_004038fc:
DAT_004038fc  dword offset LAB_00403809
DAT_00403900  dword offset LAB_0040385c
DAT_00403904  dword offset LAB_004038c0
DAT_00403908  dword offset LAB_004038ce
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorTypeA_walkingTree@4 endp
~

COMMENT ~
@updateActorType3_snowboarder@4 proc
          push  esi
          push  edi
          mov   edi, ecx
          mov   eax, dword ptr [edi+018h]
          mov   esi, dword ptr [edi+01Ch]
          cmp   eax, 000000003h
          jz    LAB_0040392e
          mov   edx, 0000008E2h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040392e:     mov   ecx, edi
          call  @updateActorPositionWithVelocityMaybe@4
          mov   edi, eax
          lea   eax, dword ptr [esi-01Fh]
          cmp   eax, 000000008h
          jb    LAB_0040394e
          mov   edx, 0000008E5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040394e:     lea   edx, dword ptr [esi-01Fh]
          mov   ecx, edi
          shl   edx, 004h
          add   edx, offset snowboarderActorMovementTbl ; <a4e0>
          call  @updateActorVelMaybe@8
          mov   edi, eax
          mov   eax, esi
          sub   eax, 00000001Fh
          jz    LAB_004039d8
          dec   eax
          jz    LAB_004039b8
          dec   eax
          jz    LAB_004039a0
          cmp   esi, 000000022h
          jl    LAB_0040397a
          cmp   esi, 000000027h
          jl    LAB_00403989
LAB_0040397a:     mov   edx, 0000008FAh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403989:     inc   esi
          cmp   esi, 000000027h
          jnz   LAB_004039ec
          mov   esi, 000000020h
          mov   ecx, edi
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004039a0:     cmp   word ptr [edi+044h], 000000000h
          jnz   LAB_004039ec
          mov   esi, 000000020h
          mov   ecx, edi
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004039b8:     mov   ecx, 00000000Ah
          call  @random@4
          test  ax, ax
          jnz   LAB_004039ec
          mov   esi, 00000001Fh
          mov   ecx, edi
          mov   edx, esi
          call  @setActorFrameNo@8
          pop   edi
          pop   esi
          ret
LAB_004039d8:     mov   ecx, 00000000Ah
          call  @random@4
          test  ax, ax
          jnz   LAB_004039ec
          mov   esi, 000000020h
LAB_004039ec:     mov   ecx, edi
          mov   edx, esi
          pop   edi
          pop   esi
          jmp   @setActorFrameNo@8
LAB_004039f7:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorType3_snowboarder@4 endp
~

COMMENT ~
@handleActorCollision@8 proc
          sub   esp, 00000000Ch
          push  esi
          mov   esi, ecx
          push  edi
          mov   edi, edx
          test  esi, esi
          jnz   LAB_00403a1c
          mov   edx, 00000092Eh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403a1c:     test  edi, edi
          jnz   LAB_00403a2f
          mov   edx, 00000092Fh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403a2f:     cmp   dword ptr [esi+018h], 00000000Bh
          jl    LAB_00403a3d
          mov   eax, esi
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403a3d:     push  ebx
          mov   bx, word ptr [esi+042h]
          push  ebp
          mov   bp, word ptr [edi+042h]
          mov   ecx, esi
          call  @getLinkedActorIfExists@4
          mov   ax, word ptr [eax+042h]
          mov   ecx, edi
          mov   word ptr [esp+018h], ax
          call  @getLinkedActorIfExists@4
          mov   ax, word ptr [eax+042h]
          mov   ecx, dword ptr [esp+018h]
          cmp   bx, bp
          jl    LAB_00403a70
          cmp   cx, ax
          jle   LAB_00403a7a
LAB_00403a70:     cmp   bx, bp
          jg    LAB_00403a8e
          cmp   cx, ax
          jl    LAB_00403a8e
LAB_00403a7a:     cmp   bx, bp
          jnz   LAB_00403a84
          cmp   cx, ax
          jz    LAB_00403a8e
LAB_00403a84:     mov   dword ptr [esp+018h], 000000001h
          jmp   LAB_00403a96
LAB_00403a8e:     mov   dword ptr [esp+018h], 000000000h
LAB_00403a96:     mov   edx, dword ptr [edi+018h]
          mov   eax, dword ptr [esi+014h]
          mov   ecx, dword ptr [esi+01Ch]
          mov   bx, word ptr [esi+044h]
          mov   ax, word ptr [eax+00Ch]
          mov   dword ptr [esp+014h], edx
          mov   edx, dword ptr [edi+014h]
          mov   dword ptr [esp+010h], ecx
          mov   cx, word ptr [edi+044h]
          add   ax, bx
          mov   bp, word ptr [edx+00Ch]
          mov   edx, dword ptr [esi+018h]
          add   bp, cx
          cmp   edx, 00000000Ah
          ja    LAB_00403fb2
          jmp   dword ptr [edx*4+LAB_00403fd4]  ; <3fd4>
LAB_00403ad3:     mov   dword ptr [esp+010h], 00000003Ch
          mov   ecx, esi
          mov   edx, dword ptr [esp+010h]
          mov   word ptr [esi+046h], 00000h
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403af4:     cmp   edi, dword ptr [playerActor]    ; <c72c>
          jnz   LAB_00403fc1
          mov   eax, dword ptr [esp+014h]
          xor   ebx, ebx
          cmp   eax, ebx
          jz    LAB_00403b19
          mov   edx, 000000959h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403b19:     mov   ecx, offset sound_7.soundResource       ; <c6e0>
          call  @playSound@4
          test  byte ptr [edi+04Ch], 001h
          jz    LAB_00403b32
          mov   ecx, edi
          call  @duplicateAndLinkActor@4
          jmp   LAB_00403b34
LAB_00403b32:     mov   eax, edi
LAB_00403b34:     mov   ecx, eax
          call  @actorSetFlag8IfFlag1IsUnset@4
          cmp   dword ptr [esi+00Ch], ebx
          jnz   LAB_00403b4f
          mov   edx, 00000095Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403b4f:     mov   ecx, dword ptr [esi+00Ch]
          mov   eax, 000000032h
          mov   dword ptr [esp+010h], eax
          mov   dword ptr [ecx+010h], eax
          mov   edx, dword ptr [esi+00Ch]
          mov   word ptr [esi+046h], bx
          mov   word ptr [edx+01Ah], bx
          mov   eax, dword ptr [esi+00Ch]
          mov   word ptr [esi+048h], bx
          mov   word ptr [eax+01Ch], bx
          mov   ecx, dword ptr [esi+00Ch]
          mov   edx, dword ptr [currentTickCount]       ; <c698>
          mov   dword ptr [ecx+020h], edx
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403b93:     cmp   dword ptr [esp+010h], 000000011h
          jz    LAB_00403fc1
          mov   edx, dword ptr [esp+014h]
          dec   edx
          cmp   edx, 000000010h
          ja    LAB_00403fc1
          jmp   dword ptr [edx*4+LAB_00404000]  ; <4000>
LAB_00403bb3:     test  bx, bx
          jg    LAB_00403bc3
          mov   word ptr [esi+04Ah], 00004h
          jmp   LAB_00403cb4
LAB_00403bc3:     cmp   bx, bp
          jge   LAB_00403fc1
LAB_00403bcc:     movsx eax, word ptr [esi+048h]
          cdq
          sub   eax, edx
          mov   ecx, 000000001h
          sar   eax, 1h
          mov   word ptr [esi+04Ah], ax
          call  @addStylePoints@4
          mov   ecx, offset sound_2.soundResource       ; <c768>
LAB_00403be8:     call  @playSound@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403c00:     mov   eax, dword ptr [esp+018h]
          test  eax, eax
          jz    LAB_00403c15
          movsx eax, word ptr [esi+048h]
          cdq
          sub   eax, edx
          sar   eax, 1h
          mov   word ptr [esi+048h], ax
LAB_00403c15:     cmp   word ptr [edi+010h], 000000052h
          jnz   LAB_00403fc1
          mov   ecx, 0FFFFFFF0h
          call  @addStylePoints@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403c3d:     mov   eax, dword ptr [esp+010h]
          test  eax, eax
          jnz   LAB_00403fc1
          mov   ax, word ptr [esi+048h]
          mov   dword ptr [esp+010h], 00000000Dh
          cmp   ax, 00004h
          mov   word ptr [esi+04Ah], 00001h
          jle   LAB_00403fc1
          movsx eax, ax
          cdq
          sub   eax, edx
          mov   edx, dword ptr [esp+010h]
          sar   eax, 1h
          mov   ecx, esi
          mov   word ptr [esi+048h], ax
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403c84:     mov   eax, dword ptr [esp+018h]
          test  eax, eax
          jz    LAB_00403fc1
          movsx eax, bp
          cdq
          sub   eax, edx
          movsx ecx, bx
          sar   eax, 1h
          cmp   ecx, eax
          jge   LAB_00403fc1
          mov   ax, word ptr [esi+048h]
          test  ax, ax
          jle   LAB_00403fc1
          mov   word ptr [esi+04Ah], ax
LAB_00403cb4:     mov   ecx, 000000001h
          mov   dword ptr [esp+010h], 00000000Dh
          call  @addStylePoints@4
          mov   ecx, offset sound_2.soundResource       ; <c768>
          call  @playSound@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403ce3:     test  bx, bx
          jle   LAB_00403d3e
          cmp   bx, bp
          jg    LAB_00403cfe
          mov   eax, dword ptr [esp+018h]
          test  eax, eax
          jz    LAB_00403fc1
          jmp   LAB_00403bcc
LAB_00403cfe:     cmp   word ptr [edi+010h], 000000056h
          jnz   LAB_00403fc1
          test  byte ptr [edi+04Ch], 001h
          jz    LAB_00403d18
          mov   ecx, edi
          call  @duplicateAndLinkActor@4
          jmp   LAB_00403d1a
LAB_00403d18:     mov   eax, edi
LAB_00403d1a:     mov   ecx, eax
          call  @actorSetFlag8IfFlag1IsUnset@4
          mov   ecx, 000000064h
          call  @addStylePoints@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403d3e:     cmp   bx, bp
          jg    LAB_00403e60
          cmp   cx, ax
          jg    LAB_00403e60
          mov   eax, dword ptr [esp+018h]
          test  eax, eax
          jz    LAB_00403fc1
          cmp   dword ptr [esp+014h], 00000000Dh
          jnz   LAB_00403dba
          mov   eax, dword ptr [esi+014h]
          mov   ecx, dword ptr [edi+014h]
          mov   ax, word ptr [eax+00Ah]
          mov   cx, word ptr [ecx+00Ah]
          cmp   ax, cx
          jle   LAB_00403d7b
          movsx ecx, ax
          jmp   LAB_00403d7e
LAB_00403d7b:     movsx ecx, cx
LAB_00403d7e:     movsx eax, word ptr [esi+040h]
          movsx edx, word ptr [edi+040h]
          sub   eax, edx
          cdq
          mov   ebp, eax
          mov   eax, ecx
          xor   ebp, edx
          sub   ebp, edx
          cdq
          sub   eax, edx
          sar   eax, 1h
          cmp   ebp, eax
          jle   LAB_00403dba
          movsx eax, word ptr [esi+048h]
          cdq
          sub   eax, edx
          mov   edx, dword ptr [esp+010h]
          sar   eax, 1h
          mov   ecx, esi
          mov   word ptr [esi+048h], ax
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403dba:     test  bx, bx
          jnz   LAB_00403dfa
          cmp   word ptr [esi+04Ah], bx
          jnz   LAB_00403dfa
          mov   dword ptr [esp+010h], 00000000Bh
LAB_00403dcd:     cmp   word ptr [esi+048h], 000000000h
          jge   LAB_00403e39
          cmp   word ptr [edi+010h], 00000002Eh
          jnz   LAB_00403e39
          mov   edx, 000000056h
          mov   ecx, edi
          call  @actorSetSpriteIdx@8
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403dfa:     cmp   word ptr [edi+010h], 000000032h
          mov   dword ptr [esp+010h], 000000011h
          jnz   LAB_00403dcd
          mov   edx, 000000038h
          mov   ecx, edi
          mov   dword ptr [edi+018h], 000000009h
          call  @setActorFrameNo@8
          mov   ecx, 000000010h
          call  @addStylePoints@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403e39:     mov   ecx, 0FFFFFFE0h
          call  @addStylePoints@4
          mov   ecx, offset sound_1.soundResource       ; <c6c0>
          call  @playSound@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403e60:     cmp   dword ptr [esp+014h], 000000009h
          jnz   LAB_00403e97
          mov   ecx, 0000003E8h
          call  @addStylePoints@4
          mov   edx, 000000032h
          mov   ecx, edi
          mov   dword ptr [edi+018h], 00000000Dh
          call  @actorSetSpriteIdx@8
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403e97:     mov   ecx, 000000006h
          call  @addStylePoints@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403eb4:     mov   eax, dword ptr [esp+014h]
          cmp   eax, 000000010h
          ja    LAB_00403fc1
          xor   ecx, ecx
          mov   cl, byte ptr [eax+LAB_00404054] ; <4054>
          jmp   dword ptr [ecx*4+LAB_00404044]  ; <4044>
LAB_00403ed0:     cmp   bx, bp
          jge   LAB_00403fc1
          movsx eax, word ptr [esi+048h]
          cdq
          sub   eax, edx
          mov   ecx, offset sound_5.soundResource       ; <c750>
          sar   eax, 1h
          mov   word ptr [esi+04Ah], ax
          mov   dword ptr [esp+010h], 000000021h
          call  @playSound@4
          mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403f0b:     mov   ecx, 000000014h
          call  @addStylePoints@4
LAB_00403f15:     cmp   bx, bp
          jge   LAB_00403fc1
          mov   ecx, dword ptr [esp+010h]
          mov   eax, 000000022h
          cmp   ecx, eax
          jz    LAB_00403fc1
          mov   edx, eax
          mov   ecx, esi
          mov   dword ptr [esp+010h], eax
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403f44:     cmp   dword ptr [esp+010h], 000000019h
          jge   LAB_00403fc1
          mov   eax, dword ptr [esp+014h]
          test  eax, eax
          jnz   LAB_00403f5d
          mov   ecx, 000000014h
          call  @addStylePoints@4
LAB_00403f5d:     xor   edx, edx
          mov   ecx, offset sound_6.soundResource       ; <c628>
          cmp   word ptr [edi+044h], dx
          setg  dl
          add   edx, 000000019h
          mov   dword ptr [esp+010h], edx
          jmp   LAB_00403be8
LAB_00403f77:     mov   eax, dword ptr [esp+010h]
          mov   ebx, 00000001Dh
          cmp   eax, ebx
          jge   LAB_00403fc1
          cmp   word ptr [edi+046h], 000000000h
          jnz   LAB_00403f92
          cmp   word ptr [edi+048h], 000000000h
          jz    LAB_00403fc1
LAB_00403f92:     mov   eax, dword ptr [esp+014h]
          test  eax, eax
          jnz   LAB_00403fa4
          mov   ecx, 000000003h
          call  @addStylePoints@4
LAB_00403fa4:     mov   dword ptr [esp+010h], ebx
          mov   ecx, offset sound_3.soundResource       ; <c5d0>
          jmp   LAB_00403be8
LAB_00403fb2:     mov   edx, 000000948h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00403fc1:     mov   edx, dword ptr [esp+010h]
          mov   ecx, esi
          call  @setActorFrameNo@8
          pop   ebp
          pop   ebx
          pop   edi
          pop   esi
          add   esp, 00000000Ch
          ret
LAB_00403fd4:
DAT_00403fd4  dword offset LAB_00403b93
DAT_00403fd8  dword offset LAB_00403f44
DAT_00403fdc  dword offset LAB_00403f77
DAT_00403fe0  dword offset LAB_00403eb4
DAT_00403fe4  dword offset LAB_00403fc1
DAT_00403fe8  dword offset LAB_00403af4
DAT_00403fec  dword offset LAB_00403af4
DAT_00403ff0  dword offset LAB_00403af4
DAT_00403ff4  dword offset LAB_00403af4
DAT_00403ff8  dword offset LAB_00403fc1
DAT_00403ffc  dword offset LAB_00403ad3
LAB_00404000:
DAT_00404000  dword offset LAB_00403d3e
DAT_00404004  dword offset LAB_00403c00
DAT_00404008  dword offset LAB_00403d3e
DAT_0040400c  dword offset LAB_00403d3e
DAT_00404010  dword offset LAB_00403fc1
DAT_00404014  dword offset LAB_00403fc1
DAT_00404018  dword offset LAB_00403fc1
DAT_0040401c  dword offset LAB_00403fc1
DAT_00404020  dword offset LAB_00403d3e
DAT_00404024  dword offset LAB_00403d3e
DAT_00404028  dword offset LAB_00403c3d
DAT_0040402c  dword offset LAB_00403c00
DAT_00404030  dword offset LAB_00403d3e
DAT_00404034  dword offset LAB_00403ce3
DAT_00404038  dword offset LAB_00403bb3
DAT_0040403c  dword offset LAB_00403c84
DAT_00404040  dword offset LAB_00403c00
LAB_00404044:
DAT_00404044  dword offset LAB_00403f0b
DAT_00404048  dword offset LAB_00403f15
DAT_0040404c  dword offset LAB_00403ed0
DAT_00404050  dword offset LAB_00403fc1
LAB_00404054:
          db 000h
          db 001h
          db 003h
          db 001h
          db 003h
          db 003h
          db 003h
          db 003h
          db 003h
          db 003h
          db 003h
          db 003h
          db 003h
          db 001h
          db 001h
          db 002h
          db 002h
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
@handleActorCollision@8 endp
~

COMMENT ~
@getLinkedActorIfExists@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_00404086
          mov   edx, 0000003C5h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00404086:     mov   eax, dword ptr [esi+004h]
          test  eax, eax
          jnz   LAB_0040408f
          mov   eax, esi
LAB_0040408f:     pop   esi
          ret
LAB_00404091:
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
@getLinkedActorIfExists@4 endp
~

COMMENT ~
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
~

COMMENT ~
@addActorForPermObject@4 proc
          sub   esp, 000000010h
          push  ebx
          push  ebp
          push  esi
          mov   esi, ecx
          test  esi, esi
          push  edi
          jnz   LAB_0040414c
          mov   edx, 000000A2Ch
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040414c:     cmp   dword ptr [esi], 000000000h
          jnz   LAB_004041b0
          mov   bp, word ptr [esi+018h]
          mov   bx, word ptr [esi+016h]
          mov   di, word ptr [esi+014h]
          mov   edx, dword ptr [esi+004h]
          push  ebp
          push  ebx
          push  edi
          lea   ecx, dword ptr [esp+01Ch]
          call  @updateRectForSpriteAtLocation@20
          mov   edx, offset windowClientRectWith120Margin.left  ; <c680>
          lea   ecx, dword ptr [esp+010h]
          call  @doRectsOverlap@8
          test  eax, eax
          jz    LAB_004041b0
          mov   dx, word ptr [esi+008h]
          test  dx, dx
          jnz   LAB_00404194
          mov   edx, dword ptr [esi+010h]
          mov   ecx, dword ptr [esi+00Ch]
          call  @addActorOfType@8
          jmp   LAB_0040419c
LAB_00404194:     mov   ecx, dword ptr [esi+00Ch]
          call  @addActorOfTypeWithSpriteIdx@8
LAB_0040419c:     test  eax, eax
          jz    LAB_004041b0
          push  ebp
          push  ebx
          mov   edx, edi
          mov   ecx, eax
          call  @updateActorPositionMaybe@16
          mov   dword ptr [esi], eax
          mov   dword ptr [eax+00Ch], esi
LAB_004041b0:     mov   eax, dword ptr [esi]
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 000000010h
          ret
LAB_004041ba:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@addActorForPermObject@4 endp
~

COMMENT ~
@updatePermObject@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          push  edi
          jnz   LAB_004041d7
          mov   edx, 000000AE7h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004041d7:     mov   ax, word ptr [esi+01Ah]
          mov   cx, word ptr [esi+01Ch]
          add   word ptr [esi+014h], ax
          mov   dx, word ptr [esi+01Eh]
          mov   eax, dword ptr [esi+00Ch]
          add   word ptr [esi+016h], cx
          add   word ptr [esi+018h], dx
          cmp   eax, 000000004h
          jz    LAB_00404218
          jle   LAB_00404207
          cmp   eax, 000000008h
          jg    LAB_00404207
          mov   ecx, esi
          call  @FUN_00404350@4
          jmp   LAB_0040421f
LAB_00404207:     mov   edx, 000000AF9h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
          jmp   LAB_0040421f
LAB_00404218:     mov   ecx, esi
          call  @updatePermObjectActorType4@4
LAB_0040421f:     mov   edi, dword ptr [esi]
          test  edi, edi
          jz    LAB_0040427f
          jnz   LAB_00404236
          mov   edx, 000000AFEh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00404236:     mov   eax, dword ptr [edi+00Ch]
          test  eax, eax
          jnz   LAB_0040424c
          mov   edx, 000000AFFh
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040424c:     cmp   dword ptr [edi+00Ch], esi
          jz    LAB_00404260
          mov   edx, 000000B00h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00404260:     mov   ax, word ptr [esi+018h]
          mov   cx, word ptr [esi+016h]
          mov   dx, word ptr [esi+014h]
          push  eax
          push  ecx
          mov   ecx, edi
          call  @updateActorPositionMaybe@16
          mov   edx, dword ptr [esi+010h]
          mov   ecx, eax
          call  @setActorFrameNo@8
LAB_0040427f:     pop   edi
          pop   esi
          ret
LAB_00404282:
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
@updatePermObject@4 endp
~

COMMENT ~
@updatePermObjectActorType4@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_004042a6
          mov   edx, 000000A49h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004042a6:     cmp   dword ptr [esi+00Ch], 000000004h
          jz    LAB_004042bb
          mov   edx, 000000A4Ah
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_004042bb:     mov   ax, word ptr [esi+016h]
          cmp   ax, 0FC00h
          jg    LAB_004042da
          mov   dword ptr [esi+010h], 000000029h
          mov   word ptr [esi+01Ch], 00002h
          mov   word ptr [esi+014h], 0FF70h
          pop   esi
          ret
LAB_004042da:     cmp   ax, 05C00h
          jl    LAB_004042f5
          mov   dword ptr [esi+010h], 000000027h
          mov   word ptr [esi+01Ch], 0FFFEh
          mov   word ptr [esi+014h], 0FF90h
          pop   esi
          ret
LAB_004042f5:     cmp   dword ptr [esi], 000000000h
          jz    LAB_0040433f
          cmp   dword ptr [esi+010h], 000000027h
          jnz   LAB_0040433f
          mov   ecx, 0000003E8h
          call  @random@4
          test  ax, ax
          jnz   LAB_0040433f
          mov   ax, word ptr [esi+018h]
          mov   cx, word ptr [esi+016h]
          push  edi
          mov   di, word ptr [esi+014h]
          push  eax
          push  ecx
          mov   edx, 000000021h
          mov   ecx, 000000003h
          call  @addActorOfType@8
          mov   ecx, eax
          mov   dx, di
          call  @updateActorPositionMaybe@16
          mov   dword ptr [esi+010h], 000000028h
          pop   edi
LAB_0040433f:     pop   esi
          ret
LAB_00404341:
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
@updatePermObjectActorType4@4 endp
~

COMMENT ~
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
~

@FUN_004046e0@4 proc
          push  ecx
          mov   eax, dword ptr [skierScreenYOffset]     ; <c5fc>
          push  ebx
          mov   ebx, dword ptr [windowClientRectWith120Margin.top]      ; <c684>
          push  ebp
          mov   ebp, dword ptr [windowClientRectWith120Margin.bottom]   ; <c68c>
          push  esi
          push  edi
          sub   ebx, eax
          sub   ebp, eax
          mov   edi, ecx
          sub   ebx, 00000003Ch
          add   ebp, 00000003Ch
          mov   esi, dword ptr [edi+008h]
          test  edi, edi
          jnz   LAB_00404718
          mov   edx, 000000B21h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00404718:     cmp   esi, dword ptr [edi]
          jae   LAB_0040472b
          mov   edx, 000000B22h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040472b:     cmp   esi, dword ptr [edi+004h]
          jbe   LAB_0040473f
          mov   edx, 000000B23h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040473f:     mov   eax, dword ptr [edi+004h]
          cmp   esi, eax
          mov   dword ptr [esp+010h], eax
          jae   LAB_00404769
          movsx eax, word ptr [playerY] ; <c5f2>
          movsx ecx, bx
LAB_00404754:     movsx edx, word ptr [esi+016h]
          sub   edx, eax
          cmp   edx, ecx
          jge   LAB_00404769
          mov   edx, dword ptr [esp+010h]
          add   esi, 000000024h
          cmp   esi, edx
          jb    LAB_00404754
LAB_00404769:     mov   edx, dword ptr [edi]
          cmp   esi, edx
          jbe   LAB_0040478a
          movsx eax, word ptr [playerY] ; <c5f2>
          movsx ecx, bx
LAB_00404779:     movsx ebx, word ptr [esi+016h]
          sub   ebx, eax
          cmp   ebx, ecx
          jl    LAB_0040478a
          sub   esi, 000000024h
          cmp   esi, edx
          ja    LAB_00404779
LAB_0040478a:     mov   eax, dword ptr [esp+010h]
          mov   dword ptr [edi+008h], esi
          cmp   esi, eax
          jae   LAB_004047b8
          movsx ebx, bp
LAB_00404798:     movsx eax, word ptr [esi+016h]
          movsx ecx, word ptr [playerY] ; <c5f2>
          sub   eax, ecx
          cmp   eax, ebx
          jge   LAB_004047b8
          mov   ecx, esi
          add   esi, 000000024h
          call  @addActorForPermObject@4
          cmp   esi, dword ptr [edi+004h]
          jb    LAB_00404798
LAB_004047b8:     pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          pop   ecx
          ret
LAB_004047be:
          db 090h
          db 090h
@FUN_004046e0@4 endp

COMMENT ~
_timerCallbackFunc proc
          mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004047ce
          call  _timerUpdateFunc
LAB_004047ce:     mov   eax, 000000001h
          ret   00010h
LAB_004047d6:
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
_timerCallbackFunc endp
~

COMMENT ~
_WinMain@16 proc
          mov   eax, dword ptr [esp+00Ch]
          sub   esp, 00000001Ch
          push  offset s_nosound_0040c0fc       ; <c0fc>
          push  eax
          call  dword ptr [__imp__lstrcmpiA@8]  ; <lstrcmpiA>
          test  eax, eax
          jnz   LAB_00404801
          mov   dword ptr [isSoundDisabled], 000000001h ; <c794>
LAB_00404801:     call  _allocateMemory
          test  eax, eax
          jnz   LAB_00404810
          add   esp, 00000001Ch
          ret   00010h
LAB_00404810:     call  _resetGame
          test  eax, eax
          jnz   LAB_0040481f
          add   esp, 00000001Ch
          ret   00010h
LAB_0040481f:     mov   ecx, dword ptr [esp+02Ch]
          mov   edx, dword ptr [esp+024h]
          push  ecx
          mov   ecx, dword ptr [esp+024h]
          call  @initWindows@12
          test  eax, eax
          jnz   LAB_0040483b
          add   esp, 00000001Ch
          ret   00010h
LAB_0040483b:     call  _setupGame
          test  eax, eax
          jnz   LAB_0040485e
          mov   edx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  edx
          call  dword ptr [__imp__DestroyWindow@4]      ; <DestroyWindow>
          call  _cleanupSound
          xor   eax, eax
          add   esp, 00000001Ch
          ret   00010h
LAB_0040485e:     push  esi
          mov   esi, dword ptr [__imp__GetMessageA@16]  ; <GetMessageA>
          push  000000000h
          push  000000000h
          lea   eax, dword ptr [esp+00Ch]
          push  000000000h
          push  eax
          call  esi
          test  eax, eax
          jz    LAB_004048a5
          push  ebx
          mov   ebx, dword ptr [__imp__DispatchMessageA@4]      ; <DispatchMessageA>
          push  edi
          mov   edi, dword ptr [__imp__TranslateMessage@4]      ; <TranslateMessage>
LAB_00404884:     lea   ecx, dword ptr [esp+00Ch]
          push  ecx
          call  edi
          lea   edx, dword ptr [esp+00Ch]
          push  edx
          call  ebx
          push  000000000h
          push  000000000h
          lea   eax, dword ptr [esp+014h]
          push  000000000h
          push  eax
          call  esi
          test  eax, eax
          jnz   LAB_00404884
          pop   edi
          pop   ebx
LAB_004048a5:     call  _cleanupSound
          mov   eax, dword ptr [esp+00Ch]
          pop   esi
          add   esp, 00000001Ch
          ret   00010h
LAB_004048b5:
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
_WinMain@16 endp
~

COMMENT ~
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
          mov   dword ptr [PTR_0040c758], eax   ; <c758>
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
~

COMMENT ~
@showErrorMessage@4 proc
          push  esi
          mov   esi, ecx
          push  000000030h
          mov   ecx, 000000001h
          call  @getCachedString@4
          push  eax
          push  esi
          push  000000000h
          call  dword ptr [__imp__MessageBoxA@16]       ; <MessageBoxA>
          pop   esi
          ret
LAB_0040496b:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@showErrorMessage@4 endp
~

_resetGame proc
          push  esi
          call  dword ptr [__imp__GetTickCount@0]       ; <GetTickCount>
          mov   dword ptr [currentTickCount], eax       ; <c698>
          push  eax
          call  _srand
          add   esp, 000000004h
          call  _setupActorList
          xor   esi, esi
          mov   dword ptr [playerActorPtrMaybe_1], esi  ; <c64c>
          mov   dword ptr [playerActor], esi    ; <c72c>
          mov   dword ptr [totalAreaOfActorSprites], esi        ; <c6fc>
          call  _resetPermObjectCount
          mov   eax, 000000001h
          mov   dword ptr [isTurboMode], esi    ; <c670>
          mov   word ptr [playerY], si  ; <c5f2>
          mov   word ptr [playerX], si  ; <c640>
          mov   word ptr [DAT_0040c5d8], si     ; <c5d8>
          mov   word ptr [DAT_0040c714], si     ; <c714>
          mov   dword ptr [stylePoints], esi    ; <c6a8>
          mov   dword ptr [INT_0040c964], esi   ; <c964>
          mov   dword ptr [isSsGameMode], esi   ; <c95c>
          mov   dword ptr [INT_0040c960], esi   ; <c960>
          mov   dword ptr [isGsGameMode], esi   ; <c958>
          mov   dword ptr [elapsedTime], esi    ; <c944>
          mov   dword ptr [updateTimerDurationMillis], 000000028h       ; <c678>
          mov   dword ptr [redrawRequired], eax ; <c610>
          pop   esi
          ret
LAB_004049ff:
          db 090h
_resetGame endp

COMMENT ~
_setupActorList proc
          push  esi
          mov   esi, dword ptr [actors] ; <c648>
          xor   edx, edx
          mov   dword ptr [actorListPtr], 000000000h    ; <c618>
          mov   dword ptr [currentFreeActor], esi       ; <c744>
          mov   ecx, 000000001h
          xor   eax, eax
          jmp   LAB_00404a28
LAB_00404a22:     mov   esi, dword ptr [actors] ; <c648>
LAB_00404a28:     lea   ecx, dword ptr [ecx+ecx*4]
          lea   eax, dword ptr [eax+eax*4]
          shl   ecx, 004h
          shl   eax, 004h
          add   ecx, esi
          inc   edx
          mov   dword ptr [eax+esi*1], ecx
          mov   eax, edx
          and   eax, 00000FFFFh
          lea   ecx, dword ptr [eax+001h]
          cmp   ecx, 000000064h
          jl    LAB_00404a22
          and   edx, 00000FFFFh
          pop   esi
          lea   ecx, dword ptr [edx+edx*4]
          mov   edx, dword ptr [actors] ; <c648>
          shl   ecx, 004h
          mov   dword ptr [ecx+edx*1], 000000000h
          ret
LAB_00404a64:
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
_setupActorList endp
~

COMMENT ~
_resetPermObjectCount proc
          mov   word ptr [permObjectCount], 00000h      ; <c702>
          ret
LAB_00404a7a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_resetPermObjectCount endp
~

COMMENT ~
_setupGame proc
          push  000000000h
          push  000000000h
          mov   edx, 000000003h
          xor   ecx, ecx
          call  @addActorOfType@8
          mov   ecx, eax
          xor   edx, edx
          call  @updateActorPositionMaybe@16
          test  eax, eax
          mov   dword ptr [playerActor], eax    ; <c72c>
          mov   dword ptr [playerActorPtrMaybe_1], eax  ; <c64c>
          jnz   LAB_00404aa8
          ret
LAB_00404aa8:     call  _setupGameTitleActors
          call  _setupPermObjects
          mov   dword ptr [isPaused], 000000000h        ; <c650>
          call  _startGameTimer
          mov   eax, 000000001h
          ret
LAB_00404ac7:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_setupGame endp
~

COMMENT ~
_startGameTimer proc
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          test  eax, eax
          jz    LAB_00404b4f
          mov   eax, dword ptr [isGameTimerRunning]     ; <c6d0>
          test  eax, eax
          jnz   LAB_00404b4f
          mov   eax, dword ptr [isPaused]       ; <c650>
          test  eax, eax
          jnz   LAB_00404b4f
          mov   dword ptr [isGameTimerRunning], 000000001h      ; <c6d0>
          call  dword ptr [__imp__GetTickCount@0]       ; <GetTickCount>
          mov   ecx, dword ptr [isSsGameMode]   ; <c95c>
          mov   dword ptr [currentTickCount], eax       ; <c698>
          test  ecx, ecx
          jnz   LAB_00404b14
          mov   ecx, dword ptr [isGsGameMode]   ; <c958>
          test  ecx, ecx
          jz    LAB_00404b2a
LAB_00404b14:     mov   edx, dword ptr [pauseStartTickCount]    ; <c600>
          mov   ecx, dword ptr [timedGameRelated]       ; <c948>
          sub   eax, edx
          add   ecx, eax
          mov   dword ptr [timedGameRelated], ecx       ; <c948>
LAB_00404b2a:     mov   ecx, dword ptr [updateTimerDurationMillis]      ; <c678>
          mov   eax, dword ptr [timerCallbackFuncPtr]   ; <c940>
          mov   edx, dword ptr [hSkiMainWnd]    ; <c6c8>
          and   ecx, 00000FFFFh
          push  eax
          push  ecx
          push  00000029Ah
          push  edx
          call  dword ptr [__imp__SetTimer@16]  ; <SetTimer>
LAB_00404b4f:     ret
_startGameTimer endp
~

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

COMMENT ~
@setPointerToNull@4 proc
          push  esi
          mov   esi, ecx
          test  esi, esi
          jnz   LAB_00405116
          mov   edx, 000000A12h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00405116:     mov   dword ptr [esi], 000000000h
          pop   esi
          ret
LAB_0040511e:
          db 090h
          db 090h
@setPointerToNull@4 endp
~

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

COMMENT ~
_setupGameTitleActors proc
          push  ecx
          mov   eax, dword ptr [sprites]        ; <c5f8>
          push  esi
          mov   esi, 0FFFFFFD8h
          push  edi
          movsx eax, word ptr [eax+00000035Ah]
          cdq
          sub   eax, edx
          push  000000000h
          sar   eax, 1h
          sub   esi, eax
          mov   ax, word ptr [playerY]  ; <c5f2>
          push  eax
          mov   edx, 000000035h
          mov   ecx, 000000011h
          mov   word ptr [esp+010h], ax
          call  @addActorOfTypeWithSpriteIdx@8
          mov   ecx, eax
          mov   edx, esi
          call  @updateActorPositionMaybe@16
          mov   ecx, dword ptr [sprites]        ; <c5f8>
          mov   eax, dword ptr [esp+008h]
          push  000000000h
          mov   dx, word ptr [ecx+00000036Ch]
          mov   ecx, 000000011h
          add   dx, 000000004h
          add   eax, edx
          mov   edx, 000000036h
          push  eax
          call  @addActorOfTypeWithSpriteIdx@8
          mov   ecx, eax
          mov   edx, esi
          call  @updateActorPositionMaybe@16
          mov   eax, dword ptr [sprites]        ; <c5f8>
          mov   cx, word ptr [eax+00000037Ah]
          mov   dx, word ptr [eax+00000038Ah]
          cmp   cx, dx
          mov   edi, ecx
          jg    LAB_0040526f
          mov   edi, edx
LAB_0040526f:     mov   si, word ptr [eax+00000037Ch]
          push  000000000h
          push  esi
          mov   edx, 000000037h
          mov   ecx, 000000011h
          call  @addActorOfTypeWithSpriteIdx@8
          mov   ecx, eax
          mov   edx, edi
          call  @updateActorPositionMaybe@16
          mov   eax, dword ptr [sprites]        ; <c5f8>
          mov   edx, 000000038h
          push  000000000h
          mov   cx, word ptr [eax+00000038Ch]
          add   cx, 000000004h
          add   esi, ecx
          mov   ecx, 000000011h
          push  esi
          call  @addActorOfTypeWithSpriteIdx@8
          mov   ecx, eax
          mov   edx, edi
          call  @updateActorPositionMaybe@16
          pop   edi
          pop   esi
          pop   ecx
          ret
LAB_004052c2:
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
_setupGameTitleActors endp
~

COMMENT ~
@initWindows@12 proc
          sub   esp, 00000002Ch
          push  ebx
          push  ebp
          push  esi
          xor   esi, esi
          push  edi
          mov   dword ptr [esp+010h], edx
          mov   edi, ecx
          push  esi
          call  dword ptr [__imp__GetDC@4]      ; <GetDC>
          mov   ebx, eax
          cmp   ebx, esi
          jnz   LAB_004052f8
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_004052f8:     mov   ebp, dword ptr [__imp__GetDeviceCaps@8] ; <GetDeviceCaps>
          push  000000008h
          push  ebx
          call  ebp
          mov   word ptr [SCREEN_WIDTH], ax     ; <c6a0>
          push  00000000Ah
          push  ebx
          call  ebp
          mov   word ptr [SCREEN_HEIGHT], ax    ; <c74c>
          push  ebx
          push  esi
          call  dword ptr [__imp__ReleaseDC@8]  ; <ReleaseDC>
          mov   dword ptr [skiFreeHInstance], edi       ; <c61c>
          push  esi
          call  dword ptr [__imp__GetStockObject@4]     ; <GetStockObject>
          mov   dword ptr [whiteBrush], eax     ; <c69c>
          mov   dword ptr [hSkiMainWnd], esi    ; <c6c8>
          push  esi
          push  offset s_skiMain        ; <a190>
          mov   dword ptr [hSkiStatusWnd], esi  ; <c624>
          mov   dword ptr [isGameTimerRunning], esi     ; <c6d0>
          mov   dword ptr [isMinimised], 000000001h     ; <c770>
          mov   dword ptr [mainWndActivationFlags], esi ; <c694>
          mov   dword ptr [inputEnabled], esi   ; <c67c>
          mov   word ptr [skierScreenXOffset], si       ; <c704>
          mov   word ptr [skierScreenYOffset], si       ; <c5fc>
          call  dword ptr [__imp__FindWindowA@8]        ; <FindWindowA>
          cmp   eax, esi
          mov   dword ptr [hSkiMainWnd], eax    ; <c6c8>
          jz    LAB_004053b6
          push  000000003h
          push  esi
          push  esi
          push  esi
          push  esi
          push  esi
          push  eax
          call  dword ptr [__imp__SetWindowPos@28]      ; <SetWindowPos>
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  eax
          call  dword ptr [__imp__IsIconic@4]   ; <IsIconic>
          test  eax, eax
          jz    LAB_004053a4
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  ecx
          call  dword ptr [__imp__OpenIcon@4]   ; <OpenIcon>
LAB_004053a4:     mov   dword ptr [hSkiMainWnd], esi    ; <c6c8>
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_004053b6:     mov   edx, offset _timerCallbackFunc  ; <47c0>
          mov   dword ptr [timerCallbackFuncPtr], offset _timerCallbackFunc     ; <c940>
          test  edx, edx
          jnz   LAB_004053d5
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_004053d5:     cmp   dword ptr [isSoundDisabled], esi        ; <c794>
          jnz   LAB_00405475
          call  _loadSoundFunc
          test  eax, eax
          jz    LAB_00405475
          mov   edx, offset sound_1.soundResource       ; <c6c0>
          mov   ecx, 000000001h
          call  @loadSound@8
          mov   edx, offset sound_2.soundResource       ; <c768>
          mov   ecx, 000000002h
          call  @loadSound@8
          mov   edx, offset sound_3.soundResource       ; <c5d0>
          mov   ecx, 000000003h
          call  @loadSound@8
          mov   edx, offset sound_4.soundResource       ; <c718>
          mov   ecx, 000000004h
          call  @loadSound@8
          mov   edx, offset sound_5.soundResource       ; <c750>
          mov   ecx, 000000005h
          call  @loadSound@8
          mov   edx, offset sound_6.soundResource       ; <c628>
          mov   ecx, 000000006h
          call  @loadSound@8
          mov   edx, offset sound_9.soundResource       ; <c6f0>
          mov   ecx, 000000009h
          call  @loadSound@8
          mov   edx, offset sound_7.soundResource       ; <c6e0>
          mov   ecx, 000000007h
          call  @loadSound@8
          mov   edx, offset sound_8.soundResource       ; <c608>
          mov   ecx, 000000008h
          call  @loadSound@8
LAB_00405475:     cmp   dword ptr [esp+010h], esi
          jnz   LAB_00405532
          push  offset s_iconSki_0040c120       ; <c120>
          push  edi
          mov   dword ptr [esp+01Ch], 000002023h
          mov   dword ptr [esp+020h], offset _skiMainWndProc@16 ; <5800>
          mov   dword ptr [esp+024h], esi
          mov   dword ptr [esp+028h], esi
          mov   dword ptr [esp+02Ch], edi
          call  dword ptr [__imp__LoadIconA@8]  ; <LoadIconA>
          mov   ebx, dword ptr [__imp__LoadCursorA@8]   ; <LoadCursorA>
          push  000007F00h
          push  esi
          mov   dword ptr [esp+030h], eax
          call  ebx
          mov   ebp, dword ptr [__imp__RegisterClassA@4]        ; <RegisterClassA>
          lea   ecx, dword ptr [esp+014h]
          mov   dword ptr [esp+02Ch], eax
          mov   eax, dword ptr [whiteBrush]     ; <c69c>
          push  ecx
          mov   dword ptr [esp+034h], eax
          mov   dword ptr [esp+038h], esi
          mov   dword ptr [esp+03Ch], offset s_skiMain  ; <a190>
          call  ebp
          test  ax, ax
          jnz   LAB_004054f0
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_004054f0:     push  000007F00h
          push  esi
          mov   dword ptr [esp+020h], offset _skiStatusWndProc@16       ; <68d0>
          mov   dword ptr [esp+030h], esi
          call  ebx
          mov   edx, dword ptr [whiteBrush]     ; <c69c>
          mov   dword ptr [esp+038h], offset s_skiStatus        ; <a198>
          mov   dword ptr [esp+02Ch], eax
          lea   eax, dword ptr [esp+014h]
          push  eax
          mov   dword ptr [esp+034h], edx
          call  ebp
          test  ax, ax
          jnz   LAB_00405532
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_00405532:     mov   dx, word ptr [SCREEN_WIDTH]     ; <c6a0>
          mov   bx, word ptr [SCREEN_HEIGHT]    ; <c74c>
          mov   eax, dword ptr [SCREEN_WIDTH]   ; <c6a0>
          cmp   dx, bx
          jl    LAB_0040554f
          mov   eax, dword ptr [SCREEN_HEIGHT]  ; <c74c>
LAB_0040554f:     movsx ecx, ax
          push  esi
          push  edi
          movsx eax, bx
          push  esi
          push  esi
          push  eax
          push  ecx
          movsx eax, dx
          sub   eax, ecx
          push  esi
          cdq
          sub   eax, edx
          mov   ecx, 000000001h
          sar   eax, 1h
          push  eax
          push  002CF0000h
          call  @getCachedString@4
          mov   ebx, dword ptr [__imp__CreateWindowExA@48]      ; <CreateWindowExA>
          push  eax
          push  offset s_skiMain        ; <a190>
          push  esi
          call  ebx
          cmp   eax, esi
          mov   dword ptr [hSkiMainWnd], eax    ; <c6c8>
          jnz   LAB_0040559a
          pop   edi
          pop   esi
          pop   ebp
          xor   eax, eax
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_0040559a:     push  esi
          push  edi
          push  esi
          push  eax
          push  esi
          push  esi
          push  esi
          push  esi
          push  040000000h
          push  offset statusWindowNameStrPtr   ; <c788>
          push  offset s_skiStatus      ; <a198>
          push  esi
          call  ebx
          cmp   eax, esi
          mov   dword ptr [hSkiStatusWnd], eax  ; <c624>
          jnz   LAB_004055d6
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  ecx
          call  dword ptr [__imp__DestroyWindow@4]      ; <DestroyWindow>
          xor   eax, eax
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_004055d6:     mov   edx, dword ptr [esp+040h]
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          mov   esi, dword ptr [__imp__ShowWindow@8]    ; <ShowWindow>
          push  edx
          push  eax
          call  esi
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          mov   edi, dword ptr [__imp__UpdateWindow@4]  ; <UpdateWindow>
          push  ecx
          call  edi
          mov   edx, dword ptr [hSkiStatusWnd]  ; <c624>
          push  000000001h
          push  edx
          call  esi
          mov   eax, dword ptr [hSkiStatusWnd]  ; <c624>
          push  eax
          call  edi
          mov   eax, 000000001h
          pop   edi
          pop   esi
          pop   ebp
          pop   ebx
          add   esp, 00000002Ch
          ret   00004h
LAB_0040561a:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@initWindows@12 endp
~

COMMENT ~
_loadSoundFunc proc
          mov   eax, dword ptr [__imp__sndPlaySoundA@8] ; <sndPlaySoundA>
          xor   ecx, ecx
          test  eax, eax
          setnz cl
          mov   dword ptr [sndPlaySoundAFuncPtr], eax   ; <c790>
          mov   eax, ecx
          ret
LAB_00405634:
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
_loadSoundFunc endp
~

COMMENT ~
@loadSound@8 proc
          mov   eax, dword ptr [skiFreeHInstance]       ; <c61c>
          push  esi
          and   ecx, 00000FFFFh
          push  offset s_WAVE   ; <c128>
          push  ecx
          mov   esi, edx
          push  eax
          call  dword ptr [__imp__FindResourceA@12]     ; <FindResourceA>
          test  eax, eax
          mov   dword ptr [esi], eax
          jz    LAB_00405671
          mov   ecx, dword ptr [skiFreeHInstance]       ; <c61c>
          push  eax
          push  ecx
          call  dword ptr [__imp__LoadResource@8]       ; <LoadResource>
          mov   dword ptr [esi], eax
LAB_00405671:     mov   eax, dword ptr [esi]
          test  eax, eax
          jz    LAB_00405688
          push  eax
          call  dword ptr [__imp__LockResource@4]       ; <LockResource>
          mov   dword ptr [esi+004h], eax
          mov   eax, 000000001h
          pop   esi
          ret
LAB_00405688:     mov   dword ptr [esi+004h], 000000000h
          xor   eax, eax
          pop   esi
          ret
LAB_00405693:
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
@loadSound@8 endp
~

COMMENT ~
_cleanupSound proc
          mov   eax, dword ptr [isSoundDisabled]        ; <c794>
          test  eax, eax
          jnz   LAB_00405722
          mov   eax, dword ptr [sndPlaySoundAFuncPtr]   ; <c790>
          test  eax, eax
          jz    LAB_004056b8
          push  000000000h
          push  000000000h
          call  eax
LAB_004056b8:     mov   eax, dword ptr [DAT_0040c78c]   ; <c78c>
          test  eax, eax
          jz    LAB_004056c8
          push  eax
          call  dword ptr [__imp__FreeLibrary@4]        ; <FreeLibrary>
LAB_004056c8:     mov   ecx, offset sound_1.soundResource       ; <c6c0>
          call  @freeSoundResource@4
          mov   ecx, offset sound_2.soundResource       ; <c768>
          call  @freeSoundResource@4
          mov   ecx, offset sound_3.soundResource       ; <c5d0>
          call  @freeSoundResource@4
          mov   ecx, offset sound_4.soundResource       ; <c718>
          call  @freeSoundResource@4
          mov   ecx, offset sound_5.soundResource       ; <c750>
          call  @freeSoundResource@4
          mov   ecx, offset sound_6.soundResource       ; <c628>
          call  @freeSoundResource@4
          mov   ecx, offset sound_9.soundResource       ; <c6f0>
          call  @freeSoundResource@4
          mov   ecx, offset sound_7.soundResource       ; <c6e0>
          call  @freeSoundResource@4
          mov   ecx, offset sound_8.soundResource       ; <c608>
          jmp   @freeSoundResource@4
LAB_00405722:     ret
LAB_00405723:
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
_cleanupSound endp
~

COMMENT ~
@freeSoundResource@4 proc
          push  esi
          mov   esi, ecx
          mov   eax, dword ptr [esi+004h]
          test  eax, eax
          jz    LAB_00405741
          mov   dword ptr [esi+004h], 000000000h
LAB_00405741:     mov   eax, dword ptr [esi]
          test  eax, eax
          jz    LAB_00405754
          push  eax
          call  dword ptr [__imp__FreeResource@4]       ; <FreeResource>
          mov   dword ptr [esi], 000000000h
LAB_00405754:     pop   esi
          ret
LAB_00405756:
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
@freeSoundResource@4 endp
~

COMMENT ~
_togglePausedState proc
          mov   eax, dword ptr [isGameTimerRunning]     ; <c6d0>
          test  eax, eax
          mov   dword ptr [isPaused], eax       ; <c650>
          jz    LAB_0040579c
          call  _pauseGame
          mov   ecx, 000000002h
          call  @getCachedString@4
          push  eax
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  eax
          call  dword ptr [__imp__SetWindowTextA@8]     ; <SetWindowTextA>
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  000000000h
          push  000000000h
          push  ecx
          call  dword ptr [__imp__InvalidateRect@12]    ; <InvalidateRect>
          ret
LAB_0040579c:     mov   ecx, 000000001h
          call  @getCachedString@4
          mov   edx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  eax
          push  edx
          call  dword ptr [__imp__SetWindowTextA@8]     ; <SetWindowTextA>
          jmp   _startGameTimer
LAB_004057b9:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_togglePausedState endp
~

COMMENT ~
_pauseGame proc
          mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          test  eax, eax
          jz    LAB_004057f3
          mov   ecx, dword ptr [isGameTimerRunning]     ; <c6d0>
          test  ecx, ecx
          jz    LAB_004057f3
          push  00000029Ah
          push  eax
          mov   dword ptr [isGameTimerRunning], 000000000h      ; <c6d0>
          call  dword ptr [__imp__KillTimer@8]  ; <KillTimer>
          mov   eax, dword ptr [currentTickCount]       ; <c698>
          mov   dword ptr [pauseStartTickCount], eax    ; <c600>
LAB_004057f3:     ret
LAB_004057f4:
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
_pauseGame endp
~

COMMENT ~
_skiMainWndProc@16 proc
          mov   eax, dword ptr [esp+008h]
          push  esi
          cmp   eax, 000000024h
          ja    LAB_00405915
          jz    LAB_004058fd
          lea   ecx, dword ptr [eax-001h]
          cmp   ecx, 000000020h
          ja    LAB_00405995
          xor   edx, edx
          mov   dl, byte ptr [ecx+LAB_004059e0] ; <59e0>
          jmp   dword ptr [edx*4+LAB_004059c4]  ; <59c4>
LAB_0040582f:     mov   esi, dword ptr [esp+008h]
          mov   ecx, esi
          call  @loadBitmaps@4
          test  eax, eax
          jnz   LAB_00405845
          or    eax, 0FFFFFFFFh
          pop   esi
          ret   00010h
LAB_00405845:     mov   ecx, esi
          call  @updateWindowSize@4
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00405852:     mov   ecx, dword ptr [esp+008h]
          call  @handleWindowMoveMessage@4
          push  000000000h
          call  dword ptr [__imp__PostQuitMessage@4]    ; <PostQuitMessage>
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00405869:     mov   ecx, dword ptr [esp+008h]
          call  @mainWindowPaint@4
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00405878:     mov   ecx, dword ptr [esp+008h]
          call  @updateWindowSize@4
          mov   eax, dword ptr [hSkiStatusWnd]  ; <c624>
          test  eax, eax
          jz    LAB_0040588f
          call  _handleWindowSizeMessage
LAB_0040588f:     mov   ecx, dword ptr [esp+010h]
          xor   eax, eax
          cmp   ecx, 000000001h
          setz  al
          mov   dword ptr [isMinimised], eax    ; <c770>
          call  _updateWindowsActiveStatus
          mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004059bd
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  ecx
          call  dword ptr [__imp__UpdateWindow@4]       ; <UpdateWindow>
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_004058c5:     mov   eax, dword ptr [esp+010h]
          test  eax, eax
          mov   dword ptr [mainWndActivationFlags], eax ; <c694>
          jz    LAB_004058dd
          mov   edx, dword ptr [esp+008h]
          push  edx
          call  dword ptr [__imp__SetFocus@4]   ; <SetFocus>
LAB_004058dd:     call  _updateWindowsActiveStatus
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_004058e8:     cmp   word ptr [esp+014h], 000000001h
          jnz   LAB_004059bd
          mov   eax, 000000002h
          pop   esi
          ret   00010h
LAB_004058fd:     mov   eax, dword ptr [esp+014h]
          pop   esi
          mov   dword ptr [eax+018h], 000000140h
          mov   dword ptr [eax+01Ch], 00000012Ch
          xor   eax, eax
          ret   00010h
LAB_00405915:     cmp   eax, 000000200h
          ja    LAB_00405986
          jz    LAB_00405969
          mov   ecx, eax
          sub   ecx, 000000100h
          jz    LAB_0040594d
          sub   ecx, 000000002h
          jnz   LAB_00405995
          mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004059bd
          mov   edx, dword ptr [esp+014h]
          mov   ecx, dword ptr [esp+010h]
          call  @handleCharMessage@4
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_0040594d:     mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004059bd
          mov   edx, dword ptr [esp+014h]
          mov   ecx, dword ptr [esp+010h]
          call  @handleKeydownMessage@4
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00405969:     mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004059bd
          mov   ecx, dword ptr [esp+014h]
          mov   edx, ecx
          shr   edx, 010h
          call  @handleMouseMoveMessage@8
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00405986:     mov   ecx, eax
          sub   ecx, 000000201h
          jz    LAB_004059af
          sub   ecx, 000000002h
          jz    LAB_004059af
LAB_00405995:     mov   ecx, dword ptr [esp+014h]
          mov   edx, dword ptr [esp+010h]
          push  ecx
          push  edx
          push  eax
          mov   eax, dword ptr [esp+014h]
          push  eax
          call  dword ptr [__imp__DefWindowProcA@16]    ; <DefWindowProcA>
          pop   esi
          ret   00010h
LAB_004059af:     mov   eax, dword ptr [inputEnabled]   ; <c67c>
          test  eax, eax
          jz    LAB_004059bd
          call  _handleMouseClick
LAB_004059bd:     xor   eax, eax
          pop   esi
          ret   00010h
LAB_004059c3:
          db 090h
LAB_004059c4:
DAT_004059c4  dword offset LAB_0040582f
DAT_004059c8  dword offset LAB_00405852
DAT_004059cc  dword offset LAB_00405878
DAT_004059d0  dword offset LAB_004058c5
DAT_004059d4  dword offset LAB_00405869
DAT_004059d8  dword offset LAB_004058e8
DAT_004059dc  dword offset LAB_00405995
LAB_004059e0:
          db 000h
          db 001h
          db 006h
          db 006h
          db 002h
          db 003h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 004h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 006h
          db 005h
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
_skiMainWndProc@16 endp
~

COMMENT ~
_updateWindowsActiveStatus proc
          mov   eax, dword ptr [mainWndActivationFlags] ; <c694>
          test  eax, eax
          jz    LAB_00405a31
          mov   eax, dword ptr [isMinimised]    ; <c770>
          test  eax, eax
          jnz   LAB_00405a31
          mov   dword ptr [inputEnabled], 000000001h    ; <c67c>
          jmp   _startGameTimer
LAB_00405a31:     mov   dword ptr [inputEnabled], 000000000h    ; <c67c>
          jmp   _pauseGame
_updateWindowsActiveStatus endp
~

COMMENT ~
@loadBitmaps@4 proc
          push  ecx
          call  dword ptr [__imp__GetDC@4]      ; <GetDC>
          xor   edx, edx
          mov   dword ptr [mainWindowDC], eax   ; <c63c>
          cmp   eax, edx
          jnz   LAB_00405a55
          xor   eax, eax
          ret
LAB_00405a55:     mov   ecx, eax
          mov   dword ptr [smallBitmapDC], edx  ; <c710>
          mov   dword ptr [smallBitmapDC_1bpp], edx     ; <c6a4>
          mov   dword ptr [largeBitmapDC], edx  ; <c730>
          mov   dword ptr [largeBitmapDC_1bpp], edx     ; <c6ec>
          mov   dword ptr [bitmapSourceDC], edx ; <c5ec>
          mov   dword ptr [smallBitmapSheet], edx       ; <c620>
          mov   dword ptr [smallBitmapSheet_1bpp], edx  ; <c6d4>
          mov   dword ptr [largeBitmapSheet], edx       ; <c644>
          mov   dword ptr [largeBitmapSheet_1bpp], edx  ; <c75c>
          mov   dword ptr [scratchBitmap], edx  ; <c614>
          call  @createBitmapSheets@4
          test  eax, eax
          jnz   LAB_00405aa9
          mov   ecx, offset s_bitmap_load_error_message ; <c130>
          call  @showErrorMessage@4
          xor   eax, eax
          ret
LAB_00405aa9:     mov   eax, 000000001h
          ret
LAB_00405aaf:
          db 090h
@loadBitmaps@4 endp
~

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

COMMENT ~
@loadBitmapResource@4 proc
          mov   eax, dword ptr [skiFreeHInstance]       ; <c61c>
          and   ecx, 00000FFFFh
          push  ecx
          push  eax
          call  dword ptr [__imp__LoadBitmapA@8]        ; <LoadBitmapA>
          ret
LAB_00405eb4:
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
@loadBitmapResource@4 endp
~

COMMENT ~
@handleWindowMoveMessage@4 proc
          mov   eax, dword ptr [mainWindowDC]   ; <c63c>
          push  eax
          push  ecx
          call  dword ptr [__imp__ReleaseDC@8]  ; <ReleaseDC>
          call  _pauseGame
          jmp   _deleteWindowObjects
LAB_00405ed7:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@handleWindowMoveMessage@4 endp
~

_deleteWindowObjects proc
          mov   eax, dword ptr [smallBitmapSheet]       ; <c620>
          push  esi
          mov   esi, dword ptr [__imp__DeleteObject@4]  ; <DeleteObject>
          push  edi
          mov   edi, dword ptr [__imp__SelectObject@8]  ; <SelectObject>
          test  eax, eax
          jz    LAB_00405f03
          push  eax
          mov   eax, dword ptr [smallBitmapDC]  ; <c710>
          push  eax
          call  edi
          push  eax
          call  esi
LAB_00405f03:     mov   eax, dword ptr [largeBitmapSheet]       ; <c644>
          test  eax, eax
          jz    LAB_00405f19
          mov   ecx, dword ptr [largeBitmapDC]  ; <c730>
          push  eax
          push  ecx
          call  edi
          push  eax
          call  esi
LAB_00405f19:     mov   eax, dword ptr [smallBitmapSheet_1bpp]  ; <c6d4>
          test  eax, eax
          jz    LAB_00405f2f
          mov   edx, dword ptr [smallBitmapDC_1bpp]     ; <c6a4>
          push  eax
          push  edx
          call  edi
          push  eax
          call  esi
LAB_00405f2f:     mov   eax, dword ptr [largeBitmapSheet_1bpp]  ; <c75c>
          test  eax, eax
          jz    LAB_00405f44
          push  eax
          mov   eax, dword ptr [largeBitmapDC_1bpp]     ; <c6ec>
          push  eax
          call  edi
          push  eax
          call  esi
LAB_00405f44:     mov   eax, dword ptr [scratchBitmap]  ; <c614>
          test  eax, eax
          jz    LAB_00405f5a
          mov   ecx, dword ptr [bitmapSourceDC] ; <c5ec>
          push  eax
          push  ecx
          call  edi
          push  eax
          call  esi
LAB_00405f5a:     mov   eax, dword ptr [smallBitmapDC]  ; <c710>
          mov   esi, dword ptr [__imp__DeleteDC@4]      ; <DeleteDC>
          test  eax, eax
          jz    LAB_00405f6c
          push  eax
          call  esi
LAB_00405f6c:     mov   eax, dword ptr [largeBitmapDC]  ; <c730>
          test  eax, eax
          jz    LAB_00405f78
          push  eax
          call  esi
LAB_00405f78:     mov   eax, dword ptr [smallBitmapDC_1bpp]     ; <c6a4>
          test  eax, eax
          jz    LAB_00405f84
          push  eax
          call  esi
LAB_00405f84:     mov   eax, dword ptr [largeBitmapDC_1bpp]     ; <c6ec>
          test  eax, eax
          jz    LAB_00405f90
          push  eax
          call  esi
LAB_00405f90:     mov   eax, dword ptr [bitmapSourceDC] ; <c5ec>
          test  eax, eax
          jz    LAB_00405f9c
          push  eax
          call  esi
LAB_00405f9c:     pop   edi
          pop   esi
          ret
LAB_00405f9f:
          db 090h
_deleteWindowObjects endp

@updateWindowSize@4 proc
          push  ebx
          push  ebp
          push  esi
          push  edi
          push  offset windowClientRect.left    ; <c6b0>
          push  ecx
          mov   dword ptr [DAT_0040c760], 000000000h    ; <c760>
          call  dword ptr [__imp__GetClientRect@8]      ; <GetClientRect>
          mov   eax, dword ptr [windowClientRect.top]   ; <c6b4>
          mov   ecx, dword ptr [windowClientRect.bottom]        ; <c6bc>
          add   ecx, eax
          mov   eax, 055555556h
          imul  ecx
          mov   eax, dword ptr [windowClientRect.left]  ; <c6b0>
          mov   ecx, dword ptr [windowClientRect.right] ; <c6b8>
          mov   esi, edx
          add   eax, ecx
          shr   edx, 01Fh
          add   esi, edx
          cdq
          sub   eax, edx
          mov   edx, esi
          mov   ecx, eax
          sar   ecx, 1h
          call  @updateActorsAfterWindowResize@8
          mov   ebp, dword ptr [windowClientRect.top]   ; <c6b4>
          mov   esi, dword ptr [windowClientRect.bottom]        ; <c6bc>
          mov   ecx, dword ptr [windowClientRect.right] ; <c6b8>
          mov   edi, dword ptr [windowClientRect.left]  ; <c6b0>
          lea   eax, dword ptr [ebp-078h]
          mov   dword ptr [windowClientRectWith120Margin.top], eax      ; <c684>
          lea   eax, dword ptr [esi+078h]
          sub   esi, ebp
          lea   edx, dword ptr [ecx+078h]
          mov   word ptr [windowHeight], si     ; <c6d8>
          mov   esi, dword ptr [windowClientRectWith120Margin.top]      ; <c684>
          lea   ebx, dword ptr [edi-078h]
          mov   dword ptr [windowClientRectWith120Margin.right], edx    ; <c688>
          mov   dword ptr [windowClientRectWith120Margin.bottom], eax   ; <c68c>
          sub   eax, esi
          sub   edx, ebx
          sub   ecx, edi
          imul  eax, edx
          pop   edi
          pop   esi
          mov   dword ptr [windowClientRectWith120Margin.left], ebx     ; <c680>
          pop   ebp
          mov   word ptr [windowWidth], cx      ; <c5f0>
          mov   dword ptr [windowWithMarginTotalArea], eax      ; <c748>
          pop   ebx
          ret
LAB_00406053:
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
@updateWindowSize@4 endp

@updateActorsAfterWindowResize@8 proc
          push  ebx
          push  esi
          mov   esi, dword ptr [actorListPtr]   ; <c618>
          push  edi
          test  esi, esi
          mov   di, dx
          mov   bx, cx
          jz    LAB_00406097
LAB_00406073:     mov   eax, dword ptr [esi+04Ch]
          test  al, 004h
          jz    LAB_00406091
          test  al, 002h
          jnz   LAB_00406091
          test  al, 001h
          jz    LAB_0040608b
          mov   ecx, esi
          call  @duplicateAndLinkActor@4
          jmp   LAB_0040608d
LAB_0040608b:     mov   eax, esi
LAB_0040608d:     and   dword ptr [eax+04Ch], 0FFFFFFFBh
LAB_00406091:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00406073
LAB_00406097:     mov   word ptr [skierScreenYOffset], di       ; <c5fc>
          pop   edi
          mov   word ptr [skierScreenXOffset], bx       ; <c704>
          pop   esi
          pop   ebx
          ret
LAB_004060a9:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@updateActorsAfterWindowResize@8 endp

COMMENT ~
@mainWindowPaint@4 proc
          sub   esp, 000000040h
          lea   eax, dword ptr [esp+000h]
          push  esi
          mov   esi, ecx
          push  eax
          push  esi
          call  dword ptr [__imp__BeginPaint@8] ; <BeginPaint>
          mov   ecx, dword ptr [whiteBrush]     ; <c69c>
          lea   edx, dword ptr [esp+00Ch]
          mov   eax, dword ptr [esp+004h]
          push  ecx
          push  edx
          push  eax
          call  dword ptr [__imp__FillRect@12]  ; <FillRect>
          lea   edx, dword ptr [esp+00Ch]
          mov   ecx, dword ptr [esp+004h]
          call  @paintActors@8
          lea   ecx, dword ptr [esp+004h]
          push  ecx
          push  esi
          call  dword ptr [__imp__EndPaint@8]   ; <EndPaint>
          pop   esi
          add   esp, 000000040h
          ret
LAB_004060f7:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@mainWindowPaint@4 endp
~

COMMENT ~
@paintActors@8 proc
          push  ebp
          mov   ebp, ecx
          push  esi
          push  edi
          test  ebp, ebp
          mov   edi, edx
          jnz   LAB_0040611a
          mov   edx, 000000543h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040611a:     test  edi, edi
          jnz   LAB_0040612d
          mov   edx, 000000544h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_0040612d:     mov   esi, dword ptr [actorListPtr]   ; <c618>
          test  esi, esi
          jz    LAB_00406164
LAB_00406137:     test  byte ptr [esi+04Ch], 004h
          jz    LAB_00406142
          lea   eax, dword ptr [esi+020h]
          jmp   LAB_00406149
LAB_00406142:     mov   ecx, esi
          call  @updateActorSpriteRect@4
LAB_00406149:     mov   edx, edi
          mov   ecx, eax
          call  @doRectsOverlap@8
          test  eax, eax
          jz    LAB_0040615e
          mov   eax, dword ptr [esi+04Ch]
          and   al, 0FEh
          mov   dword ptr [esi+04Ch], eax
LAB_0040615e:     mov   esi, dword ptr [esi]
          test  esi, esi
          jnz   LAB_00406137
LAB_00406164:     mov   edx, edi
          pop   edi
          mov   ecx, ebp
          pop   esi
          pop   ebp
          jmp   @drawWindow@8
@paintActors@8 endp
~

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
LAB_0040620c:     mov   esi, dword ptr [esi*8+DAT_0040a258]     ; <a258>
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
LAB_0040624f:     mov   esi, dword ptr [esi*8+DAT_0040a25c]     ; <a25c>
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

COMMENT ~
_handleGameReset proc
          call  _resetGame
          test  eax, eax
          jz    LAB_0040653e
          mov   eax, dword ptr [isPaused]       ; <c650>
          test  eax, eax
          jz    LAB_00406517
          call  _togglePausedState
LAB_00406517:     mov   eax, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  000000001h
          push  000000000h
          push  eax
          call  dword ptr [__imp__InvalidateRect@12]    ; <InvalidateRect>
          call  _setupGame
          test  eax, eax
          jz    LAB_0040653e
          mov   ecx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  ecx
          call  dword ptr [__imp__UpdateWindow@4]       ; <UpdateWindow>
          ret
LAB_0040653e:     mov   edx, dword ptr [hSkiMainWnd]    ; <c6c8>
          push  edx
          call  dword ptr [__imp__DestroyWindow@4]      ; <DestroyWindow>
          ret
LAB_0040654c:
          db 090h
          db 090h
          db 090h
          db 090h
_handleGameReset endp
~

@handleMouseMoveMessage@8 proc
          mov   eax, dword ptr [DAT_0040c760]   ; <c760>
          push  esi
          push  edi
          mov   esi, edx
          test  eax, eax
          mov   edi, ecx
          jz    LAB_004065bd
          cmp   di, word ptr [prevMouseX]       ; <c700>
          jnz   LAB_00406571
          cmp   si, word ptr [prevMouseY]       ; <c70c>
          jz    LAB_004065bd
LAB_00406571:     mov   eax, dword ptr [playerActor]    ; <c72c>
          test  eax, eax
          jz    LAB_004065bd
          mov   ecx, dword ptr [eax+01Ch]
          cmp   ecx, 00000000Bh
          jz    LAB_004065bd
          cmp   ecx, 000000011h
          jz    LAB_004065bd
          mov   edx, dword ptr [skierScreenXOffset]     ; <c704>
          mov   ecx, edi
          push  ebx
          mov   ebx, dword ptr [skierScreenYOffset]     ; <c5fc>
          sub   ecx, edx
          mov   edx, esi
          sub   edx, ebx
          cmp   word ptr [eax+044h], 000000000h
          pop   ebx
          jnz   LAB_004065ab
          call  @getSkierGroundSpriteFromMousePosition@8
          jmp   LAB_004065b0
LAB_004065ab:     call  @getSkierInAirSpriteFromMousePosition@8
LAB_004065b0:     mov   ecx, dword ptr [playerActor]    ; <c72c>
          mov   edx, eax
          call  @setActorFrameNo@8
LAB_004065bd:     mov   word ptr [prevMouseX], di       ; <c700>
          mov   word ptr [prevMouseY], si       ; <c70c>
          pop   edi
          mov   dword ptr [DAT_0040c760], 000000001h    ; <c760>
          pop   esi
          ret
LAB_004065d8:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
@handleMouseMoveMessage@8 endp

@getSkierGroundSpriteFromMousePosition@8 proc
          test  dx, dx
          jle   LAB_00406655
          test  cx, cx
          jnz   LAB_004065ed
          xor   eax, eax
          ret
LAB_004065ed:     movsx eax, dx
          push  esi
          shl   eax, 002h
          movsx esi, cx
          cdq
          idiv  esi
          pop   esi
          cmp   ax, 0FFF4h
          jg    LAB_00406604
          xor   eax, eax
          ret
LAB_00406604:     cmp   ax, 0FFFAh
          jg    LAB_00406610
          mov   eax, 000000001h
          ret
LAB_00406610:     cmp   ax, 0FFFDh
          jg    LAB_0040661c
          mov   eax, 000000002h
          ret
LAB_0040661c:     cmp   ax, 0FFFFh
          jg    LAB_00406628
          mov   eax, 000000003h
          ret
LAB_00406628:     cmp   ax, 0000Ch
          jl    LAB_00406631
          xor   eax, eax
          ret
LAB_00406631:     cmp   ax, 00006h
          jl    LAB_0040663d
          mov   eax, 000000004h
          ret
LAB_0040663d:     cmp   ax, 00003h
          jl    LAB_00406649
          mov   eax, 000000005h
          ret
LAB_00406649:     cmp   ax, 00001h
          jl    LAB_00406655
          mov   eax, 000000006h
          ret
LAB_00406655:     xor   eax, eax
          test  cx, cx
          setge al
          dec   eax
          and   al, 0FDh
          add   eax, 000000006h
          ret
LAB_00406664:
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
@getSkierGroundSpriteFromMousePosition@8 endp

@getSkierInAirSpriteFromMousePosition@8 proc
          test  cx, cx
          jge   LAB_0040669f
          test  dx, dx
          jge   LAB_0040668a
          xor   eax, eax
          cmp   dx, cx
          setge al
          dec   eax
          and   eax, 000000002h
          add   eax, 00000000Eh
          ret
LAB_0040668a:     movsx eax, dx
          movsx ecx, cx
          neg   eax
          xor   edx, edx
          cmp   eax, ecx
          setge dl
          add   edx, 00000000Dh
          mov   eax, edx
          ret
LAB_0040669f:     test  dx, dx
          jge   LAB_004066b9
          movsx eax, dx
          movsx ecx, cx
          neg   eax
          xor   edx, edx
          cmp   eax, ecx
          setg  dl
          add   edx, 00000000Fh
          mov   eax, edx
          ret
LAB_004066b9:     xor   eax, eax
          cmp   dx, cx
          setle al
          add   eax, 00000000Dh
          ret
LAB_004066c5:
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
@getSkierInAirSpriteFromMousePosition@8 endp

_handleMouseClick proc
          mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jnz   LAB_004066df
          jmp   _handleGameReset
LAB_004066df:     mov   edx, dword ptr [ecx+01Ch]
          cmp   edx, 00000000Bh
          jz    LAB_00406736
          cmp   word ptr [ecx+044h], 000000000h
          jnz   LAB_00406701
          mov   word ptr [ecx+04Ah], 00004h
          mov   ecx, dword ptr [playerActor]    ; <c72c>
          mov   edx, 00000000Dh
          jmp   LAB_00406736
LAB_00406701:     cmp   edx, 000000011h
          jz    LAB_00406736
          lea   eax, dword ptr [edx-00Dh]
          cmp   eax, 000000006h
          ja    LAB_00406736
          jmp   dword ptr [eax*4+LAB_00406764]  ; <6764>
LAB_00406715:     mov   edx, 000000012h
          jmp   LAB_00406736
LAB_0040671c:     mov   edx, 000000013h
          jmp   LAB_00406736
LAB_00406723:     mov   edx, 00000000Dh
          jmp   LAB_00406736
LAB_0040672a:     mov   edx, 000000014h
          jmp   LAB_00406736
LAB_00406731:     mov   edx, 000000015h
LAB_00406736:     cmp   edx, dword ptr [ecx+01Ch]
          jz    LAB_00406763
          call  @setActorFrameNo@8
          mov   eax, dword ptr [redrawRequired] ; <c610>
          test  eax, eax
          jz    LAB_00406763
          mov   ecx, dword ptr [mainWindowDC]   ; <c63c>
          mov   edx, offset windowClientRect.left       ; <c6b0>
          call  @drawWindow@8
          mov   dword ptr [redrawRequired], 000000000h  ; <c610>
LAB_00406763:     ret
LAB_00406764:
DAT_00406764  dword offset LAB_00406715
DAT_00406768  dword offset LAB_0040672a
DAT_0040676c  dword offset LAB_00406731
DAT_00406770  dword offset LAB_00406736
DAT_00406774  dword offset LAB_00406736
DAT_00406778  dword offset LAB_0040671c
DAT_0040677c  dword offset LAB_00406723
_handleMouseClick endp

COMMENT ~
@handleCharMessage@4 proc
          lea   eax, dword ptr [ecx-058h]
          cmp   eax, 000000021h
          ja    LAB_0040684a
          xor   ecx, ecx
          mov   cl, byte ptr [eax+LAB_0040686c] ; <686c>
          jmp   dword ptr [ecx*4+LAB_0040684c]  ; <684c>
LAB_0040679b:     jmp   _timerUpdateFunc
LAB_004067a0:     mov   eax, dword ptr [isTurboMode]    ; <c670>
          xor   edx, edx
          test  eax, eax
          setz  dl
          mov   dword ptr [isTurboMode], edx    ; <c670>
          ret
LAB_004067b3:     mov   ecx, dword ptr [mainWindowDC]   ; <c63c>
          mov   edx, offset windowClientRect.left       ; <c6b0>
          jmp   @drawWindow@8
LAB_004067c3:     mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_0040684a
          mov   ax, word ptr [ecx+044h]
          mov   dx, word ptr [ecx+042h]
          push  eax
          push  edx
          mov   dx, word ptr [ecx+040h]
          add   dx, 000000002h
          call  @updateActorPositionMaybe@16
          ret
LAB_004067e5:     mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_0040684a
          mov   ax, word ptr [ecx+044h]
          mov   dx, word ptr [ecx+042h]
          push  eax
          push  edx
          mov   dx, word ptr [ecx+040h]
          sub   dx, 000000002h
          call  @updateActorPositionMaybe@16
          ret
LAB_00406807:     mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_0040684a
          mov   dx, word ptr [ecx+042h]
          mov   ax, word ptr [ecx+044h]
          add   dx, 000000002h
          push  eax
          push  edx
          mov   dx, word ptr [ecx+040h]
          call  @updateActorPositionMaybe@16
          ret
LAB_00406829:     mov   ecx, dword ptr [playerActor]    ; <c72c>
          test  ecx, ecx
          jz    LAB_0040684a
          mov   dx, word ptr [ecx+042h]
          mov   ax, word ptr [ecx+044h]
          sub   dx, 000000002h
          push  eax
          push  edx
          mov   dx, word ptr [ecx+040h]
          call  @updateActorPositionMaybe@16
LAB_0040684a:     ret
LAB_0040684b:
          db 090h
LAB_0040684c:
DAT_0040684c  dword offset LAB_004067e5
DAT_00406850  dword offset LAB_00406829
DAT_00406854  dword offset LAB_004067a0
DAT_00406858  dword offset LAB_004067b3
DAT_0040685c  dword offset LAB_0040679b
DAT_00406860  dword offset LAB_004067c3
DAT_00406864  dword offset LAB_00406807
DAT_00406868  dword offset LAB_0040684a
LAB_0040686c:
          db 000h
          db 001h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 002h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 007h
          db 003h
          db 007h
          db 004h
          db 007h
          db 007h
          db 007h
          db 005h
          db 006h
          db 090h
          db 090h
@handleCharMessage@4 endp
~

COMMENT ~
_handleWindowSizeMessage proc
          mov   cx, word ptr [statusWindowHeight]       ; <c66a>
          mov   eax, dword ptr [statusWindowTotalTextWidth]     ; <c66c>
          add   cx, 000000004h
          add   eax, 000000004h
          movsx edx, cx
          mov   ecx, dword ptr [windowClientRect.top]   ; <c6b4>
          push  000000001h
          movsx eax, ax
          push  edx
          mov   edx, dword ptr [windowClientRect.right] ; <c6b8>
          push  eax
          sub   edx, eax
          mov   eax, dword ptr [hSkiStatusWnd]  ; <c624>
          push  ecx
          push  edx
          push  eax
          call  dword ptr [__imp__MoveWindow@24]        ; <MoveWindow>
          ret
LAB_004068ca:
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_handleWindowSizeMessage endp
~

COMMENT ~
_skiStatusWndProc@16 proc
          push  esi
          mov   esi, dword ptr [esp+00Ch]
          push  edi
          mov   edi, dword ptr [esp+00Ch]
          lea   eax, dword ptr [esi-001h]
          cmp   eax, 00000000Eh
          ja    LAB_00406930
          xor   ecx, ecx
          mov   cl, byte ptr [eax+LAB_0040695c] ; <695c>
          jmp   dword ptr [ecx*4+LAB_00406948]  ; <6948>
LAB_004068f1:     mov   ecx, dword ptr [esp+00Ch]
          call  @paintStatusWindow@4
          pop   edi
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00406901:     mov   ecx, dword ptr [esp+00Ch]
          call  @statusWindowReleaseDC@4
          pop   edi
          xor   eax, eax
          pop   esi
          ret   00010h
LAB_00406911:     mov   ecx, edi
          call  @calculateStatusWindowDimensions@4
          test  eax, eax
          jnz   LAB_00406924
          pop   edi
          or    eax, 0FFFFFFFFh
          pop   esi
          ret   00010h
LAB_00406924:     push  offset statusBorderRect ; <c778>
          push  edi
          call  dword ptr [__imp__GetClientRect@8]      ; <GetClientRect>
LAB_00406930:     mov   edx, dword ptr [esp+018h]
          mov   eax, dword ptr [esp+014h]
          push  edx
          push  eax
          push  esi
          push  edi
          call  dword ptr [__imp__DefWindowProcA@16]    ; <DefWindowProcA>
          pop   edi
          pop   esi
          ret   00010h
LAB_00406947:
          db 090h
LAB_00406948:
DAT_00406948  dword offset LAB_00406911
DAT_0040694c  dword offset LAB_00406901
DAT_00406950  dword offset LAB_00406924
DAT_00406954  dword offset LAB_004068f1
DAT_00406958  dword offset LAB_00406930
LAB_0040695c:
          db 000h
          db 001h
          db 004h
          db 004h
          db 002h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 004h
          db 003h
          db 090h
          db 090h
          db 090h
          db 090h
          db 090h
_skiStatusWndProc@16 endp
~

COMMENT ~
@paintStatusWindow@4 proc
          sub   esp, 000000044h
          push  esi
          push  edi
          lea   eax, dword ptr [esp+00Ch]
          mov   edi, ecx
          push  eax
          push  edi
          mov   dword ptr [esp+010h], 000000002h
          call  dword ptr [__imp__BeginPaint@8] ; <BeginPaint>
          push  000000004h
          call  dword ptr [__imp__GetStockObject@4]     ; <GetStockObject>
          mov   ecx, dword ptr [esp+00Ch]
          push  eax
          push  offset statusBorderRect ; <c778>
          push  ecx
          call  dword ptr [__imp__FrameRect@12] ; <FrameRect>
          mov   ecx, 000000003h
          call  @getCachedString@4
          mov   esi, dword ptr [__imp__lstrlenA@4]      ; <lstrlenA>
          push  eax
          call  esi
          lea   edx, dword ptr [esp+008h]
          mov   ecx, 000000003h
          push  eax
          push  edx
          push  000000002h
          call  @getCachedString@4
          mov   ecx, dword ptr [esp+018h]
          mov   edx, eax
          call  @drawText@20
          mov   ecx, 000000004h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000004h
          push  eax
          lea   eax, dword ptr [esp+00Ch]
          push  eax
          push  000000002h
          call  @getCachedString@4
          mov   ecx, dword ptr [esp+018h]
          mov   edx, eax
          call  @drawText@20
          mov   ecx, 000000005h
          call  @getCachedString@4
          push  eax
          call  esi
          lea   ecx, dword ptr [esp+008h]
          push  eax
          push  ecx
          push  000000002h
          mov   ecx, 000000005h
          call  @getCachedString@4
          mov   ecx, dword ptr [esp+018h]
          mov   edx, eax
          call  @drawText@20
          mov   ecx, 000000006h
          call  @getCachedString@4
          push  eax
          call  esi
          lea   edx, dword ptr [esp+008h]
          mov   ecx, 000000006h
          push  eax
          push  edx
          push  000000002h
          call  @getCachedString@4
          mov   ecx, dword ptr [esp+018h]
          mov   edx, eax
          call  @drawText@20
          mov   ecx, dword ptr [esp+00Ch]
          call  @formatAndPrintStatusStrings@4
          lea   eax, dword ptr [esp+00Ch]
          push  eax
          push  edi
          call  dword ptr [__imp__EndPaint@8]   ; <EndPaint>
          pop   edi
          pop   esi
          add   esp, 000000044h
          ret
LAB_00406a6d:
          db 090h
          db 090h
          db 090h
@paintStatusWindow@4 endp
~

COMMENT ~
@calculateStatusWindowDimensions@4 proc
          sub   esp, 000000040h
          push  esi
          xor   esi, esi
          push  ecx
          mov   dword ptr [esp+008h], esi
          mov   dword ptr [esp+00Ch], esi
          call  dword ptr [__imp__GetDC@4]      ; <GetDC>
          cmp   eax, esi
          mov   dword ptr [statusWindowDC], eax ; <c6cc>
          jnz   LAB_00406a95
          xor   eax, eax
          pop   esi
          add   esp, 000000040h
          ret
LAB_00406a95:     push  00000000Ah
          call  dword ptr [__imp__GetStockObject@4]     ; <GetStockObject>
          cmp   eax, esi
          mov   dword ptr [statusWindowFont], eax       ; <c664>
          jz    LAB_00406ab8
          push  eax
          mov   eax, dword ptr [statusWindowDC] ; <c6cc>
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
          mov   dword ptr [statusWindowFont], eax       ; <c664>
LAB_00406ab8:     mov   edx, dword ptr [statusWindowDC] ; <c6cc>
          lea   ecx, dword ptr [esp+00Ch]
          push  ecx
          push  edx
          call  dword ptr [__imp__GetTextMetricsA@8]    ; <GetTextMetricsA>
          mov   ecx, 000000003h
          mov   ax, word ptr [esp+00Ch]
          mov   word ptr [textLineHeight], ax   ; <c668>
          call  @getCachedString@4
          mov   esi, dword ptr [__imp__lstrlenA@4]      ; <lstrlenA>
          push  eax
          call  esi
          mov   ecx, 000000003h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+008h]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000004h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000004h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+008h]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000005h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000005h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+008h]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000006h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000006h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+008h]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000007h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000007h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+00Ch]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000008h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000008h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+00Ch]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 000000009h
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 000000009h
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          push  eax
          lea   edx, dword ptr [esp+010h]
          call  @statusWindowFindLongestTextString@16
          mov   ecx, 00000000Ah
          call  @getCachedString@4
          push  eax
          call  esi
          mov   ecx, 00000000Ah
          push  eax
          call  @getCachedString@4
          mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          lea   edx, dword ptr [esp+00Ch]
          push  eax
          call  @statusWindowFindLongestTextString@16
          mov   ecx, dword ptr [textLineHeight] ; <c668>
          mov   eax, dword ptr [esp+004h]
          pop   esi
          lea   edx, dword ptr [ecx*4+000000000h]
          mov   ecx, dword ptr [esp+004h]
          add   ecx, eax
          mov   word ptr [statusWindowLabelWidth], ax   ; <c66e>
          mov   word ptr [statusWindowHeight], dx       ; <c66a>
          mov   word ptr [statusWindowTotalTextWidth], cx       ; <c66c>
          mov   eax, 000000001h
          add   esp, 000000040h
          ret
@calculateStatusWindowDimensions@4 endp
~

COMMENT ~
@statusWindowFindLongestTextString@16 proc
          sub   esp, 000000008h
          lea   eax, dword ptr [esp+000h]
          push  esi
          mov   esi, edx
          mov   edx, dword ptr [esp+014h]
          push  eax
          mov   eax, dword ptr [esp+014h]
          push  edx
          push  eax
          push  ecx
          call  dword ptr [__imp__GetTextExtentPoint32A@16]     ; <GetTextExtentPoint32A>
          mov   eax, dword ptr [esp+004h]
          cmp   ax, word ptr [esi]
          jle   LAB_00406c78
          mov   word ptr [esi], ax
LAB_00406c78:     pop   esi
          add   esp, 000000008h
          ret   00008h
LAB_00406c7f:
          db 090h
@statusWindowFindLongestTextString@16 endp
~

COMMENT ~
@statusWindowReleaseDC@4 proc
          mov   eax, dword ptr [hSkiStatusWnd]  ; <c624>
          push  esi
          mov   esi, ecx
          cmp   esi, eax
          jz    LAB_00406c9b
          mov   edx, 000001123h
          mov   ecx, offset sourceFilename      ; <c090>
          call  @assertFailed@8
LAB_00406c9b:     mov   eax, dword ptr [statusWindowFont]       ; <c664>
          test  eax, eax
          jz    LAB_00406cb1
          push  eax
          mov   eax, dword ptr [statusWindowDC] ; <c6cc>
          push  eax
          call  dword ptr [__imp__SelectObject@8]       ; <SelectObject>
LAB_00406cb1:     mov   ecx, dword ptr [statusWindowDC] ; <c6cc>
          push  ecx
          push  esi
          call  dword ptr [__imp__ReleaseDC@8]  ; <ReleaseDC>
          pop   esi
          ret
LAB_00406cc1:
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
@statusWindowReleaseDC@4 endp
~

end
