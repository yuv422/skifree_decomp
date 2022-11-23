extern @updateActorsAfterWindowResize@8: proc

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