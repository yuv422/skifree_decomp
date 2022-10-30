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