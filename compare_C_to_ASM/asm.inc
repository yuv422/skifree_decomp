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