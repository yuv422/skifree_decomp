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



#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//



void __fastcall handleKeydownMessage(UINT charCode)

{
    short sVar1;
    int iVar2;
    UINT uVar3;
    UINT ActorframeNo;

    switch(charCode) {
        case VK_RETURN:
            if (playerActor != (Actor *)0x0) {
                return;
            }
        case VK_F2:
            handleGameReset();
            return;
        case VK_ESCAPE:
            ShowWindow(hSkiMainWnd,6);
            return;
        case VK_F3:
            togglePausedState();
            return;
    }
    if (playerActor == (Actor *)0x0) {
        return;
    }
    ActorframeNo = playerActor->frameNo;
    sVar1 = playerActor->isInAir;
    if ((ActorframeNo == 0xb) || (ActorframeNo == 0x11)) goto switchD_004061ec_caseD_29;
    switch(charCode) {
        case 0x21:
        case 0x69:
            /* numpad 9
               Up right */
            if (sVar1 == 0) {
                ActorframeNo = 6;
            }
            break;
        case 0x22:
        case 99:
            /* numpad 3
               down right */
            if (sVar1 == 0) {
                ActorframeNo = 4;
            }
            break;
        case 0x23:
        case 0x61:
            /* numpad 1
               down left */
            if (sVar1 == 0) {
                ActorframeNo = 1;
            }
            break;
        case 0x24:
        case 0x67:
            /* numpad 7
               up left */
            if (sVar1 == 0) {
                ActorframeNo = 3;
            }
            break;
        case 0x25:
        case 100:
            /* numpad 4
               left */
            if (0x15 < ActorframeNo) {
                assertFailed(sourceFilename,0xf63);
            }
            ActorframeNo = playerTurnFrameNoTbl[ActorframeNo].leftFrameNo;
            if (ActorframeNo == 7) {
                iVar2 = playerActor->HorizontalVelMaybe + -8;
                if (iVar2 < -7) {
                    iVar2 = -8;
                }
                playerActor->HorizontalVelMaybe = (short)iVar2;
            }
            break;
        case 0x26:
        case 0x68:
            /* numpad 8 Up */
            switch(ActorframeNo) {
                case 3:
                case 7:
                case 0xc:
                    if (playerActor->verticalVelocityMaybe == 0) {
                        ActorframeNo = 9;
                        playerActor->verticalVelocityMaybe = -4;
                    }
                    break;
                case 6:
                case 8:
                    if (playerActor->verticalVelocityMaybe == 0) {
                        ActorframeNo = 10;
                        playerActor->verticalVelocityMaybe = -4;
                    }
                    break;
                case 0xd:
                switchD_0040628c_caseD_13:
                    ActorframeNo = 0x12;
                    break;
                case 0xe:
                    ActorframeNo = 0x14;
                    break;
                case 0xf:
                    ActorframeNo = 0x15;
                    break;
                case 0x12:
                switchD_0040628c_caseD_d:
                    ActorframeNo = 0x13;
                    break;
                case 0x13:
                switchD_0040628c_caseD_12:
                    ActorframeNo = 0xd;
            }
            break;
        case 0x27:
        case 0x66:
            /* numpad 6, Right */
            if (0x15 < ActorframeNo) {
                assertFailed(sourceFilename,3947);
            }
            ActorframeNo = playerTurnFrameNoTbl[ActorframeNo].rightFrameNo;
            if (ActorframeNo == 8) {
                uVar3 = (int)playerActor->HorizontalVelMaybe + 8;
                if (7 < (int)uVar3) {
                    uVar3 = ActorframeNo;
                }
                playerActor->HorizontalVelMaybe = (short)uVar3;
            }
            break;
        case 0x28:
        case 0x62:
            /* down key pressed */
            if (sVar1 == 0) {
                ActorframeNo = 0;
                break;
            }
            switch(ActorframeNo) {
                case 0xd:
                    goto switchD_0040628c_caseD_d;
                case 0x12:
                    goto switchD_0040628c_caseD_12;
                case 0x13:
                    goto switchD_0040628c_caseD_13;
                case 0x14:
                    ActorframeNo = 0xe;
                    break;
                case 0x15:
                    ActorframeNo = 0xf;
            }
            break;
        case 0x2d:
        case 0x60:
            /* numpad 0, Insert
               Jump. */
            if (sVar1 == 0) {
                playerActor->inAirCounter = 2;
                ActorframeNo = 0xd;
                if (4 < playerActor->verticalVelocityMaybe) {
                    playerActor->verticalVelocityMaybe = playerActor->verticalVelocityMaybe + -4;
                }
            }
    }
    switchD_004061ec_caseD_29:
    if ((ActorframeNo != playerActor->frameNo) &&
        (setActorFrameNo(playerActor,ActorframeNo), redrawRequired != 0)) {
        drawWindow(mainWindowDC,&windowClientRect);
        redrawRequired = 0;
    }
    return;
}










