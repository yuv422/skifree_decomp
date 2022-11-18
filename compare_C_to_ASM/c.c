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
extern Actor * __fastcall updateActorPositionMaybe(Actor *actor,short newX,short newY,short inAir);
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

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp)!=0 || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//


void __fastcall updateAllPermObjectsInList(PermObjectList *param_1) {
    short top = (short)((windowClientRectWith120Margin.top - skierScreenYOffset) - 0x3c);
    short bottom = (short)((windowClientRectWith120Margin.bottom - skierScreenYOffset) + 0x3c);
    short sVar4;
    PermObject *permObject;

    permObject = param_1->startingObject;
    ski_assert(param_1, 2829);
    ski_assert(permObject <= param_1->nextObject, 2830);

    if (permObject < param_1->nextObject) {
        do {
            updatePermObject(permObject);
            sVar4 = permObject->maybeY - playerY;
            if ((sVar4 >= top) && (sVar4 < bottom))
            {
                addActorForPermObject(permObject);
            }
            permObject++;
        } while (permObject < param_1->nextObject);
    }
    return;
}




//Actor * __fastcall handleActorCollision(Actor *actor1,Actor *actor2) {
//    short sVar1;
//    short sVar2;
//    short sVar3;
//    int iVar4;
//    BOOL bVar5;
//    Actor *pAVar6;
//    Sound *sound;
//    short sVar9;
//    short actor1y;
//    short actor2y;
//    UINT local_c;
//    short maxSpriteWidth;
//
//    ski_assert(actor1, 2350);
//    ski_assert(actor2, 2351);
//
//    if (actor1->typeMaybe >= 11) {
//        return actor1;
//    }
//    actor1y = actor1->yPosMaybe;
//    actor2y = actor2->yPosMaybe;
//    pAVar6 = getLinkedActorIfExists(actor1);
//    sVar2 = pAVar6->yPosMaybe;
//    pAVar6 = getLinkedActorIfExists(actor2);
//    sVar3 = pAVar6->yPosMaybe;
//    if ((((actor1y < actor2y) || (sVar2 > sVar3)) && ((actor1y > actor2y  || (sVar2 < sVar3)))) ||
//        ((actor1y == actor2y && (sVar2 == sVar3)))) {
//        bVar5 = FALSE;
//    }
//    else {
//        bVar5 = TRUE;
//    }
//    iVar4 = actor2->typeMaybe;
//    local_c = actor1->frameNo;
//    sVar1 = actor1->isInAir;
//    sVar9 = actor2->spritePtr->height + actor2->isInAir;
//    switch(actor1->typeMaybe) {
//        case 10:
//            actor1->HorizontalVelMaybe = 0;
//            return setActorFrameNo(actor1,0x3c);
//        case 5:
//        case 6:
//        case 7:
//        case 8:
//            if (actor2 == playerActor) {
//                ski_assert(iVar4 == 0, 2393);
//                playSound(&sound_7);
//                if ((actor2->flags & FLAG_1) != 0) {
//                    actor2 = duplicateAndLinkActor(actor2);
//                }
//                actorSetFlag8IfFlag1IsUnset(actor2);
//                ski_assert(actor1->permObject, 2396);
//
//                actor1->permObject->actorFrameNo = 0x32;
//                actor1->HorizontalVelMaybe = 0;
//                actor1->permObject->unk_0x1a = 0;
//                actor1->verticalVelocityMaybe = 0;
//                actor1->permObject->unk_0x1c = 0;
//                actor1->permObject->unk_0x20 = currentTickCount;
//                return setActorFrameNo(actor1,0x32);
//            }
//            break;
//        case ACTOR_TYPE_0_PLAYER:
//            if (local_c == 0x11) break;
//            switch(iVar4) {
//                case 0xf:
//                    if (sVar1 < 1) {
//                        actor1->inAirCounter = 4;
////                        LAB_00403cb4:
//                        addStylePoints(1);
//                        playSound(&sound_2);
//                        return setActorFrameNo(actor1,0xd);
//                    }
//                    if (sVar9 <= sVar1) break;
////                LAB_00403bcc:
//                    actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
//                    addStylePoints(1);
//                    sound = &sound_2;
////                LAB_00403be8:
//                    playSound(sound);
//                    return setActorFrameNo(actor1,local_c);
//                case ACTOR_TYPE_2_DOG:
//                case 0xc:
//                case 0x11:
//                    if (bVar5) {
//                        actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
//                    }
//                    if (actor2->spriteIdx2 == 0x52) {
//                        addStylePoints(-16);
//                        return setActorFrameNo(actor1,local_c);
//                    }
//                    break;
//
//                case 0xb:
//                    if (local_c == 0) {
//                        local_c = 0xd;
//                        actor1->inAirCounter = 1;
//                        if (actor1->verticalVelocityMaybe > 4) {
//                            actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
//                            return setActorFrameNo(actor1,0xd);
//                        }
//                    }
//                    break;
//
//                    //here
//
//                case 0xe:
//                    if (0 < sVar1) {
//                        if (sVar9 < sVar1) {
//                            if (actor2->spriteIdx2 == 0x56) {
//                                if ((actor2->flags & FLAG_1) != 0) {
//                                    actor2 = duplicateAndLinkActor(actor2);
//                                }
//                                actorSetFlag8IfFlag1IsUnset(actor2);
//                                addStylePoints(100);
//                                return setActorFrameNo(actor1,local_c);
//                            }
//                            break;
//                        }
//                        if (!bVar5) break;
//                        // goto LAB_00403bcc;
//                        actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
//                        addStylePoints(1);
//                        sound = &sound_2;
////                LAB_00403be8:
//                        playSound(sound);
//                        return setActorFrameNo(actor1,local_c);
//                    }
//                case ACTOR_TYPE_1_BEGINNER:
//                case ACTOR_TYPE_3_SNOWBOARDER:
//                case 4:
//                case 9:
//                case 10:
//                case 0xd:
//                    if ((sVar9 < sVar1) || ((short)(actor1->spritePtr->height + sVar1) < actor2->isInAir)) {
//                        if (iVar4 == 9) {
//                            addStylePoints(1000);
//                            actor2->typeMaybe = 0xd;
//                            actorSetSpriteIdx(actor2, 0x32);
//                            return setActorFrameNo(actor1, local_c);
//                        } else {
//                            addStylePoints(6);
//                            return setActorFrameNo(actor1,local_c);
//                        }
//                    }
//                    if (bVar5) {
//                        if (iVar4 == 0xd) {
//                            maxSpriteWidth = max(actor1->spritePtr->width,actor2->spritePtr->width);
//                            if (abs((int)actor1->xPosMaybe - (int)actor2->xPosMaybe) > (int)maxSpriteWidth / 2) {
//                                actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
//                                return setActorFrameNo(actor1,local_c);
//                            }
//                        }
//                        if ((sVar1 == 0) && (actor1->inAirCounter == 0)) {
//                            local_c = 0xb;
//                        }
//                        else {
//                            local_c = 0x11;
//                            if (actor2->spriteIdx2 == 0x32) {
//                                actor2->typeMaybe = 9;
//                                setActorFrameNo(actor2,0x38);
//                                addStylePoints(0x10);
//                                return setActorFrameNo(actor1,0x11);
//                            }
//                        }
//                        if ((actor1->verticalVelocityMaybe < 0) && (actor2->spriteIdx2 == 0x2e)) {
//                            actorSetSpriteIdx(actor2,0x56);
//                            return setActorFrameNo(actor1,local_c);
//                        }
//                        addStylePoints(-0x20);
//                        playSound(&sound_1);
//                        return setActorFrameNo(actor1,local_c);
//                    }
//                    break;
//
//                case 0x10:
//                    if (((bVar5) && ((int)sVar1 < (int)sVar9 / 2)) && (0 < actor1->verticalVelocityMaybe)) {
//                        actor1->inAirCounter = actor1->verticalVelocityMaybe;
////                        goto LAB_00403cb4;
//                        addStylePoints(1);
//                        playSound(&sound_2);
//                        return setActorFrameNo(actor1,0xd);
//                    }
//            }
//            break;
//        case ACTOR_TYPE_1_BEGINNER:
//            if (0x18 < (int)local_c) break;
//            if (iVar4 == 0) {
//                addStylePoints(0x14);
//            }
//            sound = &sound_6;
//            local_c = (0 < actor2->isInAir) + 0x19;
////            goto LAB_00403be8;
//            playSound(sound);
//            return setActorFrameNo(actor1,local_c);
//        case ACTOR_TYPE_2_DOG:
//            if (((int)local_c < 0x1d) &&
//                ((actor2->HorizontalVelMaybe != 0 || (actor2->verticalVelocityMaybe != 0)))) {
//                if (iVar4 == 0) {
//                    addStylePoints(3);
//                }
//                local_c = 0x1d;
//                sound = &sound_3;
////                goto LAB_00403be8;
//                playSound(sound);
//                return setActorFrameNo(actor1,local_c);
//            }
//            break;
//        case ACTOR_TYPE_3_SNOWBOARDER:
//            switch(iVar4) {
//                case ACTOR_TYPE_0_PLAYER:
//                    addStylePoints(0x14);
//                case ACTOR_TYPE_1_BEGINNER:
//                case ACTOR_TYPE_3_SNOWBOARDER:
//                case 0xd:
//                case 0xe:
//                    if ((sVar1 < sVar9) && (local_c != 0x22)) {
//                        return setActorFrameNo(actor1,0x22);
//                    }
//                    break;
//                case 0xf:
//                case 0x10:
//                    if (sVar1 < sVar9) {
//                        actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
//                        playSound(&sound_5);
//                        return setActorFrameNo(actor1,0x21);
//                    }
//            }
//            break;
//        case 4:
//        case 9:
//            break;
//        default:
//            assertFailed(sourceFilename,2376);
//    }
//    return setActorFrameNo(actor1,local_c);
//}


