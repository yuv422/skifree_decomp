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
//extern void __fastcall updateActorRectsAfterPlayerMove(short newPlayerX,short newPlayerY);
USHORT __fastcall random(short maxValue);
extern int randomActorType1();
extern int randomActorType2();
extern int randomActorType3();
extern int areaBasedActorType();
extern Actor * __fastcall addActorOfType(int actorType, UINT frameNo);
extern short __fastcall getSpriteIdxForActorType(int actorType);
extern Actor * __fastcall addActorOfTypeWithSpriteIdx(int actorType, USHORT spriteIdx);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp)!=0 || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


//int randomActorType3() {
//    if (totalAreaOfActorSprites > windowWithMarginTotalArea / 16) {
//        return 0x12;
//    }
//
//    return random(0x40) != 0 ? 0xb + 2 : 2;
//}

int randomActorType2() {
    USHORT uVar1;

    if (totalAreaOfActorSprites > windowWithMarginTotalArea / 32) {
        return 0x12;
    }

    uVar1 = random(100);
    if (uVar1 < 2) {
        return 0xa;
    }
    if (uVar1 < 0x14) {
        return 0xd;
    }
    if (uVar1 < 0x32) {
        return 0xf;
    }
    if (uVar1 < 0x3c) {
        return 0xb;
    }
    return uVar1 < 0x50 ? 0xe : 0x10;
}