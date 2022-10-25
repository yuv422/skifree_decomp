#include <windows.h>

#include "../types.h"

#include "../resource.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern void __fastcall enlargeRect(RECT *rect1, RECT *rect2);
extern char * __fastcall getCachedString(UINT stringIdx);
extern int __fastcall formatElapsedTime(int totalMillis,LPSTR outputString);
extern void __fastcall drawText(HDC hdc,LPCSTR textStr,short x,short *y,int textLen);
extern void updateGameState();
extern void __fastcall drawWindow(HDC hdc, RECT *rect);
extern void __fastcall formatAndPrintStatusStrings(HDC windowDC);
extern Actor * getFreeActor();
extern Actor * __fastcall actorSetSpriteIdx(Actor *actor,USHORT spriteIdx);
extern Actor * __fastcall FUN_00402220(Actor *actor);
extern BOOL __fastcall isSlowTile(short spriteIdx);
extern Actor * __fastcall addActor(Actor *actor, BOOL insertBack);
extern void __fastcall getRandomOffscreenStartingPosition(int borderType,short *xPos,short *yPos);
extern Actor * __fastcall updateActorPositionMaybe(Actor *actor,short newX,short newY,short inAir);
extern Actor * __fastcall duplicateAndLinkActor(Actor *actor);
extern void __fastcall updateActorRectsAfterPlayerMove(short newPlayerX,short newPlayerY);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp)!=0 || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


Actor * __fastcall updateActorPositionMaybe(Actor *actor,short newX,short newY,short inAir) {
    int uVar1;
    BOOL bVar2;
    byte bVar3;
    BOOL bVar4;
    BOOL isPlayer;

    if ((actor->xPosMaybe == newX) && (actor->yPosMaybe == newY)) {
        bVar2 = FALSE;
    }
    else {
        bVar2 = TRUE;
    }
    bVar4 = actor->isInAir != inAir;
    isPlayer = actor != playerActorPtrMaybe_1;
    ski_assert(actor, 1037);

    if (isPlayer) {
        if (bVar2) goto LAB_00402404;
    }
    else if (bVar2) {
        updateActorRectsAfterPlayerMove(newX,newY);
        goto LAB_00402404;
    }
    if (!bVar4) {
        return actor;
    }
    LAB_00402404:
    uVar1 = *(UINT *)&actor->flags;
    if ((uVar1 & FLAG_1) != 0) {
        actor = duplicateAndLinkActor(actor);
    }
    if (((-1 < (int)(uVar1 << 0x1d)) || (isPlayer)) || (bVar4)) {
        bVar3 = 0;
    }
    else {
        bVar3 = 1;
    }
    actor->yPosMaybe = newY;
    actor->xPosMaybe = newX;
    actor->isInAir = inAir;
    *(UINT *)&actor->flags = (UINT)(bVar3 | 8) << 2 | *(UINT *)&actor->flags & 0xfffffffb;
    return actor;
}



