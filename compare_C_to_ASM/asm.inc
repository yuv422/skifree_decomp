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