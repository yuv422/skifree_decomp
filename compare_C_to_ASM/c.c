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
extern void togglePausedState();
extern Actor * __fastcall addRandomActor(int borderType);
extern void __fastcall FUN_004046e0(PermObjectList *permObjList);
extern Actor * __fastcall updateActor(Actor *actor);
extern RECT * __fastcall updateActorSpriteRect(Actor *actor);
extern void __fastcall updateAllPermObjectsInList(PermObjectList *param_1);
extern void removeFlag8ActorsFromList();
extern Actor * __fastcall handleActorCollision(Actor *actor1,Actor *actor2);
extern Actor * __fastcall updateActorWithOffscreenStartingPosition(Actor *actor, int borderType);
extern HBITMAP __fastcall loadBitmapResource(UINT resourceId);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


/* WARNING: Could not reconcile some variable overlaps */

BOOL __fastcall createBitmapSheets(HDC param_1) {
    HBITMAP pHVar1;
    HGDIOBJ pvVar2;

    int resourceId;
    Sprite *sprite;
    short maxWidth;
    int smallBitmapSheetHeight;
    int largeBitmapSheetHeight;
    int largeSpriteYOffset;
    int smallSpriteYOffset;
    int sheetYOffset;
    short maxHeight;
    BITMAP bitmap;
    int spriteWidth;
    int spriteHeigth;

    sprites->sheetDC = NULL;
    sprites->sheetDC_1bpp = NULL;
    sprites->sheetYOffset = 0;
    sprites->width = 0;
    sprites->height = 0;
    sprites->totalPixels = 0;
    maxWidth = 0;
    maxHeight = 0;
    largeBitmapSheetHeight = 0;
    smallBitmapSheetHeight = 0;
    smallSpriteYOffset = 0;
    largeSpriteYOffset = 0;

    for (resourceId = 1; (USHORT)resourceId < 90; resourceId++) {
        pHVar1 = loadBitmapResource(resourceId);
        if (pHVar1 == NULL) {
            return FALSE;
        }
        GetObjectA(pHVar1,sizeof(BITMAP),&bitmap);
        if (bitmap.bmWidth > maxWidth) {
            maxWidth = (short)bitmap.bmWidth;
        }
        if (bitmap.bmHeight > maxHeight) {
            maxHeight = (short)bitmap.bmHeight;
        }
        if (bitmap.bmWidth > 32) {
            largeBitmapSheetHeight += bitmap.bmHeight;
        } else {
            smallBitmapSheetHeight += bitmap.bmHeight;
        }
        DeleteObject(pHVar1);
    }

    smallBitmapDC = CreateCompatibleDC(param_1);
    if (!smallBitmapDC) {
        return FALSE;
    }
    pHVar1 = CreateCompatibleBitmap(param_1,32,(int)(short)smallBitmapSheetHeight);
    if (pHVar1 == (HBITMAP)0x0) {
        return FALSE;
    }
    smallBitmapSheet = SelectObject(smallBitmapDC,pHVar1);
    if (smallBitmapSheet == (HGDIOBJ)0x0) {
        DeleteObject(pHVar1);
        return FALSE;
    }
    smallBitmapDC_1bpp = CreateCompatibleDC(param_1);
    if (smallBitmapDC_1bpp == (HDC)0x0) {
        return FALSE;
    }
    pHVar1 = CreateBitmap(32,(int)(short)smallBitmapSheetHeight,1,1,(void *)0x0);
    if (pHVar1 == (HBITMAP)0x0) {
        return FALSE;
    }
    smallBitmapSheet_1bpp = SelectObject(smallBitmapDC_1bpp,pHVar1);
    if (smallBitmapSheet_1bpp == (HGDIOBJ)0x0) {
        DeleteObject(pHVar1);
        return FALSE;
    }
    largeBitmapDC = CreateCompatibleDC(param_1);
    if (largeBitmapDC == (HDC)0x0) {
        return FALSE;
    }
    pHVar1 = CreateCompatibleBitmap
            (param_1,(int)(short)(USHORT)maxWidth,(int)(short)largeBitmapSheetHeight);
    if (pHVar1 == (HBITMAP)0x0) {
        return FALSE;
    }
    largeBitmapSheet = SelectObject(largeBitmapDC,pHVar1);
    if (largeBitmapSheet == (HGDIOBJ)0x0) {
        DeleteObject(pHVar1);
        return FALSE;
    }
    largeBitmapDC_1bpp = CreateCompatibleDC(param_1);
    if (largeBitmapDC_1bpp == (HDC)0x0) {
        return FALSE;
    }
    pHVar1 = CreateBitmap((int)(short)(USHORT)maxWidth,(int)(short)largeBitmapSheetHeight,1,1,
                          (void *)0x0);
    if (pHVar1 == (HBITMAP)0x0) {
        return FALSE;
    }

    largeBitmapSheet_1bpp = SelectObject(largeBitmapDC_1bpp,pHVar1);
    if (largeBitmapSheet_1bpp == (HGDIOBJ)0x0) {
        DeleteObject(pHVar1);
        return FALSE;
    }
    bitmapSourceDC = CreateCompatibleDC(param_1);
    for (resourceId = 1; (USHORT)resourceId < 90; resourceId++) {
        sprite = &sprites[resourceId & 0xffff];
        pHVar1 = loadBitmapResource(resourceId);
        if (pHVar1 == (HBITMAP)0x0) {
            return FALSE;
        }
        GetObjectA(pHVar1,sizeof(BITMAP),&bitmap);

        spriteWidth = bitmap.bmWidth;
        spriteHeigth = bitmap.bmHeight;

        sprite->width = (short)spriteWidth;
        sprite->height = (short)spriteHeigth;
        sprite->totalPixels = (short)(spriteWidth * spriteHeigth);
        if ((short)spriteWidth > 0x20) {
            sheetYOffset = largeSpriteYOffset;
            largeSpriteYOffset += spriteHeigth;
        } else {
            sheetYOffset = smallSpriteYOffset;
            smallSpriteYOffset += spriteHeigth;
        }
        sprite->sheetYOffset = (short)sheetYOffset;
        pvVar2 = SelectObject(bitmapSourceDC,pHVar1);
        sprite->sheetDC = (short)spriteWidth > 32 ? largeBitmapDC : smallBitmapDC;

        sprite->sheetDC_1bpp = (short)spriteWidth > 32 ? largeBitmapDC_1bpp : smallBitmapDC_1bpp;

        BitBlt(sprite->sheetDC,0,sheetYOffset,bitmap.bmWidth,bitmap.bmHeight,bitmapSourceDC,0,0,
               0xcc0020);
        BitBlt(sprite->sheetDC_1bpp,0,sheetYOffset,bitmap.bmWidth,bitmap.bmHeight,
               bitmapSourceDC,0,0,0x330008);
        pvVar2 = SelectObject(bitmapSourceDC,pvVar2);
        DeleteObject(pvVar2);
    }

    scratchBitmapWidth = ((USHORT)maxWidth & 0xffc0) + 0x40;
    scratchBitmapHeight = ((USHORT)maxHeight & 0xffc0) + 0x40;

    pHVar1 = CreateCompatibleBitmap(param_1,(int)scratchBitmapWidth,(int)scratchBitmapHeight);
    if (pHVar1 == (HBITMAP)0x0) {
        return FALSE;
    }
    scratchBitmap = SelectObject(bitmapSourceDC,pHVar1);
    if (scratchBitmap == (HGDIOBJ)0x0) {
        DeleteObject(pHVar1);
        return FALSE;
    }
    return TRUE;
}
















