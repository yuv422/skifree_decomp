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