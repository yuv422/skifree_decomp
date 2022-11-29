extern @drawActor@8:proc

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