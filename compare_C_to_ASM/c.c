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

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


/* WARNING: Could not reconcile some variable overlaps */

void __fastcall drawWindow(HDC hdc, RECT *windowRect) {
//    LONG LVar1;
    RECT *rect1;
    RECT *ptVar3;
    UINT uVar4;
    Actor *pAVar6;
    Actor *pAVar7;

    ski_assert(hdc, 1272);
    ski_assert(windowRect, 1273);

//    pAVar7 = actorListPtr;
    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
        /* if FLAG_1 FLAG_2 FLAG_8 are unset */
        if ((pAVar7->flags & (FLAG_1 | FLAG_2 | FLAG_8)) == 0) {
            pAVar6 = pAVar7->linkedActor;
            if ( pAVar6 != NULL && (pAVar6->flags & FLAG_1) != 0 && (pAVar6->flags & FLAG_2) != 0 && pAVar7->spriteIdx2 == pAVar6->spriteIdx2) {
                if ((pAVar6->flags & FLAG_4) != 0) {
                    ptVar3 = &pAVar6->someRect;
                } else {
                    ptVar3 = updateActorSpriteRect(pAVar6);
                }
                if ((pAVar7->flags & FLAG_4) != 0) {
                    rect1 = &pAVar7->someRect;
                } else {
                    rect1 = updateActorSpriteRect(pAVar7);
                }
                if (areRectanglesEqual(rect1,ptVar3)) {
                    pAVar7->flags |= FLAG_1;
                    pAVar6->flags = pAVar6->flags &= 0xfffffffe;
                    actorSetFlag8IfFlag1IsUnset(pAVar6);
                }
            }
        }
    }
//    pAVar6 = actorListPtr;
//    for (; actorListPtr = pAVar6, pAVar5 != (Actor *)0x0; pAVar5 = pAVar5->next) {
    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
//        uVar4 = *(UINT *)&pAVar5->flags;
        if ((pAVar7->flags & FLAG_8) != 0) {
            pAVar7->flags &= 0xffffffef;
        } else {
            if ((pAVar7->flags & FLAG_4) != 0) {
                ptVar3 = &pAVar7->someRect;
            } else {
                ptVar3 = updateActorSpriteRect(pAVar7);
            }
            uVar4 = doRectsOverlap(ptVar3,windowRect);
            /* set FLAG_10 if rects overlap */
//            pAVar5->flags = (uVar4 ? FLAG_10 : 0) | (pAVar5->flags & 0xffffffef);
            pAVar7->flags = (pAVar7->flags & 0xffffffef) | ((uVar4 & 1) << 4);
            if ((uVar4 & 1) != 0) {
                (pAVar7->rect).left = ptVar3->left;
                (pAVar7->rect).top = ptVar3->top;
                (pAVar7->rect).right = ptVar3->right;
                (pAVar7->rect).bottom = ptVar3->bottom; // LVar1;
//                LVar1 = ptVar3->bottom;
                pAVar7->actorPtr = (Actor *)0x0;
            }
        }
    }


//    pAVar6 = actorListPtr;
//    pAVar7 = pAVar6;
//    if (pAVar6 != (Actor *)0x0) {
//        do {
    for (pAVar7 = actorListPtr; pAVar7 != NULL; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & FLAG_10) != 0) {
            pAVar6 = pAVar7->linkedActor;
//                    pAVar5 = actorListPtr;
//                if (pAVar6 == (Actor *)0x0) goto LAB_004011cd;
//                if ((pAVar6->flags & FLAG_10) == 0) goto LAB_004011cd;
//                BVar2 = doRectsOverlap(&pAVar7->rect,&pAVar6->rect);
//                pAVar5 = actorListPtr;
//                if (BVar2 == 0) goto LAB_004011cd;

            if (pAVar6 != (Actor *) 0x0 && (pAVar6->flags & FLAG_10) != 0 &&
                doRectsOverlap(&pAVar7->rect, &pAVar6->rect)) {
                actorClearFlag10(pAVar7, pAVar6);
            }

            for (pAVar6 = actorListPtr; pAVar6 != NULL && pAVar6 != pAVar7; pAVar6 = pAVar6->next) {
                if ((pAVar6->flags & FLAG_10) != 0 && doRectsOverlap(&pAVar7->rect, &pAVar6->rect)) {
                    actorClearFlag10(pAVar7, pAVar6);
                    pAVar6 = actorListPtr;
                }
            }
        }
    }
//                    do {
////                    LAB_004011cd:
//                        while (TRUE) {
//                            pAVar6 = actorListPtr;
//                            if ((pAVar5 == (Actor *) 0x0) || (pAVar7 == pAVar5)) goto LAB_004011f2;
//                            if (((pAVar5->flags & FLAG_10) != 0) &&
//                                (BVar2 = doRectsOverlap(&pAVar7->rect, &pAVar5->rect), pAVar6 = pAVar5, BVar2 != 0))
//                                break;
//                            pAVar5 = pAVar5->next;
//                        }
//                        actorClearFlag10(pAVar7, pAVar6);
//                        pAVar5 = actorListPtr;
//                    } while (TRUE);
//                }
//                LAB_004011f2:
//                ;
//            }
//            pAVar7 = pAVar7->next;
//        } while (pAVar7 != (Actor *)0x0);
//    }

    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & FLAG_10) != 0) {
            drawActor(hdc,pAVar7);
        }
    }

    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & FLAG_2) != 0) {
            actorSetFlag8IfFlag1IsUnset(pAVar7);
        }
    }
    removeFlag8ActorsFromList();
}
















