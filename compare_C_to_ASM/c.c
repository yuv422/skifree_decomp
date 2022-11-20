#include <windows.h>

#include "../types.h"

#include "../resource.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern void __fastcall enlargeRect(RECT *rect1, RECT *rect2);
extern char * __fastcall getCachedString(UINT stringIdx);
extern short __fastcall formatElapsedTime(int totalMillis,LPSTR outputString);
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
extern void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5);
extern void __fastcall updatePermObjectActorType4(PermObject *permObject);
extern void __fastcall FUN_00404350(PermObject *permObject);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp)!=0 || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//

void __fastcall FUN_00404350(PermObject *permObject) {
    short permObjX;
    short permObjY;
    int iVar6;
    short sVar9;
    int actorFrameNo;
    short local_c;
    short pX;
    short pY;
    int tickRelated;
    int dX;
    int dY;

    sVar9 = 0;
    actorFrameNo = permObject->actorFrameNo;
    iVar6 = permObject->actorTypeMaybe;
    ski_assert(permObject, 2664);
    if (permObject->unk_0x18 > 0) {
        permObject->unk_0x1e--;
    }
    else {
        permObject->unk_0x1e = 0;
        permObject->unk_0x18 = 0;
    }
    if (permObject->unk_0x18 == 0) { //goto LAB_004046b8;

        if (actorFrameNo >= 0x32 && actorFrameNo < 0x38) {
            tickRelated = currentTickCount - permObject->unk_0x20;
            switch (actorFrameNo) {
                case 0x32:
                    permObject->actorFrameNo = 0x33;
                    return;
                case 0x33:
                    permObject->actorFrameNo = (tickRelated < 500) ? 0x32 : 0x34; // ((499 < iVar6) - 1 & 0xfffffffe) + 0x34;
                    return;
                case 0x34:
                    if (tickRelated > 700) {
                        permObject->actorFrameNo = 0x35;
                        return;
                    }
                    break;
                case 0x35:
                    if (tickRelated > 1000) {
                        permObject->actorFrameNo = 0x36;
                        return;
                    }
                    break;
                case 0x36:
                    permObject->actorFrameNo = 0x37;
                    return;
                case 0x37:
                    permObject->actorFrameNo = iVar6 < 3000 ? 0x36 : 0x2a; // ((2999 < iVar6) - 1 & 0xc) + 0x2a;
                    return;
                default:
                    assertFailed(sourceFilename, 2678);
                    permObject->actorFrameNo = actorFrameNo;
                    return;
            }
//        goto LAB_004046b8;
            permObject->actorFrameNo = actorFrameNo;
            return;
        }
        permObjX = permObject->maybeX;
        permObjY = permObject->maybeY;
        local_c = 0;
        if (iVar6 == 5 && permObjY > -2000) {
            sVar9 = -10;
        } else if (iVar6 == 6 && permObjY < 32000) {
            sVar9 = 0x1a;
        } else if (iVar6 == 7 && permObjX > -16000) {
            local_c = -0x10;
        } else if (iVar6 == 8 && permObjX < 16000) {
            local_c = 0x10;
        } else {
//            LAB_004044dd:
            if (playerActor) {
                pX = playerActor->xPosMaybe;
                pY = playerActor->yPosMaybe;
//                    sVar3 = playerActor->xPosMaybe;
//                    sVar4 = playerActor->yPosMaybe;
//                if (iVar6 == 5 && sVar4 < -2000) {
//                    if () goto LAB_00404539;
//                }
//                else if (iVar6 == 6 && sVar4 > 32000) {
//                    if () goto LAB_00404539;
//                }
//                else if (iVar6 == 7 && sVar3 < -16000)

                if ((iVar6 == 5 && pY < -2000) ||
                    (iVar6 == 6 && pY > 32000) ||
                    (iVar6 == 7 && pX < -16000) ||
                    (iVar6 == 8 && pX > 16000)
                        ) {
                    dX = (int) pX - (int) permObjX;
                    dY = (int) pY - (int) permObjY;
//                    sVar9 = (short) windowWidth;
//                        iVar10 = (int) sVar9;
                    if (dX > windowWidth) {
//                        sVar9 = -sVar9;
//                        LAB_00404564:
                        permObject->maybeX = pX + -windowWidth;
                    } else if (dX < -windowWidth) { //(dX >= -sVar9) {
                        //goto LAB_00404564; // (SBORROW4(dX,-iVar10) != dX + iVar10 < 0) goto LAB_00404564;
                        permObject->maybeX = pX + windowWidth;
                    }
//                        iVar10 = (int) windowHeight;
                    if (dY > windowHeight) {
//                        sVar9 = playerActor->yPosMaybe - windowHeight;
//                        LAB_00404598:
                        permObject->maybeY = playerActor->yPosMaybe - windowHeight;
                    } else if (dY < -windowHeight) { //(SBORROW4(dY,-iVar10) != dY + iVar10 < 0) {
//                        sVar9 = playerActor->yPosMaybe + windowHeight;
                        permObject->maybeY = playerActor->yPosMaybe + windowHeight;
//                        goto LAB_00404598;
                    }
                    if (dX >= 0x10) {
                        dX = 0x10;
                    } else {
                        if (dX <= -0x10) {
                            dX = -0x10;
                        }
                    }
                    local_c = (short) dX;
                    if (dY >= 0x1a) {
                        dY = 0x1a;
                    } else {
                        if (dY <= -10) {
                            dY = -10;
                        }
                    }
                    sVar9 = (short) dY;
                    playSound(&sound_9);
                }
            }
        }
//    uVar11 = (UINT)local_c;
//    uVar8 = (UINT)sVar9;

        if (abs(local_c) > abs(sVar9)) {
            permObject->yVelocity = (short) ((int) ((int) permObject->xVelocity * sVar9) / (int) local_c);
//        LAB_00404617:
            permObject->unk_0x1e = 1;
        } else if (sVar9 != 0) {
            permObject->xVelocity = (short) ((int) ((int) permObject->yVelocity * local_c) / (int) sVar9);
//        goto LAB_00404617;
            permObject->unk_0x1e = 1;
        }
        permObject->yVelocity = sVar9;
        permObject->xVelocity = local_c;
        if (sVar9 < 0) {
            permObject->actorFrameNo = (actorFrameNo == 0x30) + 0x30;
            return;
        }
        if (local_c < 0) {
            permObject->actorFrameNo = (actorFrameNo == 0x2c) + 0x2c;
            return;
        }
        if ((local_c <= 0) && (sVar9 <= 0)) {
//            uVar5 = random(10);
            if (random(10) != 0) {
                permObject->actorFrameNo = 0x2a;
                return;
            }
            permObject->unk_0x1e = 4;
            permObject->actorFrameNo = 0x2b;
            return;
        }
        actorFrameNo = (actorFrameNo == 0x2e) + 0x2e;
    }
//    LAB_004046b8:
    permObject->actorFrameNo = actorFrameNo;
    return;
}


