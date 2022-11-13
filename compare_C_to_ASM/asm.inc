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
