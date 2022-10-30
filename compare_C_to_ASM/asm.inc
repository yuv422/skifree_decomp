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