#include <windows.h>

#include "../types.h"

#include "../resource.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern void __fastcall enlargeRect(RECT *rect1, RECT *rect2);
extern char * __fastcall getCachedString(UINT stringIdx);
extern int __fastcall formatElapsedTime(int totalMillis, LPSTR outputString);
extern void __fastcall drawText(HDC hdc,LPCSTR textStr,short x,short *y,int textLen);
extern void updateGameState();
extern void __fastcall drawWindow(HDC hdc, RECT *rect);
extern void __fastcall formatAndPrintStatusStrings(HDC windowDC);
extern Actor * getFreeActor();
extern Actor * __fastcall actorSetSpriteIdx(Actor *actor, USHORT spriteIdx);
extern Actor * __fastcall FUN_00402220(Actor *actor);
extern BOOL __fastcall isSlowTile(short spriteIdx);
extern Actor * __fastcall addActor(Actor *actor, BOOL insertBack);
extern void __fastcall getRandomOffscreenStartingPosition(int borderType,short *xPos,short *yPos);
extern Actor * __fastcall updateActorPositionMaybe(Actor *actor, short newX, short newY, short inAir);
extern Actor * __fastcall duplicateAndLinkActor(Actor *actor);
//extern void __fastcall updateActorRectsAfterPlayerMove(short newPlayerX,short newPlayerY);
short __fastcall random(short maxValue);
extern int randomActorType1();
extern int randomActorType2();
extern int randomActorType3();
extern int areaBasedActorType();
extern Actor * __fastcall addActorOfType(int actorType, UINT frameNo);
//extern short __fastcall getSpriteIdxForActorType(int actorType);
extern Actor * __fastcall addActorOfTypeWithSpriteIdx(int actorType, USHORT spriteIdx);
extern Actor * __fastcall updateActorType1_Beginner(Actor *actor);
extern Actor * __fastcall updateActorType2_dog(Actor *actor);
extern Actor * __fastcall updateActorType3_snowboarder(Actor *actor);
extern Actor * __fastcall updateActorType9_treeOnFire(Actor *actor);
;extern Actor * __fastcall updateActorTypeA_walkingTree(Actor *actor);
extern Actor *__fastcall updateActorPositionWithVelocityMaybe(Actor *actor);
extern Actor * __fastcall updateActorVelMaybe(Actor *actor,ActorVelStruct *param_2);
extern void __fastcall addStylePoints(int points);
extern void __fastcall playSound(Sound *sound);
extern Actor * __fastcall setActorFrameNo(Actor *actor, int frameNo);
extern void __fastcall updateSsGameMode(Actor *actor,short param_2,short param_3);
extern void __fastcall updateFsGameMode(Actor *actor,short param_2,short param_3);
extern void __fastcall updateGsGameMode(Actor *actor,short param_2,short param_3);
extern Actor * __fastcall updatePlayerActor(Actor *actor);
extern int __fastcall FUN_00402e30(int param_1,int param_2,int param_3,int param_4,int param_5);
extern void resetPlayerFrameNo();
extern void __fastcall updateEntPackIniKeyValue(LPCSTR configKey, int value, int isTime);
extern void __fastcall permObjectSetSpriteIdx(PermObject *permObject, USHORT spriteIdx);
extern Actor * __fastcall getLinkedActorIfExists(Actor *actor);
extern void __fastcall actorSetFlag8IfFlag1IsUnset(Actor *actor);
extern void __fastcall updatePermObject(PermObject *permObject);
extern Actor * __fastcall addActorForPermObject(PermObject *permObject);
extern BOOL __fastcall doRectsOverlap(RECT *rect1, RECT *rect2);
//extern void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5);
extern void __fastcall updatePermObjectActorType4(PermObject *permObject);
extern void __fastcall FUN_00404350(PermObject *permObject);
extern int allocateMemory();
extern int resetGame();
extern BOOL __fastcall initWindows(HINSTANCE hInstance,HINSTANCE hPrevInstance,int nCmdShow);
extern BOOL setupGame();
extern void cleanupSound();
extern int __fastcall showErrorMessage(LPCSTR text);
extern void setupActorList();
extern void resetPermObjectCount();
extern void handleGameReset();
extern int __fastcall getSkierGroundSpriteFromMousePosition(short param_1,short param_2);
extern int __fastcall getSkierInAirSpriteFromMousePosition(short param_1,short param_2);
extern void __fastcall updateActorsAfterWindowResize(short centreX, short param_2);
extern void __fastcall setPointerToNull(PermObjectList *param_1);
extern PermObject * __fastcall addPermObject(PermObjectList *objList, PermObject *permObject);
extern USHORT __fastcall getSpriteIdxForActorType(int actorType);



