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
extern BOOL __fastcall areRectanglesEqual(RECT *rect1,RECT *rect2);
extern void __fastcall actorClearFlag10(Actor *actor1, Actor *actor2);
extern void __fastcall drawActor(HDC hdc,Actor *actor);
extern BOOL __fastcall changeScratchBitmapSize(short newWidth, short newHeight);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//



/* WARNING: Could not reconcile some variable overlaps */

void __fastcall drawActor(HDC hdc,Actor *actor) {
    Actor **ppAVar1;
    short y;
//    short sVar3;
//    BOOL BVar4;
//    UINT uVar5;
    RECT *rect;
//    int cx;
//    int cy;
    USHORT uVar6;
    Actor *pAVar7;
//    int y1;
    short sVar8;
    short newWidth;
    USHORT newHeight;
//    short sVar9;
//    UINT unaff_ESI;
    Actor *actor_00;
    short sVar10;
//    UINT unaff_EDI;
    Actor **ppAVar11;
    HDC hdcSrc;
    DWORD rop;
    Actor *local_24;
    Actor *local_20;
    int local_1c;
//    UINT local_18;
    UINT local_14;
    short sheetY;
    int local_c;
    UINT local_8;
    Actor **local_4;
    Sprite *sprite;
    short spriteWidth;
    short spriteHeight;

    uVar6 = *(USHORT *)&(actor->rect).left;
//    local_14 = /*unaff_EDI & 0xffff0000 |*/ (UINT)uVar6;
    y = *(short *)&(actor->rect).top;
    newWidth = *(short *)&(actor->rect).right - uVar6;
    newHeight = *(short *)&(actor->rect).bottom - y;
//    local_18 = unaff_ESI & 0xffff0000 | (UINT)newHeight;
//    local_18 = (UINT)newHeight;
    local_c = 0;
    local_20 = actor;
    ski_assert(actor, 1133);
    ski_assert(hdc, 1134);
    ski_assert((actor->flags & FLAG_10) != 0, 1135);

    if (actor == (Actor *)0x0) {
        return;
    }
    pAVar7 = actor;
    while ((pAVar7->flags & FLAG_1) << 1 != (pAVar7->flags & FLAG_2)) {
        pAVar7 = pAVar7->actorPtr;
        if (pAVar7 == (Actor *)0x0) {
            return;
        }
    }
    local_1c = 0;
    if (!changeScratchBitmapSize(newWidth,newHeight)) {
        PatBlt(hdc,(int)(short)uVar6,(int)y,(int)newWidth,(int)(short)newHeight,0xff0062);
        do {
            if ((actor->flags & FLAG_1) == 0 && (actor->flags & FLAG_2) == 0) {
                sprite = actor->spritePtr;
                if ((actor->flags & FLAG_4) == 0) {
                    rect = updateActorSpriteRect(actor);
                }
                else {
                    rect = &actor->someRect;
                }
                BitBlt(hdc,rect->left,rect->top,(int)sprite->width,(int)sprite->height,sprite->sheetDC,0
                        ,(int)sprite->sheetYOffset,0x8800c6);
                actor->flags |= FLAG_1;
            }
            else {
                actor->flags &= 0xfffffffe;
            }
            actor = actor->actorPtr;
        } while( actor != NULL );
        return;
    }

    do {
        actor_00 = (Actor *)0x0;
        local_24 = (Actor *)0x0;
        pAVar7 = actor;
        ppAVar11 = &local_20;
        if (actor == (Actor *)0x0) break;
        do {
//            sprite = *(Sprite **)&actor->flags;
            ppAVar1 = &actor->actorPtr;
            if ((actor->flags & FLAG_2) == 0) {
                if ((actor->flags & FLAG_40) == 0) {
                    sVar8 = 0;
                }
                else {
//                    sprite = actor->spritePtr;
                    sVar8 = actor->spritePtr->height;
                }
                uVar6 = actor->yPosMaybe - sVar8;
                if ((actor_00 == (Actor *)0x0) || ((short)uVar6 < (short)local_8)) {
                    actor_00 = actor;
                    local_24 = actor;
                    local_8 = uVar6; //actor->flags & 0xffff0000 | (UINT)uVar6;
                    local_4 = ppAVar11;
                }
            }
            else {
                if ((actor->flags & 1) != 0) {
                    local_c = 1;
                    actor->flags &= 0xfffffffe;
                }
                *ppAVar11 = *ppAVar1;
                pAVar7 = local_20;
            }
            actor = *ppAVar1;
            ppAVar11 = ppAVar1;
        } while (actor != (Actor *)0x0);
        actor = pAVar7;
        if (actor_00 != (Actor *)0x0) {
            sprite = actor_00->spritePtr;
            spriteWidth = sprite->width;
            spriteHeight = sprite->height;
            sheetY = sprite->sheetYOffset;
            if ((actor_00->flags & FLAG_4) == 0) {
                rect = updateActorSpriteRect(actor_00);
            }
            else {
                rect = &actor_00->someRect;
            }
//            cx = (int)sVar3;
            //local_14._0_2_ = *(short *)&rect->left - (short)local_14; // TODO fixme
            local_14 = rect->left - uVar6;
            sVar10 = *(short *)&rect->top - y;
            ski_assert(rect->right - rect->left == spriteWidth, 1203);
            ski_assert(rect->bottom - rect->top == spriteHeight, 1204);
            ski_assert(local_14 >= 0, 1205);
            ski_assert(sVar10 >= 0, 1206);
            ski_assert(newWidth >= spriteWidth, 1207);

//            if (rect->right - rect->left != spriteWidth) {
//                assertFailed(sourceFilename,1203);
//            }
//            cy = (int)sVar8;
//            if (rect->bottom - rect->top != spriteHeight) {
//                assertFailed(sourceFilename,1204);
//            }
//            if ((short)local_14 < 0) {
//                assertFailed(sourceFilename,1205);
//            }
//            if (sVar10 < 0) {
//                assertFailed(sourceFilename,1206);
//            }
//            if (newWidth < spriteWidth) {
//                assertFailed(sourceFilename,1207);
//            }
//            sVar9 = (short)local_18;
            if (newHeight < spriteHeight) {
                assertFailed(sourceFilename,1208);
            }
            if (local_1c == 0) {
                local_1c = 1;
                if ((((0 < (short)local_14) || (0 < sVar10)) || (spriteWidth < newWidth)) || (spriteHeight < newHeight))  {
                    PatBlt(bitmapSourceDC,0,0,(int)newWidth,(int)newHeight,0xff0062);
                }
                hdcSrc = sprite->sheetDC;
                rop = 0xcc0020;
            }
            else {
                BitBlt(bitmapSourceDC,(int)(short)local_14,(int)sVar10,spriteWidth,spriteHeight,sprite->sheetDC_1bpp,0,(int)sheetY ,
                       0xee0086);
                hdcSrc = sprite->sheetDC;
                rop = 0x8800c6;
            }
            BitBlt(bitmapSourceDC,(int)(short)local_14,(int)sVar10,spriteWidth,spriteHeight,hdcSrc,0,(int)sheetY,rop);
            local_24->flags |= FLAG_1;
            *local_4 = local_24->actorPtr;
            actor = local_20;
        }
    } while (actor != (Actor *)0x0);
    if (local_1c != 0) {
        BitBlt(hdc,(int)(short)local_14,(int)y,(int)newWidth,(int)(short)newHeight,bitmapSourceDC,0
                ,0,0xcc0020);
        return;
    }
    if (local_c != 0) {
        PatBlt(hdc,(int)(short)local_14,(int)y,(int)newWidth,(int)(short)newHeight,0xff0062);
    }
}






















