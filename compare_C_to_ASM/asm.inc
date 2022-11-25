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