#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void setupPermObjects() {
    BOOL bVar1;
    USHORT uVar2;
    PermObject *pPVar3;
    short sVar4;
    PermObject permObject;
    int d;

    permObject.unk_0x1e = 0;
    permObject.yVelocity = 0;
    permObject.xVelocity = 0;
    permObject.unk_0x18 = 0;
    setPointerToNull(&PermObjectList_0040c630);
    permObject.actorTypeMaybe = 0x11;
    permObject.maybeX = ((short)playerX - skierScreenXOffset) + windowClientRect.left + 60;
    permObject.spriteIdx = 0x3d;
    if (permObject.maybeX < -320) {
        permObject.maybeX = -320;
    }
    permObject.maybeY = ((short)playerY - skierScreenYOffset) + windowClientRect.bottom - 60;
    if (640 < permObject.maybeY) {
        permObject.maybeY = 520;
    }
    addPermObject(&PermObjectList_0040c630,&permObject);
    permObject.spriteIdx = 0x39;
    permObject.maybeX = -576;
    permObject.maybeY = 640;
    addPermObject(&PermObjectList_0040c630,&permObject);
    permObject.spriteIdx = 0x3a;
    permObject.maybeX = -320;
    addPermObject(&PermObjectList_0040c630,&permObject);
    permObject.actorTypeMaybe = 0xc;
    bVar1 = TRUE;
    firstSlalomFlagLeft = (PermObject *)0x0;
    /* slalom flags */
    sVar4 = 960;
    do {
        permObject.spriteIdx = bVar1 ? 0x17 : 0x18; //0x18 - (USHORT)bVar1;
        permObject.maybeX =  bVar1 ? -496 : -400; //(-(USHORT)bVar1 & 0xffa0) + -400;
        bVar1 = !bVar1;
        permObject.maybeY = sVar4;
        pPVar3 = addPermObject(&PermObjectList_0040c630,&permObject);
        if (firstSlalomFlagLeft == (PermObject *)0x0) {
            firstSlalomFlagLeft = pPVar3;
        }
        sVar4 = sVar4 + 320;
    } while (sVar4 < 8640);
    permObject.actorTypeMaybe = 0x11;
    permObject.spriteIdx = 0x3b;
    permObject.maybeX = -576;
    permObject.maybeY = 8640;
    addPermObject(&PermObjectList_0040c630,&permObject);
    permObject.spriteIdx = 0x3c;
    permObject.maybeX = -320;
    addPermObject(&PermObjectList_0040c630,&permObject);
    setPointerToNull(&PermObjectList_0040c5e0);
    permObject.actorTypeMaybe = 0x11;
    permObject.spriteIdx = 0x3e;
    permObject.maybeX =
            ((short)windowClientRect.right - skierScreenXOffset) + -0x3c + (short)playerX;
    if (permObject.maybeX > 320) {
        permObject.maybeX = 320;
    }
    permObject.maybeY =
            ((short)windowClientRect.bottom - skierScreenYOffset) + playerY + -0x3c;
    if (0x280 < permObject.maybeY) {
        permObject.maybeY = 520;
    }
    addPermObject(&PermObjectList_0040c5e0,&permObject);
    permObject.spriteIdx = 0x39;
    permObject.maybeX = 320;
    permObject.maybeY = 640;
    addPermObject(&PermObjectList_0040c5e0,&permObject);
    permObject.spriteIdx = 0x3a;
    permObject.maybeX = 512;
    addPermObject(&PermObjectList_0040c5e0,&permObject);
    bVar1 = TRUE;
    FirstSlalomFlagRight = (PermObject *)0x0;
    /* slalom flags, right hand side */
    sVar4 = 0x410;
    do {
        permObject.actorTypeMaybe = 0xc;
        permObject.spriteIdx = bVar1 ? 0x17 : 0x18;
        permObject.maybeX = bVar1 ? 400 : 432;
        bVar1 = !bVar1;
        permObject.maybeY = sVar4;
        pPVar3 = addPermObject(&PermObjectList_0040c5e0,&permObject);
        if (FirstSlalomFlagRight == (PermObject *)0x0) {
            FirstSlalomFlagRight = pPVar3;
        }
        permObject.actorTypeMaybe = 0xd;
        permObject.spriteIdx = getSpriteIdxForActorType(0xd);
        uVar2 = random(0x20);
        permObject.maybeX = uVar2 + 400;
        /* this should use the return value */
        random(400);
        sVar4 = sVar4 + 400;
    } while (sVar4 < 0x4100);
    permObject.actorTypeMaybe = 0x11;
    /* finish sign left */
    permObject.spriteIdx = 0x3b;
    permObject.maybeX = 320;
    permObject.maybeY = 16640;
    addPermObject(&PermObjectList_0040c5e0,&permObject);
    /* finish sign right */
    permObject.spriteIdx = 0x3c;
    permObject.maybeX = 512;
    addPermObject(&PermObjectList_0040c5e0,&permObject);
    setPointerToNull(&PermObjectList_0040c658);

    permObject.actorTypeMaybe = 0x11;
    permObject.spriteIdx = 0x3f;
    permObject.maybeX = 0;
    permObject.maybeY = (windowClientRect.bottom - skierScreenYOffset);
    permObject.maybeY += playerY;
    permObject.maybeY -= 0x3c;
    if (0x280 < permObject.maybeY) {
        permObject.maybeY = 520;
    }
    addPermObject(&PermObjectList_0040c658,&permObject);
    permObject.spriteIdx = 0x39;
    permObject.maybeX = -160;
    permObject.maybeY = 640;
    addPermObject(&PermObjectList_0040c658,&permObject);
    permObject.spriteIdx = 0x3a;
    permObject.maybeX = 160;
    addPermObject(&PermObjectList_0040c658,&permObject);
    permObject.spriteIdx = 0x3b;
    permObject.maybeX = -160;
    permObject.maybeY = 16640;
    addPermObject(&PermObjectList_0040c658,&permObject);
    permObject.spriteIdx = 0x3c;
    permObject.maybeX = 160;
    addPermObject(&PermObjectList_0040c658,&permObject);
    INT_0040c968 = 0;
    isFsGameMode = 0;
    setPointerToNull(&PermObjectList_0040c738);
    /* ski lift poles??? */
    sVar4 = -1024;
    do {
        permObject.actorTypeMaybe = 0xd;
        permObject.spriteIdx = 0x40;
        permObject.maybeX = -128;
        permObject.maybeY = sVar4;
        permObject.unk_0x18 = 0;
        permObject.unk_0x1e = 0;
        permObject.yVelocity = 0;
        permObject.xVelocity = 0;
        addPermObject(&PermObjectList_0040c738,&permObject);
        sVar4 = sVar4 + 2048;
    } while (sVar4 <= 23552);
    setPointerToNull(&PermObjectList_0040c720);
    sVar4 = -1024;
    do {
        permObject.actorTypeMaybe = 4;
        permObject.spriteIdx = 0;
        permObject.unk_0x1e = 0;
        permObject.xVelocity = 0;
        permObject.unk_0x18 = 0x20;
        permObject.maybeY = sVar4;
        if (-1024 < sVar4) {
            permObject.actorFrameNo = 0x27;
            permObject.maybeX = -112;
            permObject.yVelocity = -2;
            addPermObject(&PermObjectList_0040c720,&permObject);
        }
        if (sVar4 < 23552) {
            permObject.actorFrameNo = 0x29;
            permObject.maybeX = -144;
            permObject.yVelocity = 2;
            addPermObject(&PermObjectList_0040c720,&permObject);
        }
        sVar4 = sVar4 + 2048;
    } while (sVar4 <= 23552);
    permObject.actorTypeMaybe = 7;
    permObject.actorFrameNo = 0x2a;
    permObject.spriteIdx = 0;
    permObject.maybeX = -16060;
    permObject.unk_0x18 = 0;
    permObject.maybeY = 0;
    permObject.unk_0x1e = 0;
    permObject.yVelocity = 0;
    permObject.xVelocity = 0;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = 8;
    permObject.maybeX = 16060;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = 5;
    permObject.maybeX = 0;
    permObject.maybeY = -2060;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = 6;
    permObject.maybeY = 32060;
    addPermObject(&PermObjectList_0040c720,&permObject);
}






