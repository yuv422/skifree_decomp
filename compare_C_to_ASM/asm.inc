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