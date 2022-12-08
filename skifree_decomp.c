// ski32_decomp.cpp : Defines the entry point for the application.
//


#include "skifree_decomp.h"

#include "types.h"


int __fastcall initWindows(HINSTANCE param_1, HINSTANCE param_2, int param_3);
void __fastcall assertFailed(const char *srcFilename, int lineNumber);
int __fastcall showErrorMessage(LPCSTR text);
BOOL allocateMemory();
BOOL loadSoundFunc();
BOOL __fastcall loadSound(UINT resourceId, Sound *sound);
void __fastcall statusWindowFindLongestTextString(HDC hdc, short *maxLength, LPCSTR textStr, int textLength);
void __fastcall paintStatusWindow(HWND hWnd);
BOOL __fastcall calculateStatusWindowDimensions(HWND hWnd);
void __fastcall statusWindowReleaseDC(HWND hWnd);
LRESULT CALLBACK skiMainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK skiStatusWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void __fastcall paintActors(HDC hdc, RECT *paintRect);
void pauseGame();
void togglePausedState();
void __fastcall freeSoundResource(Sound *sound);
void cleanupSound();
void __fastcall playSound(Sound *sound);
Actor * __fastcall addActor(Actor *actor, BOOL insertBack);
HBITMAP __fastcall loadBitmapResource(UINT resourceId);
BOOL __fastcall loadBitmaps(HWND hWnd);
void __fastcall handleWindowMoveMessage(HWND hWnd);
void updateWindowsActiveStatus();
void __fastcall setPointerToNull(PermObjectList *param_1);
Actor *getFreeActor();
BOOL setupGame();
short __fastcall random(short maxValue);
Actor *__fastcall updateActorPositionWithVelocityMaybe(Actor *actor);
Actor *__fastcall addActorOfTypeWithSpriteIdx(int actorType,USHORT spriteIdx);
void __fastcall actorSetFlag8IfFlag1IsUnset(Actor *actor);
void removeFlag8ActorsFromList();
BOOL __fastcall changeScratchBitmapSize(short newWidth, short newHeight);
void __fastcall actorClearFlag10(Actor *actor1, Actor *actor2);
Actor * __fastcall setActorFrameNo(Actor *actor, UINT frameNo);
Actor * __fastcall actorSetSpriteIdx(Actor *actor, USHORT spriteIdx);
Actor * __fastcall duplicateAndLinkActor(Actor *actor);
void __fastcall updateActorRectsAfterPlayerMove(short newPlayerX, short newPlayerY);
void __fastcall getRandomOffscreenStartingPosition(int borderType, short *xPos, short *yPos);
int randomActorType1();
int randomActorType2();
int randomActorType3();
int areaBasedActorType();
Actor * __fastcall updateActorType1_Beginner(Actor *actor);
Actor *__fastcall updateActorType2_dog(Actor *actor);
Actor *__fastcall updateActorType9_treeOnFire(Actor *actor);
Actor * __fastcall updateActor(Actor *actor);
Actor * __fastcall updatePlayerActor(Actor *actor);
void __fastcall updateSsGameMode(Actor *actor, short xPos, short yPos);
int __fastcall FUN_00402e30(int param_1,int param_2,int param_3,int param_4,int param_5);
void resetPlayerFrameNo();
void __fastcall updateFsGameMode(Actor *actor, short xPos, short yPos);
void __fastcall updateGsGameMode(Actor *actor, short xPos, short yPos);
Actor * __fastcall updateActorTypeA_walkingTree(Actor *actor);
Actor * __fastcall updateActorType3_snowboarder(Actor *actor);
Actor * __fastcall handleActorCollision(Actor *actor1,Actor *actor2);
Actor * __fastcall addActorForPermObject(PermObject *permObject);
void __fastcall updatePermObjectActorType4(PermObject *permObject);
void __fastcall updateYeti(PermObject *permObject);
void __fastcall FUN_004046e0(PermObjectList *permObjList);
void deleteWindowObjects();
void handleMouseClick();
int __fastcall getSkierGroundSpriteFromMousePosition(short param_1,short param_2);
int __fastcall getSkierInAirSpriteFromMousePosition(short param_1,short param_2);
void __fastcall handleMouseMoveMessage(short xPos, short yPos);
void __fastcall updateActorsAfterWindowResize(short centreX, short centreY);
void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5);
void __fastcall formatAndPrintStatusStrings(HDC windowDC);
int resetGame();
void __fastcall updatePermObject(PermObject *permObject);
Actor * __fastcall updateActorPositionMaybe(Actor *actor, short newX, short newY, short inAir);
void __fastcall updateWindowSize(HWND hWnd);
Actor * __fastcall updateActorVelMaybe(Actor *actor, const ActorVelStruct *param_2);
PermObject * __fastcall addPermObject(PermObjectList *objList, PermObject *permObject);
void setupPermObjects();
void __fastcall handleKeydownMessage(UINT charCode);
void updateGameState();
BOOL __fastcall createBitmapSheets(HDC param_1);
void __fastcall drawWindow(HDC hdc, RECT *rect);
void __fastcall drawActor(HDC hdc, Actor *actor);
void __fastcall updateEntPackIniKeyValue(LPCSTR configKey, int value, int isTime);
void __fastcall permObjectSetSpriteIdx(PermObject *permObject, USHORT spriteIdx);

#include "data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) ) // TODO remove need for src param.

void timerUpdateFunc() {
    DWORD ticks;

    ticks = GetTickCount();
    timerFrameDurationInMillis = ticks - currentTickCount;
    prevTickCount = currentTickCount;
    currentTickCount = ticks;
    updateGameState();
    drawWindow(mainWindowDC,&windowClientRect);
    redrawRequired = TRUE;
    if ((int)(currentTickCount - statusWindowLastUpdateTime) > 0x147) {
        formatAndPrintStatusStrings(statusWindowDC);
        return;
    }
}

void __fastcall assertFailedDialog(LPCSTR lpCaption, LPCSTR lpText) {
    int iVar1;

    iVar1 = MessageBoxA((HWND)0x0,lpText,lpCaption,0x31);
    if (iVar1 == IDCANCEL) {
        DestroyWindow(hSkiMainWnd);
    }
}

void __fastcall assertFailed(const char *srcFilename, int lineNumber) {
    CHAR local_20 [32];

    wsprintfA(local_20, s_assertErrorFormat, srcFilename, lineNumber);
    assertFailedDialog(s_Assertion_Failed_0040c0a8,local_20);
    togglePausedState();
}

BOOL __fastcall doRectsOverlap(RECT *rect1, RECT *rect2) {
    ski_assert(rect1 != NULL, 352);
    ski_assert(rect2 != NULL, 353);

    if ((((rect2->left < rect1->right) && (rect1->left < rect2->right)) &&
         (rect2->top < rect1->bottom)) && (rect1->top < rect2->bottom)) {
        return TRUE;
    }
    return FALSE;
}

BOOL __fastcall areRectanglesEqual(RECT *rect1,RECT *rect2) {
    ski_assert(rect1 != NULL, 381);
    ski_assert(rect2 != NULL, 382);

    if ((((rect1->top == rect2->top) && (rect1->left == rect2->left)) &&
         (rect1->right == rect2->right)) && (rect1->bottom == rect2->bottom)) {
        return TRUE;
    }
    return FALSE;
}

char * __fastcall getCachedString(UINT stringIdx) {
    int length;
    char *pcVar1;
    CHAR buf [256];

    if (stringCache[stringIdx] == NULL) {
        length = LoadStringA(skiFreeHInstance,stringIdx,buf,0xff);
        buf[length] = '\0';
        pcVar1 = (char *)LocalAlloc(0,length + 1);
        stringCache[stringIdx] = pcVar1;
        if (stringCache[stringIdx] == NULL) {
            return s_out_o_memory;
        }
        lstrcpyA(stringCache[stringIdx],buf);
    }
    return stringCache[stringIdx];
}

int __fastcall formatElapsedTime(int totalMillis, LPSTR outputString) {
    int iVar1;
    char *pcVar2;
    UINT uVar3;
    UINT uVar4;
    UINT uVar5;
    UINT uVar6;

    uVar6 = (totalMillis % 1000 & 0xffffU) / 10;
    uVar5 = (totalMillis / 1000) % 60 & 0xffff;
    iVar1 = (totalMillis / 1000) / 60;
    uVar3 = iVar1 % 60 & 0xffff;
    uVar4 = iVar1 / 60 & 0xffff;
    pcVar2 = getCachedString(IDS_TIME_FORMAT);
    return wsprintfA(outputString,pcVar2,uVar4,uVar3,uVar5,uVar6);
}

void __fastcall drawText(HDC hdc, LPCSTR textStr, short x, short *y, int textLen) {
    TextOutA(hdc,(int)x,(int)*y,textStr,textLen);
    *y = *y + textLineHeight;
}

void CALLBACK timerCallbackFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    if (inputEnabled != 0) {
        timerUpdateFunc();
    }
    // TODO check. The original seems to return 1 here.
}

// TODO check this for byte accuracy.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int iVar1;
    BOOL retVal;
    MSG msg;

    iVar1 = lstrcmpiA(lpCmdLine,s_nosound_0040c0fc);
    if (iVar1 == 0) {
        isSoundDisabled = 1;
    }
    retVal = allocateMemory();
    if (retVal == 0) {
        return 0;
    }
    retVal = resetGame();
    if (retVal == 0) {
        return 0;
    }
    retVal = initWindows(hInstance,hPrevInstance,nCmdShow);
    if (retVal == 0) {
        return 0;
    }
    iVar1 = setupGame();
    if (iVar1 == 0) {
        DestroyWindow(hSkiMainWnd);
        cleanupSound();
        return 0;
    }
    iVar1 = GetMessageA(&msg,NULL,0,0);
    while (iVar1 != 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
        iVar1 = GetMessageA(&msg,NULL,0,0);
    }
    cleanupSound();
    return msg.wParam;
}

// TODO not byte accurate.
BOOL allocateMemory() {
    int i;

    stringCache = LocalAlloc(LMEM_FIXED,NUM_STRINGS * sizeof(char **));
    sprites = LocalAlloc(LMEM_FIXED,NUM_SPRITES * sizeof(Sprite));
    actors = LocalAlloc(LMEM_FIXED,NUM_ACTORS * sizeof(Actor));
    permObjects = LocalAlloc(LMEM_FIXED,   NUM_PERM_OBJECTS * sizeof(PermObject));

    if (stringCache && actors && sprites && permObjects) {
        for (i = 0; i < NUM_STRINGS; i++) {
            stringCache[i] = NULL;
        }
        return TRUE;
    }

    showErrorMessage(s_insufficient_local_memory);
    return FALSE;
}

// TODO not byte perfect
Actor * __fastcall updateActorType1_Beginner(Actor *actor) {
    int uVar1;
    Actor *pAVar2;
    UINT ActorframeNo;

    ActorframeNo = actor->frameNo;
    if (actor == NULL) {
        assertFailed(sourceFilename,2130);
    }
    if (actor->typeMaybe != 1) {
        assertFailed(sourceFilename,2131);
    }
    if (ActorframeNo < 25) {
        pAVar2 = updateActorPositionWithVelocityMaybe(actor);
        if (ActorframeNo - 22 >= 5) {
            assertFailed(sourceFilename, 2135);
        }
        pAVar2 = updateActorVelMaybe(pAVar2, &beginnerActorMovementTbl[ActorframeNo - 22]);
        if (random(0xc) == 0) {
            uVar1 = random(3);
            if (uVar1 == 0) {
                ActorframeNo = 0x16;
            } else if (uVar1 == 1) {
                return setActorFrameNo(pAVar2, 0x17);
            } else if (uVar1 == 2) {
                return setActorFrameNo(pAVar2, 0x18);
            }
        }
        return setActorFrameNo(pAVar2, ActorframeNo);
    }
    return actor;
}

//TODO not byte perfect
Actor *__fastcall updateActorType2_dog(Actor *actor) {
    short sVar1;
    short uVar2;
    Actor *pAVar3;
    short newY;
    UINT ActorframeNo;
    short inAir;

    ActorframeNo = actor->frameNo;
    if (actor->typeMaybe != 2) {
        assertFailed(sourceFilename,2162);
    }
    switch(ActorframeNo) {
        case 0x1b:
            uVar2 = random(3);
            actor->verticalVelocityMaybe = uVar2 - 1;
            pAVar3 = updateActorPositionWithVelocityMaybe(actor);
            return setActorFrameNo(pAVar3,0x1c);
        case 0x1c:
            actor->HorizontalVelMaybe = 4;
            pAVar3 = updateActorPositionWithVelocityMaybe(actor);
            return setActorFrameNo(pAVar3,0x1b);
        case 0x1d:
            actor->verticalVelocityMaybe = 0;
            actor->HorizontalVelMaybe = 0;
            uVar2 = random(0x20);
            pAVar3 = updateActorPositionWithVelocityMaybe(actor);
            return setActorFrameNo(pAVar3, uVar2 != 0 ? 0x1b + 3 : 0x1b);
        case 0x1e:
            uVar2 = random(100);
            if (uVar2 != 0) {
                pAVar3 = updateActorPositionWithVelocityMaybe(actor);
                return setActorFrameNo(pAVar3,0x1d);
            }
            inAir = actor->isInAir;
            sVar1 = actor->xPosMaybe;
            newY = actor->yPosMaybe + -2;
            /* dog wee */
            pAVar3 = addActorOfTypeWithSpriteIdx(ACTOR_TYPE_17_SIGN,0x52);
            updateActorPositionMaybe(pAVar3,(short)(sVar1 - 4),newY,inAir);
            ActorframeNo = 0x1b;
            playSound(&sound_8);
    }
    pAVar3 = updateActorPositionWithVelocityMaybe(actor);
    return setActorFrameNo(pAVar3,ActorframeNo);
}

Actor *__fastcall updateActorType9_treeOnFire(Actor *actor) {
    int frameNo = actor->frameNo;
    ski_assert(actor->typeMaybe == 9, 2204);
    ski_assert(frameNo >= 0x38, 2205);
    ski_assert(frameNo < 0x3c, 2206);

    frameNo++;
    if (frameNo >= 0x3c) {
        frameNo = 0x38;
    }
    return setActorFrameNo(actor, frameNo);
}

Actor * __fastcall getLinkedActorIfExists(Actor *actor) {
    Actor *pAVar1;
    ski_assert(actor, 965);
    pAVar1 = actor->linkedActor;
    if (actor->linkedActor == NULL) {
        pAVar1 = actor;
    }
    return pAVar1;
}

int __fastcall showErrorMessage(LPCSTR text) {
    return MessageBoxA(NULL, text, getCachedString(IDS_TITLE), 0x30);
}

Actor * __fastcall addActorOfTypeWithSpriteIdx(int actorType, USHORT spriteIdx) {
    Actor *actor;

    actor = getFreeActor();
    if (actor != NULL) {
        ski_assert(actorType >= 0, 1403);
        ski_assert(actorType < 0x12, 1404);

        actor->typeMaybe = actorType;
        actor = actorSetSpriteIdx(actor, spriteIdx);
        return actor;
    }
    return actor;
}


void setupGameTitleActors() {
    Actor *actor;
    short x;
    short y;

    y = playerY;
    x = -(sprites[0x35].width / 2) - 40;

    actor = addActorOfTypeWithSpriteIdx(ACTOR_TYPE_17_SIGN, 0x35);
    updateActorPositionMaybe(actor, x, y, 0);

    y = y + sprites[0x36].height + 4;
    actor = addActorOfTypeWithSpriteIdx(ACTOR_TYPE_17_SIGN, 0x36);
    updateActorPositionMaybe(actor, x, y, 0);
    x = sprites[0x37].width;
    if (sprites[0x37].width <= sprites[0x38].width) {
        x = sprites[0x38].width;
    }
    y = sprites[0x37].height;
    actor = addActorOfTypeWithSpriteIdx(ACTOR_TYPE_17_SIGN, 0x37);
    updateActorPositionMaybe(actor, x, y, 0);

    y = y + sprites[0x38].height + 4;
    actor = addActorOfTypeWithSpriteIdx(ACTOR_TYPE_17_SIGN, 0x38);
    updateActorPositionMaybe(actor, x, y, 0);
}



/* WARNING: Removing unreachable block (ram,0x004053c9) */

BOOL __fastcall initWindows(HINSTANCE hInstance,HINSTANCE hPrevInstance,int nCmdShow) {
    ATOM AVar1;
    short windowWidth;
    HDC hdc;
    UINT uVar2;
    BOOL BVar3;
    int nHeight;
    int X;
    char *lpWindowName;
    int nWidth;
    DWORD dwStyle;
    int Y;
    HWND hWndParent;
    HINSTANCE hInstance_00;
    LPVOID lpParam;
    WNDCLASSA wndClass;

    hdc = GetDC(NULL);
    if (hdc == NULL) {
        return 0;
    }
    uVar2 = GetDeviceCaps(hdc,HORZRES);
    SCREEN_WIDTH = SCREEN_WIDTH & 0xffff0000U | uVar2 & 0xffff;
    uVar2 = GetDeviceCaps(hdc,VERTRES);
    SCREEN_HEIGHT = SCREEN_HEIGHT & 0xffff0000U | uVar2 & 0xffff;
    ReleaseDC((HWND)0x0,hdc);
    skiFreeHInstance = hInstance;
    whiteBrush = (HBRUSH)GetStockObject(0);
    hSkiMainWnd = (HWND)0x0;
    hSkiStatusWnd = (HWND)0x0;
    isPaused = 0;
    isMinimised = 1;
    mainWndActivationFlags = 0;
    inputEnabled = 0;
    skierScreenXOffset = 0;
    skierScreenYOffset = 0;
    hSkiMainWnd = FindWindowA("SkiMain",(LPCSTR)0x0);
    if (hSkiMainWnd != (HWND)0x0) {
        SetWindowPos(hSkiMainWnd,(HWND)0x0,0,0,0,0,3);
        BVar3 = IsIconic(hSkiMainWnd);
        if (BVar3 != 0) {
            OpenIcon(hSkiMainWnd);
        }
        hSkiMainWnd = (HWND)0x0;
        return 0;
    }
    timerCallbackFuncPtr = timerCallbackFunc;
    if ((isSoundDisabled == 0) && (BVar3 = loadSoundFunc(), BVar3 != 0)) {
        loadSound(1,&sound_1);
        loadSound(2,&sound_2);
        loadSound(3,&sound_3);
        loadSound(4,&sound_4);
        loadSound(5,&sound_5);
        loadSound(6,&sound_6);
        loadSound(9,&sound_9);
        loadSound(7,&sound_7);
        loadSound(8,&sound_8);
    }
    if (hPrevInstance == (HINSTANCE)0x0) {
        wndClass.style = 0x2023;
        wndClass.lpfnWndProc = skiMainWndProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = hInstance;
        wndClass.hIcon = LoadIconA(hInstance,"iconSki");
        wndClass.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        wndClass.hbrBackground = whiteBrush;
        wndClass.lpszMenuName = (LPCSTR)0x0;
        wndClass.lpszClassName = "SkiMain";
        AVar1 = RegisterClassA(&wndClass);
        if (AVar1 == 0) {
            return 0;
        }
        wndClass.lpfnWndProc = skiStatusWndProc;
        wndClass.hIcon = (HICON)0x0;
        wndClass.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        wndClass.lpszClassName = "SkiStatus";
        wndClass.hbrBackground = whiteBrush;
        AVar1 = RegisterClassA(&wndClass);
        if (AVar1 == 0) {
            return 0;
        }
    }
    windowWidth = (short)SCREEN_WIDTH;
    if ((short)SCREEN_HEIGHT <= (short)SCREEN_WIDTH) {
        windowWidth = (short)SCREEN_HEIGHT;
    }
    nWidth = (int)windowWidth;
    lpParam = (LPVOID)0x0;
    nHeight = (int)(short)SCREEN_HEIGHT;
    hWndParent = (HWND)0x0;
    Y = 0;
    X = ((short)SCREEN_WIDTH - nWidth) / 2;
    dwStyle = 0x2cf0000;
    hInstance_00 = hInstance;
    lpWindowName = getCachedString(1);
    hSkiMainWnd = CreateWindowExA(0,"SkiMain",lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,NULL
            ,hInstance_00,lpParam);
    if (hSkiMainWnd != (HWND)0x0) {
        hSkiStatusWnd =
                CreateWindowExA(0,"SkiStatus",statusWindowNameStrPtr,0x40000000,0,0,0,0,hSkiMainWnd,
                                (HMENU)0x0,hInstance,(LPVOID)0x0);
        if (hSkiStatusWnd != (HWND)0x0) {
            ShowWindow(hSkiMainWnd,nCmdShow);
            UpdateWindow(hSkiMainWnd);
            ShowWindow(hSkiStatusWnd,1);
            UpdateWindow(hSkiStatusWnd);
            return 1;
        }
        DestroyWindow(hSkiMainWnd);
        return 0;
    }
    return 0;
}

BOOL loadSoundFunc() {
    sndPlaySoundAFuncPtr = sndPlaySoundA;
    return (sndPlaySoundA != NULL);
}

BOOL __fastcall loadSound(UINT resourceId, Sound *sound) {
    HRSRC hResInfo;
    HGLOBAL pvVar1;
    LPVOID pvVar2;

    hResInfo = FindResourceA(skiFreeHInstance, MAKEINTRESOURCE(resourceId),"WAVE");
    sound->soundResource = hResInfo;
    if (hResInfo != NULL) {
        pvVar1 = LoadResource(skiFreeHInstance,hResInfo);
        sound->soundResource = pvVar1;
    }
    if (sound->soundResource != NULL) {
        pvVar2 = LockResource(sound->soundResource);
        sound->soundData = pvVar2;
        return TRUE;
    }
    sound->soundData = NULL;
    return FALSE;
}

USHORT __fastcall getSpriteIdxForActorType(int actorType) {
    int uVar1;

    switch(actorType) {
        case ACTOR_TYPE_11_MOGULS:
            return 0x1b;
        default:
            assertFailed(sourceFilename,1571);
            return 0;
        case ACTOR_TYPE_13_TREE:
            uVar1 = random(8);
            // TODO bytes here don't match exactly
            if (uVar1) {
                if (uVar1 != 1) {
                    return 0x31;
                }
                return 0x33;
            }
            return 0x32;
        case ACTOR_TYPE_14_ROCK_STUMP:
            return random(4) != 0 ? 0x2d : 0x2e;
        case ACTOR_TYPE_15_BUMP:
            return random(3) != 0 ? 0x2f : 0x30;
        case ACTOR_TYPE_16_JUMP:
            return 0x34;
    }
}

void __fastcall playSound(Sound *sound) {
    if (isSoundDisabled == 0) {
        if ((sound->soundData == NULL) && (sound->soundResource != NULL)) {
            sound->soundData = LockResource(sound->soundResource);
        }
        if ((sound->soundData != NULL) && (sndPlaySoundAFuncPtr != NULL)) {
            (*sndPlaySoundAFuncPtr)(sound->soundData, SND_ASYNC | SND_MEMORY);
        }
    }
}
// TODO problems in byte matching due to deadcode removal.
Actor * __fastcall updateActorPositionWithVelocityMaybe(Actor *actor) {
    short newX;
    short newY;
    short inAir;

    newX = actor->xPosMaybe + actor->HorizontalVelMaybe;
    newY = actor->yPosMaybe + actor->verticalVelocityMaybe;
    inAir = actor->isInAir + actor->inAirCounter;

    ski_assert(actor, 1061);

    if (isTurboMode != 0) {
        newX = newX + actor->HorizontalVelMaybe;
        newY = newY + actor->verticalVelocityMaybe;
        inAir = inAir + actor->inAirCounter;
    }
    if (inAir > 0) {
        actor->inAirCounter--;
        return updateActorPositionMaybe(actor,newX,newY,inAir);
    }
    actor->inAirCounter = 0;
    return updateActorPositionMaybe(actor,newX,newY,0);
}



void startGameTimer() {
    if (hSkiMainWnd && !isGameTimerRunning && !isPaused) {
        isGameTimerRunning = TRUE;
        currentTickCount = GetTickCount();
        if ((isSsGameMode != 0) || (isGsGameMode != 0)) {
            timedGameRelated = timedGameRelated + (currentTickCount - pauseStartTickCount);
        }
        SetTimer(hSkiMainWnd,0x29a,updateTimerDurationMillis & 0xffff,timerCallbackFuncPtr);
    }
}

void cleanupSound() {
    if (isSoundDisabled == 0) {
        if (sndPlaySoundAFuncPtr != NULL) {
            (*sndPlaySoundAFuncPtr)(0,0);
        }
        if (DAT_0040c78c != NULL) {
            FreeLibrary(DAT_0040c78c);
        }
        freeSoundResource(&sound_1);
        freeSoundResource(&sound_2);
        freeSoundResource(&sound_3);
        freeSoundResource(&sound_4);
        freeSoundResource(&sound_5);
        freeSoundResource(&sound_6);
        freeSoundResource(&sound_9);
        freeSoundResource(&sound_7);
        freeSoundResource(&sound_8);
    }
}

void __fastcall freeSoundResource(Sound *sound) {
    if (sound->soundData != NULL) {
        sound->soundData = NULL;
    }
    if (sound->soundResource != NULL) {
        FreeResource(sound->soundResource);
        sound->soundResource = NULL;
    }
}

void togglePausedState() {
    char *str;

    isPaused = isGameTimerRunning;
    if (isGameTimerRunning != 0) {
        pauseGame();
        str = getCachedString(IDS_PAUSED);
        SetWindowTextA(hSkiMainWnd,str);
        InvalidateRect(hSkiMainWnd,NULL,0);
        return;
    }
    str = getCachedString(IDS_TITLE);
    SetWindowTextA(hSkiMainWnd,str);
    startGameTimer();
}

void pauseGame() {
    if (hSkiMainWnd != NULL && isGameTimerRunning) {
        isGameTimerRunning = FALSE;
        KillTimer(hSkiMainWnd,0x29a);
        pauseStartTickCount = currentTickCount;
    }
}

void __fastcall enlargeRect(RECT *rect1, RECT *rect2) {
    ski_assert(rect2, 365);
    ski_assert(rect1, 366);

    if (rect2->left < rect1->left) {
        rect1->left = rect2->left;
    }
    if (rect2->right > rect1->right) {
        rect1->right = rect2->right;
    }
    if (rect2->top < rect1->top) {
        rect1->top = rect2->top;
    }
    if (rect2->bottom > rect1->bottom) {
        rect1->bottom = rect2->bottom;
    }
}

short __fastcall random(short maxValue) {
    return (short)rand() % maxValue;
}

Actor * __fastcall addActor(Actor *actor, BOOL insertBack) {
    Actor *targetActor;

    targetActor = currentFreeActor;
    ski_assert(actor, 840);

    if (targetActor) {
        currentFreeActor = targetActor->next;

        memcpy(targetActor, actor, sizeof(Actor));

        targetActor->permObject = NULL;
        if (insertBack) {
            targetActor->next = actor->next;
            actor->next = targetActor;
        } else {
            targetActor->next = actorListPtr;
            actorListPtr = targetActor;
        }
        return targetActor;
    } else {
        assertFailed(sourceFilename,857);
    }

    return targetActor; // TODO fixme the original does `MOV EAX, EBX` but we seem to be doing `XOR EAX, EAX`
}

void __fastcall addStylePoints(int points) {
    if (isFsGameMode != 0) {
        stylePoints = stylePoints + points;
    }
}

Actor * getFreeActor() {
    Actor *actor;

    blankTemplateActor.spritePtr = sprites;
    actor = addActor(&blankTemplateActor,0);
    return actor;
}

Actor * __fastcall addActorOfType(int actorType, UINT frameNo) {
    Actor *actor;

    actor = getFreeActor();
    if (actor != NULL) {
        ski_assert(actorType >= 0, 1388);
        ski_assert(actorType < 0x12, 1389);

        actor->typeMaybe = actorType;
        actor = setActorFrameNo(actor, frameNo);
    }
    return actor;
}

void handleGameReset() {
    if (resetGame()) {
        if (isPaused != 0) {
            togglePausedState();
        }
        InvalidateRect(hSkiMainWnd,NULL,TRUE);
        if (setupGame()) {
            UpdateWindow(hSkiMainWnd);
            return;
        }
    }
    DestroyWindow(hSkiMainWnd);
}

void __fastcall handleCharMessage(UINT charCode) {
    switch(charCode) {
        case 'X':
            /* 'X' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,(short)(playerActor->xPosMaybe - 2),playerActor->yPosMaybe,playerActor->isInAir);
                return;
            }
            break;
        case 'Y':
            /* 'Y' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe,(short)(playerActor->yPosMaybe + -2),playerActor->isInAir);
            }
            break;
        case 'f':
            isTurboMode = (isTurboMode == 0);
            /* 'f' key */
            return;
        case 'r':
            /* 'r' */
            drawWindow(mainWindowDC,&windowClientRect);
            return;
        case 't':
            /* 't' */
            timerUpdateFunc();
            return;
        case 'x':
            /* 'x' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,(short)(playerActor->xPosMaybe + 2),playerActor->yPosMaybe,playerActor->isInAir);
                return;
            }
            break;
        case 'y':
            /* 'y' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe,(short)(playerActor->yPosMaybe + 2),playerActor->isInAir);
                return;
            }
    }
    return;
}



void handleWindowSizeMessage(void) {
    int nWidth;

    nWidth = (int)(short)((short)statusWindowTotalTextWidth + 4);
    MoveWindow(hSkiStatusWnd,windowClientRect.right - nWidth,windowClientRect.top,nWidth,
               (int)(short)(statusWindowHeight + 4),1);
}

RECT * __fastcall updateActorSpriteRect(Actor *actor) {
    ski_assert(actor, 931);
    ski_assert((actor->flags & FLAG_4) == 0, 932);
    ski_assert(actor->spriteIdx2 != 0, 933);

    if (&sprites[actor->spriteIdx2] != actor->spritePtr) {
        assertFailed(sourceFilename,934);
    }
    updateRectForSpriteAtLocation(&actor->someRect,actor->spritePtr,actor->xPosMaybe,actor->yPosMaybe,actor->isInAir);
    actor->flags |= FLAG_4;
    return &actor->someRect;
}

void __fastcall mainWindowPaint(HWND param_1) {
    PAINTSTRUCT paint;

    BeginPaint(param_1,&paint);
    FillRect(paint.hdc,&paint.rcPaint,whiteBrush);
    paintActors(paint.hdc,&paint.rcPaint);
    EndPaint(param_1,&paint);
}

void __fastcall paintActors(HDC hdc, RECT *paintRect) {
    Actor *actor;
    RECT *rect;

    ski_assert(hdc != NULL, 1347);
    ski_assert(paintRect != NULL, 1348);

    for (actor = actorListPtr; actor != NULL; actor = actor->next) {
        if ((actor->flags & 4) == 0) {
            rect = updateActorSpriteRect(actor);
        }
        else {
            rect = &actor->someRect;
        }
        if (doRectsOverlap(rect, paintRect)) {
            actor->flags = actor->flags & 0xfffffffe;
        }
    }
    drawWindow(hdc,paintRect);
}

void __fastcall statusWindowFindLongestTextString(HDC hdc, short *maxLength, LPCSTR textStr, int textLength) {
    SIZE size;
    GetTextExtentPoint32A(hdc,textStr,textLength,&size);
    if (*maxLength < size.cx) {
        *maxLength = (short)size.cx;
    }
}

LRESULT CALLBACK skiStatusWndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
    switch(msg) {
        case WM_CREATE:
            if (calculateStatusWindowDimensions(hWnd) == 0) {
                return -1;
            }
            GetClientRect(hWnd,(LPRECT)&statusBorderRect);
            break;
        case WM_DESTROY:
            statusWindowReleaseDC(hWnd);
            return 0;
        case WM_SIZE:
            GetClientRect(hWnd,(LPRECT)&statusBorderRect);
            break;
        case WM_PAINT:
            paintStatusWindow(hWnd);
            return 0;
        default:
            break;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

void __fastcall paintStatusWindow(HWND hWnd) {
    HBRUSH hbr;
    char *str;
    int len;
    int *piVar1;
    int y;
    PAINTSTRUCT paint;

    y = 2;
    BeginPaint(hWnd,&paint);
    hbr = (HBRUSH)GetStockObject(4);
    FrameRect(paint.hdc, &statusBorderRect, hbr);
    str = getCachedString(IDS_TIME);
    len = lstrlenA(str);
    piVar1 = &y;

    str = getCachedString(IDS_TIME);
    drawText(paint.hdc,str,2,(short *)piVar1,len);
    str = getCachedString(IDS_DIST);
    len = lstrlenA(str);
    piVar1 = &y;

    str = getCachedString(IDS_DIST);
    drawText(paint.hdc,str,2,(short *)piVar1,len);
    str = getCachedString(IDS_SPEED);
    len = lstrlenA(str);
    piVar1 = &y;

    str = getCachedString(IDS_SPEED);
    drawText(paint.hdc,str,2,(short *)piVar1,len);
    str = getCachedString(IDS_STYLE);
    len = lstrlenA(str);
    piVar1 = &y;

    str = getCachedString(IDS_STYLE);
    drawText(paint.hdc,str,2,(short *)piVar1,len);
    formatAndPrintStatusStrings(paint.hdc);
    EndPaint(hWnd,&paint);
}

BOOL __fastcall calculateStatusWindowDimensions(HWND hWnd) {
    char *str;
    int len;
    short maxKeyLength;
    short maxValueLength;
    TEXTMETRIC textMetric;

    maxKeyLength = 0;
    maxValueLength = 0;
    statusWindowDC = GetDC(hWnd);
    if (statusWindowDC == NULL) {
        return 0;
    }
    statusWindowFont = GetStockObject(OEM_FIXED_FONT);
    if (statusWindowFont != NULL) {
        statusWindowFont = SelectObject(statusWindowDC,statusWindowFont);
    }
    GetTextMetricsA(statusWindowDC,&textMetric);
    textLineHeight = (short)textMetric.tmHeight;
    str = getCachedString(IDS_TIME);
    len = lstrlenA(str);
    str = getCachedString(IDS_TIME);
    statusWindowFindLongestTextString(statusWindowDC,&maxKeyLength,str,len);
    str = getCachedString(IDS_DIST);
    len = lstrlenA(str);
    str = getCachedString(IDS_DIST);
    statusWindowFindLongestTextString(statusWindowDC,&maxKeyLength,str,len);
    str = getCachedString(IDS_SPEED);
    len = lstrlenA(str);
    str = getCachedString(IDS_SPEED);
    statusWindowFindLongestTextString(statusWindowDC,&maxKeyLength,str,len);
    str = getCachedString(IDS_STYLE);
    len = lstrlenA(str);
    str = getCachedString(IDS_STYLE);
    statusWindowFindLongestTextString(statusWindowDC,&maxKeyLength,str,len);
    str = getCachedString(IDS_TIME_BLANK);
    len = lstrlenA(str);
    str = getCachedString(IDS_TIME_BLANK);
    statusWindowFindLongestTextString(statusWindowDC,&maxValueLength,str,len);
    str = getCachedString(IDS_DIST_BLANK);
    len = lstrlenA(str);
    str = getCachedString(IDS_DIST_BLANK);
    statusWindowFindLongestTextString(statusWindowDC,&maxValueLength,str,len);
    str = getCachedString(IDS_SPEED_BLANK);
    len = lstrlenA(str);
    str = getCachedString(IDS_SPEED_BLANK);
    statusWindowFindLongestTextString(statusWindowDC,&maxValueLength,str,len);
    str = getCachedString(IDS_STYLE_BLANK);
    len = lstrlenA(str);
    str = getCachedString(IDS_STYLE_BLANK);
    statusWindowFindLongestTextString(statusWindowDC,&maxValueLength,str,len);
    statusWindowHeight = (short)(textLineHeight * 4); //TODO is this correct?
//    _textLineHeight = _textLineHeight & 0xffff | (uint)(ushort)((short)_textLineHeight * 4) << 0x10;
    statusWindowTotalTextWidth = (short)maxValueLength + (short)maxKeyLength;
    statusWindowLabelWidth = (short)maxKeyLength;
    return 1;
}

void setupActorList() {
    UINT uVar1;
    UINT uVar2;
    UINT uVar3;

    uVar3 = 0;
    actorListPtr = NULL;
    currentFreeActor = actors;
    uVar2 = 1;
    uVar1 = 0;
    do {
        uVar3 = uVar3 + 1;
        actors[uVar1].next = actors + uVar2;
        uVar1 = uVar3 & 0xffff;
        uVar2 = uVar1 + 1;
    } while (uVar2 < NUM_ACTORS);
    actors[uVar3].next = (Actor *)0x0;
}

void resetPermObjectCount() {
    permObjectCount = 0;
}

BOOL setupGame() {
    Actor *actor;
    short newY;
    short inAir;

    inAir = 0;
    newY = 0;
    actor = addActorOfType(ACTOR_TYPE_0_PLAYER,3);
    playerActorPtrMaybe_1 = updateActorPositionMaybe(actor,0,newY,inAir);
    playerActor = playerActorPtrMaybe_1;
    if (!playerActorPtrMaybe_1) {
        return FALSE;
    }
    setupGameTitleActors();
    setupPermObjects();
    isPaused = FALSE;
    startGameTimer();
    return TRUE;
}

void __fastcall setPointerToNull(PermObjectList *param_1) {
    ski_assert(param_1, 2578);
    param_1->startingObject = NULL;
}

LRESULT CALLBACK skiMainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    BOOL BVar1;
    LRESULT LVar2;

    if (message < 0x25) {
        switch(message) {
            case 1:
                /* WM_CREATE */
                BVar1 = loadBitmaps(hWnd);
                if (BVar1 != 0) {
                    updateWindowSize(hWnd);
                    return 0;
                }
                return -1;
            case 2:
                /* WM_MOVE */
                handleWindowMoveMessage(hWnd);
                PostQuitMessage(0);
                return 0;
            case 3:
            case 4:
            case 7:
            case 8:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
            case 0x1e:
            case 0x1f:
            case 0x20:
                LVar2 = DefWindowProcA(hWnd,message,wParam,lParam);
                return LVar2;
            case 5:
                /* WM_SIZE */
                updateWindowSize(hWnd);
                if (hSkiStatusWnd != 0) {
                    handleWindowSizeMessage();
                }
                isMinimised = (BOOL)(wParam == 1);
                updateWindowsActiveStatus();
                if (inputEnabled != 0) {
                    UpdateWindow(hSkiMainWnd);
                    return 0;
                }
                break;
            case 6:
                /* WM_ACTIVATE */
                mainWndActivationFlags = wParam;
                if (wParam != 0) {
                    SetFocus(hWnd);
                }
                updateWindowsActiveStatus();
                return 0;
            case 0xf:
                /* WM_PAINT */
                mainWindowPaint(hWnd);
                return 0;
            case 0x21:
                /* WM_MOUSEACTIVATE */
                if ((short)lParam == 1) {
                    return 2;
                }
                break;
            default:
                // TODO what is this doing?!
                *(int *)(lParam + 0x18) = 0x140;
                *(int *)(lParam + 0x1c) = 300;
                return 0;
        }
    }
    else if (message < WM_MOUSEMOVE + 1) {
        if (message == WM_MOUSEMOVE) {
            if (inputEnabled != 0) {
                handleMouseMoveMessage((short)lParam,(short)((UINT)lParam >> 0x10));
                return 0;
            }
        }
        else if (message == WM_KEYDOWN) {
            if (inputEnabled != 0) {
                handleKeydownMessage(wParam);
                return 0;
            }
        }
        else {
            if (message != WM_CHAR) {
                LVar2 = DefWindowProcA(hWnd,message,wParam,lParam);
                return LVar2;
            }
            /* WM_CHAR */
            if (inputEnabled != 0) {
                handleCharMessage(wParam);
                return 0;
            }
        }
    }
    else {
        if ((message != WM_LBUTTONDOWN) && (message != WM_LBUTTONDBLCLK)) {
            LVar2 = DefWindowProcA(hWnd,message,wParam,lParam);
            return LVar2;
        }
        if (inputEnabled != 0) {
            handleMouseClick();
        }
    }
    return 0;
}


void updateWindowsActiveStatus() {
    if ((mainWndActivationFlags != 0) && (isMinimised == 0)) {
        inputEnabled = 1;
        startGameTimer();
        return;
    }
    inputEnabled = 0;
    pauseGame();
}

BOOL __fastcall loadBitmaps(HWND hWnd) {
    mainWindowDC = GetDC(hWnd);
    if (!mainWindowDC) {
        return FALSE;
    }
    smallBitmapDC = NULL;
    smallBitmapDC_1bpp = NULL;
    largeBitmapDC = NULL;
    largeBitmapDC_1bpp = NULL;
    bitmapSourceDC = NULL;
    smallBitmapSheet = NULL;
    smallBitmapSheet_1bpp = NULL;
    largeBitmapSheet = NULL;
    largeBitmapSheet_1bpp = NULL;
    scratchBitmap = NULL;
    if (!createBitmapSheets(mainWindowDC)) {
        showErrorMessage("Whoa, like, can't load bitmaps!  Yer outa memory, duuude!");
        return FALSE;
    }
    return TRUE;
}

HBITMAP __fastcall loadBitmapResource(UINT resourceId) {
    return LoadBitmapA(skiFreeHInstance,MAKEINTRESOURCE(resourceId));
}

void __fastcall handleWindowMoveMessage(HWND hWnd) {
    ReleaseDC(hWnd,mainWindowDC);
    pauseGame();
    deleteWindowObjects();
}

void __fastcall statusWindowReleaseDC(HWND hWnd) {
    if (hWnd != hSkiStatusWnd) {
        assertFailed(sourceFilename,4387);
    }
    if (statusWindowFont) {
        SelectObject(statusWindowDC,statusWindowFont);
    }
    ReleaseDC(hWnd, statusWindowDC);
}

void __fastcall actorSetFlag8IfFlag1IsUnset(Actor *actor) {
    ski_assert(actor, 865);

    if ((actor->flags & FLAG_1) == 0) {
        if (actor->linkedActor) {
            actor->linkedActor->linkedActor = NULL;
        }
        actor->flags |= FLAG_8;
    }
}

void removeFlag8ActorsFromList() {
    Actor *currentActor;
    Actor *prevActor;

    currentActor = actorListPtr;
    prevActor = (Actor *)&actorListPtr;
    if (actorListPtr) {
        do {
            if ((currentActor->flags & FLAG_8) != 0) {
                if (currentActor->permObject) {
                    ski_assert(currentActor->permObject->actor == currentActor, 886);
                    currentActor->permObject->actor = NULL;
                }
                if (currentActor == playerActor) {
                    playerActor = NULL;
                }
                if (currentActor == playerActorPtrMaybe_1) {
                    playerActorPtrMaybe_1 = NULL;
                }
                prevActor->next = currentActor->next;
                currentActor->next = currentFreeActor;
                currentFreeActor = currentActor;
            } else {
                prevActor = currentActor;
            }
            currentActor = prevActor->next;
        } while (currentActor != NULL);
    }
}

BOOL __fastcall changeScratchBitmapSize(short newWidth, short newHeight) {
    HGDIOBJ ho;
    HBITMAP h;

    if (((short)newWidth > (short)scratchBitmapWidth) ||
        ((short)newHeight) > (short)scratchBitmapHeight) {
        scratchBitmapWidth = (newWidth & 0xffc0) + 0x40;
        scratchBitmapHeight = (newHeight & 0xffc0) + 0x40;
        if (scratchBitmap != (HGDIOBJ)0x0) {
            ho = SelectObject(bitmapSourceDC,scratchBitmap);
            DeleteObject(ho);
            scratchBitmap = (HGDIOBJ)0x0;
        }
        h = CreateCompatibleBitmap(mainWindowDC, scratchBitmapWidth, scratchBitmapHeight);
        while (h == (HBITMAP)0x0) {
            if (scratchBitmapWidth == newWidth && scratchBitmapHeight == newHeight) {
                scratchBitmapWidth = 0;
                scratchBitmapHeight = 0;
                return FALSE;
            }
            scratchBitmapWidth = newWidth;
            scratchBitmapHeight = newHeight;
            h = CreateCompatibleBitmap(mainWindowDC, newWidth, newHeight);
        }
        scratchBitmap = SelectObject(bitmapSourceDC, h);
    }
    return TRUE;
}

void __fastcall actorClearFlag10(Actor *actor1, Actor *actor2) {
    Actor *pAVar1;
    Actor *pAVar2 = actor1;
    Actor **ppAVar3;

    ski_assert(actor1, 1252);
    ski_assert(actor2, 1253);
    ski_assert((actor1->flags & FLAG_10), 1254); // <---
    ski_assert((actor2->flags & FLAG_10), 1255);
    ski_assert(actor1 != actor2, 1256);

    ppAVar3 = &actor1->actorPtr;
    pAVar1 = actor1->actorPtr;

    while (pAVar1 != (Actor *)0x0) {
        pAVar2 = *ppAVar3;
        if ((pAVar2->flags & FLAG_10) != 0) {
            assertFailed(sourceFilename,1260);
        }
        ppAVar3 = &pAVar2->actorPtr;
        pAVar1 = pAVar2->actorPtr;
    }
    pAVar2->actorPtr = actor2;

    enlargeRect(&actor1->rect,&actor2->rect);
    /* clear FLAG_10 */
    actor2->flags &= 0xffffffef;
}

Actor * __fastcall setActorFrameNo(Actor *actor, UINT ActorframeNo) {
    Actor *pAVar1;

    ski_assert(actor, 1084);
    ski_assert((int)ActorframeNo < 64, 1085);

    if (actor->frameNo != ActorframeNo) {
        ski_assert(ActorframeNo < 64, 1088);

        pAVar1 = actorSetSpriteIdx(actor,actorFrameToSpriteTbl[ActorframeNo]);
        pAVar1->frameNo = ActorframeNo;
        return pAVar1;
    }
    return actor;
}

BOOL __fastcall isSlowTile(short spriteIdx) {
    if ((spriteIdx != 27) && (spriteIdx != 82)) {
        return FALSE;
    }
    return TRUE;
}

Actor * __fastcall actorSetSpriteIdx(Actor *actor, USHORT spriteIdx) {
    ski_assert(actor, 979);
    if (spriteIdx != actor->spriteIdx2) {
        totalAreaOfActorSprites = totalAreaOfActorSprites - actor->spritePtr->totalPixels;
        if ((actor->flags & FLAG_1) != 0) {
            actor = duplicateAndLinkActor(actor);
        }
        actor->spriteIdx2 = spriteIdx;
        actor->spritePtr = &sprites[spriteIdx];
        totalAreaOfActorSprites = totalAreaOfActorSprites + actor->spritePtr->totalPixels;
        actor->flags = actor->flags & (int)0xfffffffb;
        actor->flags |= FLAG_20;

        actor->flags = ((isSlowTile(spriteIdx) & 1) << 6) | actor->flags & 0xffffffbf;
    }
    return actor;
}

Actor * __fastcall duplicateAndLinkActor(Actor *actor) {
    Actor *pAVar1;

    ski_assert(actor, 947);
    ski_assert((actor->flags & FLAG_1), 949);

    pAVar1 = addActor(actor,1);
    actor->linkedActor = pAVar1;
    if (pAVar1 != (Actor *)0x0) {
        pAVar1->linkedActor = actor;
        pAVar1->flags |= FLAG_2;
        actor->flags &= 0xfffffffe; // Clear FLAG_1
    }
    return actor;
}

Actor * __fastcall updateActorWithOffscreenStartingPosition(Actor *actor, int borderType) {
    short y;
    short x;

    if (actor) {
        getRandomOffscreenStartingPosition(borderType,&x,&y);
        actor = updateActorPositionMaybe(actor,x,y,0);
    }

    return actor;
}

// TODO this function isn't byte perfect with the original
Actor * __fastcall updateActorPositionMaybe(Actor *actor, short newX, short newY, short inAir) {
    BOOL hasMoved;
    BOOL bVar3;
    BOOL bVar4;
    BOOL isPlayer;
    UINT flags;

    if ((actor->xPosMaybe == newX) && (actor->yPosMaybe == newY)) {
        hasMoved = FALSE;
    }
    else {
        hasMoved = TRUE;
    }
    bVar4 = actor->isInAir != inAir;
    isPlayer = actor == playerActorPtrMaybe_1;
    ski_assert(actor, 1037);

    if (isPlayer && hasMoved) {
        updateActorRectsAfterPlayerMove(newX, newY);
    }

    if ( hasMoved || bVar4) {
        flags = actor->flags;
        if ((flags & FLAG_1) != 0) {
            actor = duplicateAndLinkActor(actor);
        }
        if ((flags & FLAG_4) == 0 || !isPlayer || bVar4) {
            bVar3 = 0;
        } else {
            bVar3 = 1;
        }
        actor->yPosMaybe = newY;
        actor->xPosMaybe = newX;
        actor->isInAir = inAir;
        *(UINT *) &actor->flags = (UINT) (bVar3 | 8) << 2 | *(UINT *) &actor->flags & 0xfffffffb;
    }
    return actor;
}

//TODO not byte accurate
void __fastcall updateActorRectsAfterPlayerMove(short newPlayerX, short newPlayerY) {
    short dx = newPlayerX - playerX;
    short dy = newPlayerY - playerY;
    Actor *actor = actorListPtr;

    for (; actor != NULL; actor = actor->next) {
        if (actor != playerActorPtrMaybe_1 && (actor->flags & FLAG_4) != 0 && (actor->flags & FLAG_2) == 0) {
            if ((actor->flags & FLAG_1) != 0) {
                duplicateAndLinkActor(actor);
            }

            actor->someRect.left -= dx;
            actor->someRect.right -= dx;
            actor->someRect.top -= dy;
            actor->someRect.bottom -= dy;
        }
    }

    playerX = newPlayerX;
    playerY = newPlayerY;
}

void __fastcall getRandomOffscreenStartingPosition(int borderType, short *xPos, short *yPos) {
    short sVar1;

    *xPos = (short)playerX - (short)skierScreenXOffset;
    *yPos = playerY - (short)skierScreenYOffset;
    switch(borderType) {
        case BORDER_LEFT:
        case BORDER_RIGHT:
            if (borderType == BORDER_LEFT) {
                sVar1 = (short)windowClientRect.left + -0x3c;
            }
            else {
                sVar1 = (short)windowClientRect.right + 0x3c;
            }
            *xPos = *xPos + sVar1;
            *yPos = *yPos + (short)windowClientRect.top + random(windowHeight);
            return;
        case BORDER_TOP:
        case BORDER_BOTTOM:
            break;
        default:
            assertFailed(sourceFilename,1454);
            return;
    }
    *xPos = *xPos + random(windowWidth) + (short)windowClientRect.left;
    if (borderType == BORDER_TOP) {
        *yPos = *yPos + (short)windowClientRect.top + -0x3c;
        return;
    }
    *yPos = *yPos + (short)windowClientRect.bottom + 0x3c;
    return;
}

Actor * __fastcall addRandomActor(int borderType) {
    USHORT spriteIdx;
    int actorType;
    Actor *actor = NULL;
    short y;
    short x;

    getRandomOffscreenStartingPosition(borderType,&x,&y);
    if ((((x < -576) || (-320 < x)) || (y < 640)) || (8640 < y)) {
        if (((x < 320) || (512 < x)) || ((y < 640 || (16640 < y)))) {
            if (((x < -160) || (160 < x)) || ((y < 640 || (16640 < y)))) {
                actorType = randomActorType1();
            }
            else {
                actorType = randomActorType2();
            }
        }
        else {
            actorType = randomActorType3();
        }
    }
    else {
        actorType = areaBasedActorType();
    }
    if (actorType != 0x12) {
        if (actorType < 0xb) {
            actor = addActorOfType(actorType,UINT_ARRAY_0040a22c[actorType]);
        }
        else {
            spriteIdx = getSpriteIdxForActorType(actorType);
            actor = addActorOfTypeWithSpriteIdx(actorType,spriteIdx);
        }
        if (actor != (Actor *)0x0) {
            actor = updateActorPositionMaybe(actor,x,y,0);
            return actor;
        }
    }

    return actor;
}

int randomActorType1(void) {
    USHORT uVar1;

    if (totalAreaOfActorSprites > windowWithMarginTotalArea / 32) {
        return 0x12;
    }

    uVar1 = random(1000);
    if (uVar1 < 0x32) {
        return 10;
    }
    if (uVar1 < 500) {
        return ACTOR_TYPE_13_TREE;
    }
    if (uVar1 < 700) {
        return ACTOR_TYPE_15_BUMP;
    }
    if (uVar1 < 0x2ee) {
        return ACTOR_TYPE_11_MOGULS;
    }
    if (uVar1 < 0x3b6) {
        return ACTOR_TYPE_14_ROCK_STUMP;
    }
    if (uVar1 < 0x3ca) {
        return ACTOR_TYPE_16_JUMP;
    }
    return (uVar1 < 0x3de) ? 1 : 2;
}

int areaBasedActorType() {
    return (totalAreaOfActorSprites > windowWithMarginTotalArea / 64) ? ACTOR_TYPE_18_NOTHING : ACTOR_TYPE_11_MOGULS;
}

int randomActorType3() {
    if (totalAreaOfActorSprites > windowWithMarginTotalArea / 16) {
        return ACTOR_TYPE_18_NOTHING;
    }

    return random(0x40) != 0 ? ACTOR_TYPE_13_TREE : ACTOR_TYPE_2_DOG;
}

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
        return ACTOR_TYPE_13_TREE;
    }
    if (uVar1 < 0x32) {
        return ACTOR_TYPE_15_BUMP;
    }
    if (uVar1 < 0x3c) {
        return ACTOR_TYPE_11_MOGULS;
    }
    return uVar1 < 0x50 ? ACTOR_TYPE_14_ROCK_STUMP : ACTOR_TYPE_16_JUMP;
}

Actor * __fastcall updateActor(Actor *actor) {
    ski_assert(actor, 2311);
    ski_assert(actor->typeMaybe < 11 && !actor->permObject, 2312);

    switch(actor->typeMaybe) {
        case ACTOR_TYPE_0_PLAYER:
            return updatePlayerActor(actor);
        case ACTOR_TYPE_3_SNOWBOARDER:
            return updateActorType3_snowboarder(actor);
        case ACTOR_TYPE_2_DOG:
            return updateActorType2_dog(actor);
        case ACTOR_TYPE_1_BEGINNER:
            return updateActorType1_Beginner(actor);
        default:
            assertFailed(sourceFilename,2335);
            return actor;
        case ACTOR_TYPE_9_TREE_ON_FIRE:
            return updateActorType9_treeOnFire(actor);
        case ACTOR_TYPE_10_WALKING_TREE:
            return updateActorTypeA_walkingTree(actor);
    }
}

// TODO not 100% byte accurate. missing assert and some other logic differences
Actor * __fastcall updatePlayerActor(Actor *actor) {
    short sVar1;
    short uVar5;
    Actor *pAVar2;
    Sound *sound;
    int points;
    UINT ActorframeNo;
    short xPos;
    short yPos;

    xPos = actor->xPosMaybe;
    yPos = actor->yPosMaybe;
    ActorframeNo = actor->frameNo;
    ski_assert(actor, 2022);
    ski_assert(actor->typeMaybe == 0, 2023);


    if (ActorframeNo == 0xb) {
        ski_assert(actor->isInAir == 0, 2027);
        ski_assert(actor->inAirCounter == 0, 2028);

        sVar1 = actor->HorizontalVelMaybe;
        if ((sVar1 == 0) && (actor->verticalVelocityMaybe == 0)) {
            ActorframeNo = 0xc;
        }
        if (sVar1 < 0) {
            uVar5 = -1;
        }
        else {
            uVar5 = (short)(sVar1 > 0);
        }
        actor->HorizontalVelMaybe = sVar1 - uVar5;
        sVar1 = actor->verticalVelocityMaybe;
        if (sVar1 < 0) {
            actor->verticalVelocityMaybe = sVar1 + 1;
        }
        else {
            actor->verticalVelocityMaybe = (sVar1 > 0) ? sVar1 - 1 : sVar1;
        }
    }
    else {
        pAVar2 = updateActorPositionWithVelocityMaybe(actor);
        ski_assert(ActorframeNo < 22, 2040);

        actor = updateActorVelMaybe(pAVar2,&ActorVelStruct_ARRAY_0040a308[ActorframeNo]);
        switch(ActorframeNo) {
            case 8:
            case 10:
                ActorframeNo = 6;
                break;
            case 7:
            case 9:
                ActorframeNo = 3;
                break;
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
                if (actor->isInAir == 0) {
                    ski_assert(ActorframeNo - 0xd < 9, 2066);

                    ActorframeNo = UINT_ARRAY_0040a434[ActorframeNo];
                    if (ActorframeNo == 0x11) {
                        addStylePoints(-0x40);
                        sound = &sound_1;
                    }
                    else {
                        sound = &sound_4;
                    }
                    playSound(sound);
                }
        }
    }
    pAVar2 = setActorFrameNo(actor,ActorframeNo);
    switch(ActorframeNo) {
        case 7:
        case 8:
        case 9:
        case 10:
            points = -1;
            break;
        default:
            goto switchD_00402b0b_caseD_b;
        case 0x14:
        case 0x15:
            points = 8;
            break;
        case 0x12:
        case 0x13:
            points = 4;
            break;
        case 0x10:
            points = 2;
            break;
    }
    addStylePoints(points);
    switchD_00402b0b_caseD_b:
    updateSsGameMode(pAVar2,xPos,yPos);
    updateFsGameMode(pAVar2,xPos,yPos);
    updateGsGameMode(pAVar2,xPos,yPos);
    return pAVar2;
}

// TODO this isn't byte compatible.
void __fastcall updateSsGameMode(Actor *actor,short xPos,short yPos) {
    int iVar1;
    USHORT spriteIdx;
    short x;
    short y;

    if (actor == playerActor) {
        x = actor->xPosMaybe;
        y = actor->yPosMaybe;
        ski_assert(actor->typeMaybe == 0, 1788);
        if (isSsGameMode != 0) {
            elapsedTime = currentTickCount - timedGameRelated;
            if (y > 8640) {
                iVar1 = FUN_00402e30(currentTickCount,prevTickCount,(int)y,(int)yPos,0x21c0);
                isSsGameMode = 0;
                elapsedTime = iVar1 - timedGameRelated;
                INT_0040c964 = 1;
                resetPlayerFrameNo();
                updateEntPackIniKeyValue(iniSsConfigKey,elapsedTime,1); // TODO this is currently a jmp when it should be a call + ret
                return;
            }
            if (y <= 0x280) {
                isSsGameMode = 0;
                return;
            }
            if (y > currentSlalomFlag->maybeY) {
                spriteIdx = 0x19;
                iVar1 = FUN_00402e30((int)x,(int)xPos,(int)y,(int)yPos,(int)currentSlalomFlag->maybeY);
                if (((currentSlalomFlag->spriteIdx == 0x17) && ((short)iVar1 > currentSlalomFlag->maybeX))
                    || ((currentSlalomFlag->spriteIdx == 0x18 && ((short)iVar1 < currentSlalomFlag->maybeX)))
                        ) {
                    spriteIdx = 0x1a;
                    timedGameRelated = timedGameRelated - 5000;
                }
                permObjectSetSpriteIdx(currentSlalomFlag,spriteIdx);
                currentSlalomFlag = currentSlalomFlag + 1;
                return;
            }
        }
        else {
            if ((yPos <= 0x280) && (y > 0x280)) {
                iVar1 = FUN_00402e30((int)x,(int)xPos,(int)y,(int)yPos,0x280);
                if (((short)iVar1 >= -576) && ((short)iVar1 <= -320)) {
                    isSsGameMode = 1;
                    timedGameRelated = FUN_00402e30(currentTickCount,prevTickCount,(int)y,(int)yPos,0x280) ;
                    elapsedTime = timedGameRelated - currentTickCount;
                    currentSlalomFlag = firstSlalomFlagLeft;
                }
            }
        }
    }
}

int __fastcall FUN_00402e30(int param_1,int param_2,int param_3,int param_4,int param_5) {
    ski_assert(param_3 != param_4, 1612);
    return param_1 - ((param_1 - param_2) * (param_3 - param_5)) / (param_3 - param_4);
}

void resetPlayerFrameNo() {
    UINT ActorframeNo;

    if (playerActor) {
        ActorframeNo = playerActor->frameNo;
        if ((ActorframeNo != 0xb) && (ActorframeNo != 0x11)) {
            ActorframeNo = (playerActor->isInAir > 0) ? 0xe : 3;
        }
        setActorFrameNo(playerActor,ActorframeNo);
        formatAndPrintStatusStrings(statusWindowDC);
    }
}

// TODO not byte compatible with the original
void __fastcall updateEntPackIniKeyValue(LPCSTR configKey,int value,int isTime) {
    char cVar1;
    int *valuePtr;
    UINT uVar2;
    int iVar3;
    USHORT uVar4 = 0;
    USHORT yourscoreIdx;
    char *pcVar5;
    LPSTR outputString;
    USHORT uVar6;
    char *bufPtr;
    int hiScoreTbl [10];
    char lineBuf [256];

    bufPtr = lineBuf;

    if (isTime != 0) {
        value = -value;
    }
    GetPrivateProfileStringA
            (entpack_ini_section_name_ski,configKey,(LPCSTR)&statusWindowNameStrPtr,lineBuf,0x100,
             s_entpack_ini);
    while ((bufPtr[0] != '\0' && (uVar4 < 10))) {
        cVar1 = *bufPtr;
        while (cVar1 == ' ') {
            pcVar5 = bufPtr + 1;
            bufPtr = bufPtr + 1;
            cVar1 = *pcVar5;
        }
        cVar1 = *bufPtr;
        pcVar5 = bufPtr;
        if (cVar1 != ' ') {
            do {
                if (cVar1 == '\0') break;
                cVar1 = pcVar5[1];
                pcVar5 = pcVar5 + 1;
            } while (cVar1 != ' ');
            if (pcVar5 != bufPtr) {
                if (*pcVar5 != '\0') {
                    *pcVar5 = '\0';
                    pcVar5 = pcVar5 + 1;
                }
                hiScoreTbl[uVar4] = atol(bufPtr);
                uVar4++;
                bufPtr = pcVar5;
            }
        }
//        lineBuf[0] = *bufPtr;
    }
    yourscoreIdx = 0;
    if (uVar4 > 0) {
        do {
            if (value > hiScoreTbl[yourscoreIdx]) break;
            yourscoreIdx = yourscoreIdx + 1;
        } while (yourscoreIdx < uVar4);
        if (yourscoreIdx >= 10) goto LAB_00402fe2;
    }
    if (uVar4 == 10) {
        uVar4 = 9;
    }
    uVar6 = uVar4;
    if (uVar4 > yourscoreIdx) {
        valuePtr = hiScoreTbl + uVar4;
        iVar3 = (UINT)uVar4 - (UINT)yourscoreIdx;
        do {
            uVar6 = uVar6 - 1;
            *valuePtr = valuePtr[-1];
            valuePtr--;
            iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
    }
    uVar4 = uVar4 + 1;
    hiScoreTbl[uVar6] = value;
    LAB_00402fe2:
    bufPtr = lineBuf;
    if (uVar4 > 0) {
        valuePtr = hiScoreTbl;
        uVar2 = (UINT)uVar4;
        do {
            iVar3 = wsprintfA(bufPtr,scoreFormatString,*valuePtr);
            bufPtr = bufPtr + iVar3;
            valuePtr = valuePtr + 1;
            uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
    }
    WritePrivateProfileStringA(entpack_ini_section_name_ski,configKey,lineBuf,s_entpack_ini);
    uVar6 = 0;
    bufPtr = lineBuf;
    if (uVar4 > 0) {
        for(valuePtr = hiScoreTbl; uVar6 < uVar4; uVar6++, valuePtr++) {
            if (uVar6 > 0) {
                *bufPtr = '\n';
                bufPtr++;
            }
            if (isTime != 0) {
                uVar2 = formatElapsedTime(-*valuePtr,bufPtr);
                uVar2 = uVar2 & 0xffff;
            }
            else {
                uVar2 = wsprintfA(bufPtr,stylePointsFormatString,*valuePtr);
            }
            bufPtr = bufPtr + uVar2;
            if (uVar6 == yourscoreIdx) {
                pcVar5 = getCachedString(IDS_THATS_YOU);
                uVar2 = wsprintfA(bufPtr,scoreStringFormatString,pcVar5);
                bufPtr = bufPtr + uVar2;
            }
        }
//        valuePtr = hiScoreTbl;
//        do {
//            if (uVar6 > 0) {
//                *bufPtr = '\n';
//                bufPtr++;
//            }
//            if (isTime != 0) {
//                uVar2 = formatElapsedTime(-*valuePtr,bufPtr);
//                uVar2 = uVar2 & 0xffff;
//            }
//            else {
//                uVar2 = wsprintfA(bufPtr,stylePointsFormatString,*valuePtr);
//            }
//            bufPtr = bufPtr + uVar2;
//            if (uVar6 == yourscoreIdx) {
//                pcVar5 = getCachedString(IDS_THATS_YOU);
//                uVar2 = wsprintfA(bufPtr,scoreStringFormatString,pcVar5);
//                bufPtr = bufPtr + uVar2;
//            }
//            uVar6++;
//            valuePtr++;
//        } while (uVar6 < uVar4);
    }
    if (yourscoreIdx == 10) {
        iVar3 = wsprintfA(bufPtr,newlineString);
        outputString = bufPtr + iVar3;
//        outputString = bufPtr + wsprintfA(bufPtr,newlineString);
        if (isTime != 0) {
            uVar2 = formatElapsedTime(-value,outputString);
            uVar2 = uVar2 & 0xffff;
        }
        else {
            uVar2 = wsprintfA(outputString,stylePointsFormatString,value);
        }
        bufPtr = getCachedString(IDS_TRY_AGAIN);
        wsprintfA(outputString + uVar2,scoreStringFormatString,bufPtr);
    }
    bufPtr = getCachedString(IDS_HIGH_SCORES);
    MessageBoxA(hSkiMainWnd,lineBuf,bufPtr,0);
    return;
}

// TODO not byte compatible. jmp actorSetSpriteIdx rather than call.
void __fastcall permObjectSetSpriteIdx(PermObject *permObject, USHORT spriteIdx) {
    ski_assert(permObject, 1773);

    permObject->spriteIdx = spriteIdx;
    permObject->spritePtr = sprites + spriteIdx;
    if (permObject->actor) {
        actorSetSpriteIdx(permObject->actor,spriteIdx);
    }
}

// TODO not byte compatible. Another jmp instead of call.
void __fastcall updateFsGameMode(Actor *actor, short xPos, short yPos) {
    int iVar1;
    short x;
    short y;

    if (actor == playerActor) {
        x = actor->xPosMaybe;
        y = actor->yPosMaybe;
        ski_assert(actor->typeMaybe == 0, 1839);

        if (isFsGameMode != 0) {
            if (0x4100 < y) {
                isFsGameMode = 0;
                INT_0040c968 = 1;
                resetPlayerFrameNo();
                updateEntPackIniKeyValue(iniFsConfigKey,stylePoints,0);
                return;
            }
            if (y <= 0x280) {
                isFsGameMode = 0;
                return;
            }
        }
        else {
            if ((yPos <= 0x280) && (0x280 < y)) {
                iVar1 = FUN_00402e30((int)x, (int)xPos, (int)y, (int)yPos, 0x280);
                if (((short)iVar1 >= -160) && ((short)iVar1 <= 160)) {
                    isFsGameMode = 1;
                }
            }
        }
    }
}

// TODO not byte compatible. Another jmp instead of call.
void __fastcall updateGsGameMode(Actor *actor, short xPos, short yPos) {
    int iVar1;
    USHORT spriteIdx;
    short x;
    short y;

    if (actor == playerActor) {
        x = actor->xPosMaybe;
        y = actor->yPosMaybe;
        ski_assert(actor->typeMaybe == 0, 1870);
        if (isGsGameMode != 0) {
            elapsedTime = currentTickCount - timedGameRelated;
            if (0x4100 < y) {
                iVar1 = FUN_00402e30(currentTickCount, prevTickCount, (int)y, (int)yPos, 0x4100);
                isGsGameMode = 0;
                elapsedTime = iVar1 - timedGameRelated;
                INT_0040c960 = 1;
                resetPlayerFrameNo();
                updateEntPackIniKeyValue(iniGsConfigKey,elapsedTime,1);
                return;
            }
            if (y <= 640) {
                isGsGameMode = 0;
                return;
            }
            /* FIXME this decomp isn't right */
            if (y > currentSlalomFlag->maybeY) {
                spriteIdx = 0x19;
                iVar1 = FUN_00402e30((int)x, (int)xPos, (int)y, (int)yPos, (int)currentSlalomFlag->maybeY)
                        ;
                if (((currentSlalomFlag->spriteIdx == 0x17) && ((short)iVar1 > currentSlalomFlag->maybeX))
                    || ((currentSlalomFlag->spriteIdx == 0x18 && ((short)iVar1 < currentSlalomFlag->maybeX)))
                        ) {
                    spriteIdx = 0x1a;
                    timedGameRelated = timedGameRelated - 5000;
                }
                permObjectSetSpriteIdx(currentSlalomFlag,spriteIdx);
                currentSlalomFlag = currentSlalomFlag + 1;
                return;
            }
        }
        else {
            if ((yPos <= 0x280) && (0x280 < y)) {
                iVar1 = FUN_00402e30((int)x, (int)xPos, (int)y, (int)yPos, 0x280);
                if (((short)iVar1 >= 320) && ((short)iVar1 <= 0x200)) {
                    isGsGameMode = 1;
                    timedGameRelated = FUN_00402e30(currentTickCount, prevTickCount, (int)y, (int)yPos, 0x280);
                    elapsedTime = timedGameRelated - currentTickCount;
                    currentSlalomFlag = FirstSlalomFlagRight;
                }
            }
        }
    }
}

//TODO not byte accurate.
Actor * __fastcall updateActorVelMaybe(Actor *actor, const ActorVelStruct *param_2) {
    short xRelated;
    short sVar1;
    int iVar2;
    short existingHorizontalVel;
    short existingVerticalVel;

    existingHorizontalVel = actor->HorizontalVelMaybe;
    existingVerticalVel = actor->verticalVelocityMaybe;
    ski_assert(actor, 1951);

    if (param_2 == (ActorVelStruct *)0x0) {
        assertFailed(sourceFilename,1952);
    }
    if (actor->frameNo != param_2->frameNo) {
        assertFailed(sourceFilename,1953);
    }
    xRelated = param_2->xRelated;
    if (xRelated == 0) {
        if (existingHorizontalVel < 0) {
            xRelated = -1;
        }
        else {
            xRelated = (short)(0 < existingHorizontalVel);
        }
    }
    existingHorizontalVel = xRelated * existingHorizontalVel;
    if (existingVerticalVel > 0) {
        iVar2 = (int)existingVerticalVel;
    }
    else {
        iVar2 = 0;
    }
    sVar1 = (short)((param_2->unk_6 * iVar2) / 2);
    if (existingHorizontalVel > sVar1) {
        iVar2 = existingHorizontalVel - 2;
        if ((int)sVar1 <= iVar2) {
//            LAB_004034f1:
            sVar1 = (short)iVar2;
        }
    }
    else {
        iVar2 = (int)existingHorizontalVel + (int)param_2->unk_4;
        if (iVar2 <= sVar1) { //goto LAB_004034f1;
            sVar1 = (short)iVar2;
        }
    }
    existingHorizontalVel = param_2->unk_2;
    if (existingHorizontalVel < existingVerticalVel) {
        iVar2 = existingVerticalVel + -2;
        if (existingHorizontalVel <= iVar2) {//goto LAB_0040351c;
            existingHorizontalVel = (short)iVar2;
        }
    }
    else {
        iVar2 = (int)param_2->unk_0 + (int)existingVerticalVel;
        if (iVar2 <= existingHorizontalVel) {//goto LAB_0040351c;
            existingHorizontalVel = (short)iVar2;
        }
    }
//    existingHorizontalVel = (short)iVar2;
//    LAB_0040351c:
    actor->verticalVelocityMaybe = existingHorizontalVel;
    actor->HorizontalVelMaybe = xRelated * sVar1;
    return actor;
}

// TODO not byte accurate
Actor * __fastcall updateActorTypeA_walkingTree(Actor *actor) {
    USHORT uVar2;
    Actor *pAVar3;
    int ActorframeNo;

    ActorframeNo = actor->frameNo;
    ski_assert(actor->typeMaybe == 10, 2217);
    ski_assert(ActorframeNo >= 0x3c, 2218);
    ski_assert(ActorframeNo < 0x40, 2219);

    switch(ActorframeNo) {
        case 0x3c:
            if (actor->HorizontalVelMaybe != 0) {
                assertFailed(sourceFilename,2223);
            }
            uVar2 = random(100);
            if (uVar2 == 0) {
                uVar2 = random(2);
                actor->HorizontalVelMaybe = uVar2 * 2 + -1;
                pAVar3 = updateActorPositionWithVelocityMaybe(actor);
                return setActorFrameNo(pAVar3,0x3d);
            }
            break;
        case 0x3d:
            ski_assert(actor->HorizontalVelMaybe != 0, 2232);
            uVar2 = random(10);
            if (uVar2 != 0) {
                pAVar3 = updateActorPositionWithVelocityMaybe(actor);
                pAVar3 = setActorFrameNo(pAVar3, (actor->HorizontalVelMaybe >= 0) ? 0x3f : 0x3e);
                return pAVar3;
            } else {
                actor->HorizontalVelMaybe = 0;
                pAVar3 = updateActorPositionWithVelocityMaybe(actor);
                pAVar3 = setActorFrameNo(pAVar3,0x3c);
                return pAVar3;
            }
        case 0x3e:
            ski_assert(actor->HorizontalVelMaybe < 0, 2243);
            ActorframeNo = 0x3d;
            break;
        case 0x3f:
            ski_assert(actor->HorizontalVelMaybe > 0, 2248);
            ActorframeNo = 0x3d;
            break;
        default:
            break;
    }

    pAVar3 = updateActorPositionWithVelocityMaybe(actor);
    pAVar3 = setActorFrameNo(pAVar3,ActorframeNo);
    return pAVar3;
}

// TODO not byte accurate
Actor * __fastcall updateActorType3_snowboarder(Actor *actor) {
    UINT ActorframeNo;

    ActorframeNo = actor->frameNo;
    ski_assert(actor->typeMaybe == 3, 2274);

    actor = updateActorPositionWithVelocityMaybe(actor);
    ski_assert(ActorframeNo - 0x1f < 8, 2277);

    actor = updateActorVelMaybe(actor,&snowboarderActorMovementTbl[ActorframeNo - 0x1f]);
    if (ActorframeNo == 0x1f) {
        if (random(10) == 0) {
            ActorframeNo = 0x20;
        }
    }
    else if (ActorframeNo == 0x20) {
        if (random(10) == 0) {
            return setActorFrameNo(actor,0x1f);
        }
    }
    else if (ActorframeNo == 0x21) {
        if (actor->isInAir == 0) {
            return setActorFrameNo(actor,0x20);
        }
    }
    else {
        ski_assert(((int)ActorframeNo >= 0x22) && ((int)ActorframeNo < 0x27), 2298);

        ActorframeNo++;
        if (ActorframeNo == 0x27) {
            return setActorFrameNo(actor,0x20);
        }
    }
    return setActorFrameNo(actor,ActorframeNo);
}

// TODO not byte accurate
Actor * __fastcall handleActorCollision(Actor *actor1,Actor *actor2) {
    short sVar1;
    short sVar2;
    short sVar3;
    int iVar4;
    BOOL bVar5;
    Actor *pAVar6;
    Sound *sound;
    short sVar9;
    short actor1y;
    short actor2y;
    UINT local_c;
    short maxSpriteWidth;

    ski_assert(actor1, 2350);
    ski_assert(actor2, 2351);

    if (actor1->typeMaybe >= 11) {
        return actor1;
    }
    actor1y = actor1->yPosMaybe;
    actor2y = actor2->yPosMaybe;
    pAVar6 = getLinkedActorIfExists(actor1);
    sVar2 = pAVar6->yPosMaybe;
    pAVar6 = getLinkedActorIfExists(actor2);
    sVar3 = pAVar6->yPosMaybe;
    if ((((actor1y < actor2y) || (sVar2 > sVar3)) && ((actor1y > actor2y  || (sVar2 < sVar3)))) ||
        ((actor1y == actor2y && (sVar2 == sVar3)))) {
        bVar5 = FALSE;
    }
    else {
        bVar5 = TRUE;
    }
    iVar4 = actor2->typeMaybe;
    local_c = actor1->frameNo;
    sVar1 = actor1->isInAir;
    sVar9 = actor2->spritePtr->height + actor2->isInAir;
    switch(actor1->typeMaybe) {
        case ACTOR_TYPE_10_WALKING_TREE:
            actor1->HorizontalVelMaybe = 0;
            return setActorFrameNo(actor1,0x3c);
        case ACTOR_TYPE_5_YETI_TOP:
        case ACTOR_TYPE_6_YETI_BOTTOM:
        case ACTOR_TYPE_7_YETI_LEFT:
        case ACTOR_TYPE_8_YETI_RIGHT:
            if (actor2 == playerActor) {
                ski_assert(iVar4 == 0, 2393);
                playSound(&sound_7);
                if ((actor2->flags & FLAG_1) != 0) {
                    actor2 = duplicateAndLinkActor(actor2);
                }
                actorSetFlag8IfFlag1IsUnset(actor2);
                ski_assert(actor1->permObject, 2396);

                actor1->permObject->actorFrameNo = 0x32;
                actor1->HorizontalVelMaybe = 0;
                actor1->permObject->xVelocity = 0;
                actor1->verticalVelocityMaybe = 0;
                actor1->permObject->yVelocity = 0;
                actor1->permObject->unk_0x20 = currentTickCount;
                return setActorFrameNo(actor1,0x32);
            }
            break;
        case ACTOR_TYPE_0_PLAYER:
            if (local_c == 0x11) break;
            switch(iVar4) {
                case ACTOR_TYPE_15_BUMP:
                    if (sVar1 < 1) {
                        actor1->inAirCounter = 4;
//                        LAB_00403cb4:
                        addStylePoints(1);
                        playSound(&sound_2);
                        return setActorFrameNo(actor1,0xd);
                    }
                    if (sVar9 <= sVar1) break;
//                LAB_00403bcc:
                    actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
                    addStylePoints(1);
                    sound = &sound_2;
//                LAB_00403be8:
                    playSound(sound);
                    return setActorFrameNo(actor1,local_c);
                case ACTOR_TYPE_2_DOG:
                case ACTOR_TYPE_12_SLALOM_FLAG:
                case ACTOR_TYPE_17_SIGN:
                    if (bVar5) {
                        actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
                    }
                    if (actor2->spriteIdx2 == 0x52) {
                        addStylePoints(-16);
                        return setActorFrameNo(actor1,local_c);
                    }
                    break;

                case ACTOR_TYPE_11_MOGULS:
                    if (local_c == 0) {
                        local_c = 0xd;
                        actor1->inAirCounter = 1;
                        if (actor1->verticalVelocityMaybe > 4) {
                            actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
                            return setActorFrameNo(actor1,0xd);
                        }
                    }
                    break;

                    //here

                case ACTOR_TYPE_14_ROCK_STUMP:
                    if (0 < sVar1) {
                        if (sVar9 < sVar1) {
                            if (actor2->spriteIdx2 == 0x56) {
                                if ((actor2->flags & FLAG_1) != 0) {
                                    actor2 = duplicateAndLinkActor(actor2);
                                }
                                actorSetFlag8IfFlag1IsUnset(actor2);
                                addStylePoints(100);
                                return setActorFrameNo(actor1,local_c);
                            }
                            break;
                        }
                        if (!bVar5) break;
                        // goto LAB_00403bcc;
                        actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
                        addStylePoints(1);
                        sound = &sound_2;
//                LAB_00403be8:
                        playSound(sound);
                        return setActorFrameNo(actor1,local_c);
                    }
                case ACTOR_TYPE_1_BEGINNER:
                case ACTOR_TYPE_3_SNOWBOARDER:
                case 4:
                case 9:
                case 10:
                case ACTOR_TYPE_13_TREE:
                    if ((sVar9 < sVar1) || ((short)(actor1->spritePtr->height + sVar1) < actor2->isInAir)) {
                        if (iVar4 == 9) {
                            addStylePoints(1000);
                            actor2->typeMaybe = ACTOR_TYPE_13_TREE;
                            actorSetSpriteIdx(actor2, 0x32);
                            return setActorFrameNo(actor1, local_c);
                        } else {
                            addStylePoints(6);
                            return setActorFrameNo(actor1,local_c);
                        }
                    }
                    if (bVar5) {
                        if (iVar4 == ACTOR_TYPE_13_TREE) {
                            maxSpriteWidth = max(actor1->spritePtr->width,actor2->spritePtr->width);
                            if (abs((int)actor1->xPosMaybe - (int)actor2->xPosMaybe) > (int)maxSpriteWidth / 2) {
                                actor1->verticalVelocityMaybe = actor1->verticalVelocityMaybe / 2;
                                return setActorFrameNo(actor1,local_c);
                            }
                        }
                        if ((sVar1 == 0) && (actor1->inAirCounter == 0)) {
                            local_c = 0xb;
                        }
                        else {
                            local_c = 0x11;
                            if (actor2->spriteIdx2 == 0x32) {
                                actor2->typeMaybe = 9;
                                setActorFrameNo(actor2,0x38);
                                addStylePoints(0x10);
                                return setActorFrameNo(actor1,0x11);
                            }
                        }
                        if ((actor1->verticalVelocityMaybe < 0) && (actor2->spriteIdx2 == 0x2e)) {
                            actorSetSpriteIdx(actor2,0x56);
                            return setActorFrameNo(actor1,local_c);
                        }
                        addStylePoints(-0x20);
                        playSound(&sound_1);
                        return setActorFrameNo(actor1,local_c);
                    }
                    break;

                case ACTOR_TYPE_16_JUMP:
                    if (((bVar5) && ((int)sVar1 < (int)sVar9 / 2)) && (0 < actor1->verticalVelocityMaybe)) {
                        actor1->inAirCounter = actor1->verticalVelocityMaybe;
//                        goto LAB_00403cb4;
                        addStylePoints(1);
                        playSound(&sound_2);
                        return setActorFrameNo(actor1,0xd);
                    }
            }
            break;
        case ACTOR_TYPE_1_BEGINNER:
            if (0x18 < (int)local_c) break;
            if (iVar4 == 0) {
                addStylePoints(0x14);
            }
            sound = &sound_6;
            local_c = (0 < actor2->isInAir) + 0x19;
//            goto LAB_00403be8;
            playSound(sound);
            return setActorFrameNo(actor1,local_c);
        case ACTOR_TYPE_2_DOG:
            if (((int)local_c < 0x1d) &&
                ((actor2->HorizontalVelMaybe != 0 || (actor2->verticalVelocityMaybe != 0)))) {
                if (iVar4 == 0) {
                    addStylePoints(3);
                }
                local_c = 0x1d;
                sound = &sound_3;
//                goto LAB_00403be8;
                playSound(sound);
                return setActorFrameNo(actor1,local_c);
            }
            break;
        case ACTOR_TYPE_3_SNOWBOARDER:
            switch(iVar4) {
                case ACTOR_TYPE_0_PLAYER:
                    addStylePoints(0x14);
                case ACTOR_TYPE_1_BEGINNER:
                case ACTOR_TYPE_3_SNOWBOARDER:
                case ACTOR_TYPE_13_TREE:
                case ACTOR_TYPE_14_ROCK_STUMP:
                    if ((sVar1 < sVar9) && (local_c != 0x22)) {
                        return setActorFrameNo(actor1,0x22);
                    }
                    break;
                case ACTOR_TYPE_15_BUMP:
                case ACTOR_TYPE_16_JUMP:
                    if (sVar1 < sVar9) {
                        actor1->inAirCounter = actor1->verticalVelocityMaybe / 2;
                        playSound(&sound_5);
                        return setActorFrameNo(actor1,0x21);
                    }
            }
            break;
        case ACTOR_TYPE_4_CHAIRLIFT:
        case ACTOR_TYPE_9_TREE_ON_FIRE:
            break;
        default:
            assertFailed(sourceFilename,2376);
    }
    return setActorFrameNo(actor1,local_c);
}

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
}

Actor * __fastcall addActorForPermObject(PermObject *permObject) {
    USHORT newX;
    USHORT newY;
    short inAir;
    Actor *actor;
    RECT spriteRect;

    ski_assert(permObject, 2604);
    if (!permObject->actor) {
        newX = permObject->maybeX;
        newY = permObject->maybeY;
        inAir = permObject->unk_0x18;
        updateRectForSpriteAtLocation(&spriteRect,permObject->spritePtr, newX, newY,inAir);
        if (doRectsOverlap(&spriteRect, &windowClientRectWith120Margin)) {
            if (permObject->spriteIdx == 0) {
                actor = addActorOfType(permObject->actorTypeMaybe,permObject->actorFrameNo);
            }
            else {
                actor = addActorOfTypeWithSpriteIdx(permObject->actorTypeMaybe,permObject->spriteIdx);
            }
            if (actor) {
                actor = updateActorPositionMaybe(actor, newX, newY, inAir);
                permObject->actor = actor;
                actor->permObject = permObject;
            }
        }
    }
    return permObject->actor;
}

// TODO not byte accurate
void __fastcall updatePermObject(PermObject *permObject) {
    Actor *pAVar1;
    int actorType;

    if (permObject == (PermObject *)0x0) {
        assertFailed(sourceFilename,2791);
    }
    permObject->maybeX = permObject->maybeX + permObject->xVelocity;
    actorType = permObject->actorTypeMaybe;
    permObject->maybeY = permObject->maybeY + permObject->yVelocity;
    permObject->unk_0x18 = permObject->unk_0x18 + permObject->unk_0x1e;
    if (actorType != ACTOR_TYPE_4_CHAIRLIFT) {
        // TODO this is byte accurate but probably not how it was originally written in C
        if ((actorType <= 4) || (8 < actorType)) {
            assertFailed(sourceFilename,2809);
        } else {
            updateYeti(permObject);
        }
    }
    else {
        updatePermObjectActorType4(permObject);
    }

    pAVar1 = permObject->actor;
    if (pAVar1) {
        ski_assert(pAVar1, 2814); // TODO problems with deadcode removal here.
        ski_assert(pAVar1->permObject, 2815);
        ski_assert(pAVar1->permObject == permObject, 2816);

        pAVar1 = updateActorPositionMaybe
                (pAVar1,permObject->maybeX,permObject->maybeY,permObject->unk_0x18);
        setActorFrameNo(pAVar1,permObject->actorFrameNo);
    }
}

void __fastcall updatePermObjectActorType4(PermObject *permObject) {
    ski_assert(permObject, 2633);
    ski_assert(permObject->actorTypeMaybe == ACTOR_TYPE_4_CHAIRLIFT, 2634);

    if (permObject->maybeY <= -1024) {
        permObject->actorFrameNo = 0x29;
        permObject->yVelocity = 2;
        permObject->maybeX = -144;
        return;
    }
    if (23552 <= permObject->maybeY) {
        permObject->actorFrameNo = 0x27;
        permObject->yVelocity = -2;
        permObject->maybeX = -112;
        return;
    }
    /* snowboarder jump out of chairlift */
    if (permObject->actor && (permObject->actorFrameNo == 0x27)) {
        if (random(1000) == 0) {
            updateActorPositionMaybe(addActorOfType(ACTOR_TYPE_3_SNOWBOARDER,0x21), permObject->maybeX, permObject->maybeY, permObject->unk_0x18);
            permObject->actorFrameNo = 0x28;
        }
    }
}

// TODO not byte accurate
void __fastcall updateYeti(PermObject *permObject) {
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
                    permObject->actorFrameNo = tickRelated < 3000 ? 0x36 : 0x2a; // ((2999 < iVar6) - 1 & 0xc) + 0x2a;
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
        if (iVar6 == ACTOR_TYPE_5_YETI_TOP && permObjY > -2000) {
            sVar9 = -10;
        } else if (iVar6 == ACTOR_TYPE_6_YETI_BOTTOM && permObjY < 32000) {
            sVar9 = 0x1a;
        } else if (iVar6 == ACTOR_TYPE_7_YETI_LEFT && permObjX > -16000) {
            local_c = -0x10;
        } else if (iVar6 == ACTOR_TYPE_8_YETI_RIGHT && permObjX < 16000) {
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

                if ((iVar6 == ACTOR_TYPE_5_YETI_TOP && pY < -2000) ||
                    (iVar6 == ACTOR_TYPE_6_YETI_BOTTOM && pY > 32000) ||
                    (iVar6 == ACTOR_TYPE_7_YETI_LEFT && pX < -16000) ||
                    (iVar6 == ACTOR_TYPE_8_YETI_RIGHT && pX > 16000)
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
}

void __fastcall FUN_004046e0(PermObjectList *permObjList) {
    short top;
    short bottom;
    PermObject *permObject;
    PermObject *pPVar4;

    top = ((short)windowClientRectWith120Margin.top - skierScreenYOffset) + -0x3c;
    bottom = ((short)windowClientRectWith120Margin.bottom - skierScreenYOffset) + 0x3c;
    permObject = permObjList->currentObj;
    ski_assert(permObjList, 2849);
    ski_assert(permObject >= permObjList->startingObject, 2850);
    ski_assert(permObject <= permObjList->nextObject, 2851);

    pPVar4 = permObjList->nextObject;
    for(; permObject < pPVar4; permObject++) {
        if ((int)permObject->maybeY - (int)playerY >= (int)top) break;
    }

    for (; permObject > permObjList->startingObject; permObject--) {
        if ((int)permObject->maybeY - (int)playerY < (int)top) break;
    }

    permObjList->currentObj = permObject;

    for (; permObject < permObjList->nextObject; ) {
        if ((int)permObject->maybeY - (int)playerY >= bottom) {
            break;
        }
        addActorForPermObject(permObject++);
    }
}

// TODO not byte accurate.
BOOL resetGame(void) {
    currentTickCount = GetTickCount();
    srand(currentTickCount);
    setupActorList();
    playerActorPtrMaybe_1 = (Actor *)0x0;
    playerActor = (Actor *)0x0;
    totalAreaOfActorSprites = 0;
    resetPermObjectCount();
    isTurboMode = 0;
    playerY = 0;
    playerX = 0;
    DAT_0040c5d8 = 0;
    DAT_0040c714 = 0;
    stylePoints = 0;
    INT_0040c964 = 0;
    isSsGameMode = 0;
    INT_0040c960 = 0;
    isGsGameMode = 0;
    elapsedTime = 0;
    updateTimerDurationMillis = 40;
    redrawRequired = 1;
    return 1;
}

void deleteWindowObjects(void) {
    if (smallBitmapSheet) {
        DeleteObject(SelectObject(smallBitmapDC,smallBitmapSheet));
    }
    if (largeBitmapSheet) {
        DeleteObject(SelectObject(largeBitmapDC,largeBitmapSheet));
    }
    if (smallBitmapSheet_1bpp) {
        DeleteObject(SelectObject(smallBitmapDC_1bpp,smallBitmapSheet_1bpp));
    }
    if (largeBitmapSheet_1bpp) {
        DeleteObject(SelectObject(largeBitmapDC_1bpp,largeBitmapSheet_1bpp));
    }
    if (scratchBitmap) {
        DeleteObject(SelectObject(bitmapSourceDC,scratchBitmap));
    }
    if (smallBitmapDC) {
        DeleteDC(smallBitmapDC);
    }
    if (largeBitmapDC) {
        DeleteDC(largeBitmapDC);
    }
    if (smallBitmapDC_1bpp) {
        DeleteDC(smallBitmapDC_1bpp);
    }
    if (largeBitmapDC_1bpp) {
        DeleteDC(largeBitmapDC_1bpp);
    }
    if (bitmapSourceDC) {
        DeleteDC(bitmapSourceDC);
    }
}

int __fastcall getSkierGroundSpriteFromMousePosition(short param_1,short param_2) {
    short uVar1;

    if (param_2 > 0) {
        if (param_1 == 0) {
            return 0;
        }
        uVar1 = (((int)param_2 << 2) / (int)param_1);
        if (uVar1 <= -0xc) {
            return 0;
        }
        if (uVar1 <= -6) {
            return 1;
        }
        if (uVar1 <= -3) {
            return 2;
        }
        if (uVar1 <= -1) {
            return 3;
        }
        if (uVar1 >= 0xc) {
            return 0;
        }
        if (uVar1 >= 6) {
            return 4;
        }
        if (uVar1 >= 3) {
            return 5;
        }
        if (uVar1 >= 1) {
            return 6;
        }
    }
    return param_1 < 0 ? 3 : 6;
}

int __fastcall getSkierInAirSpriteFromMousePosition(short param_1,short param_2) {
    if (param_1 < 0) {
        if (param_2 < 0) {
            return (param_2 < param_1) ? 16 : 14;
        }
        return (-param_2 < param_1) ? 13 : 14;
    }
    if (param_2 < 0) {
        return (-param_2 <= param_1) ? 15 : 16;
    }
    return (param_2 <= param_1) + 13;
}

void handleMouseClick() {
    UINT ActorframeNo;

    if (!playerActor) {
        handleGameReset();
        return;
    }
    ActorframeNo = playerActor->frameNo;
    if (ActorframeNo != 11) {
        if (playerActor->isInAir == 0) {
            playerActor->inAirCounter = 4;
            ActorframeNo = 0xd;
        }
        else if (ActorframeNo != 17) {
            switch(ActorframeNo) {
                case 0xd:
                    ActorframeNo = 0x12;
                    break;
                case 0x12:
                    ActorframeNo = 0x13;
                    break;
                case 0x13:
                    ActorframeNo = 0xd;
                    break;
                case 0xe:
                    ActorframeNo = 0x14;
                    break;
                case 0xf:
                    ActorframeNo = 0x15;
                    break;
            }
        }
    }
    if ((ActorframeNo != playerActor->frameNo) &&
        (setActorFrameNo(playerActor,ActorframeNo), redrawRequired != 0)) {
        drawWindow(mainWindowDC,&windowClientRect);
        redrawRequired = FALSE;
    }
}

void __fastcall handleMouseMoveMessage(short xPos,short yPos) {
    int ActorframeNo;
    short mouseSkierXDelta;
    short mouseSkierYDelta;

    if (((DAT_0040c760 != 0) &&
         (((xPos != prevMouseX || (yPos != prevMouseY)) && (playerActor != NULL)))) &&
        ((playerActor->frameNo != 0xb && (playerActor->frameNo != 0x11)))) {
        mouseSkierXDelta = xPos - (short)skierScreenXOffset;
        mouseSkierYDelta = yPos - (short)skierScreenYOffset;
        if (playerActor->isInAir == 0) {
            ActorframeNo = getSkierGroundSpriteFromMousePosition(mouseSkierXDelta,mouseSkierYDelta);
        }
        else {
            ActorframeNo = getSkierInAirSpriteFromMousePosition(mouseSkierXDelta, mouseSkierYDelta);
        }
        setActorFrameNo(playerActor,ActorframeNo);
    }
    prevMouseX = xPos;
    prevMouseY = yPos;
    DAT_0040c760 = 1;
}

// TODO not byte accurate
void __fastcall updateWindowSize(HWND hWnd) {
    DAT_0040c760 = 0;
    GetClientRect(hWnd,&windowClientRect);
    updateActorsAfterWindowResize(
            (short)((windowClientRect.left + windowClientRect.right) / 2),
            (short)((windowClientRect.top + windowClientRect.bottom) / 3)
    );
    windowClientRectWith120Margin.left = windowClientRect.left - 120;
    windowClientRectWith120Margin.right = windowClientRect.right + 120;
    windowClientRectWith120Margin.bottom = windowClientRect.bottom + 120;
    windowClientRectWith120Margin.top = windowClientRect.top - 120;
    windowWidth = (short)(windowClientRect.right - windowClientRect.left);
    windowHeight = (short)(windowClientRect.bottom - windowClientRect.top);
    windowWithMarginTotalArea =
            (windowClientRectWith120Margin.bottom - windowClientRectWith120Margin.top) *
            (windowClientRectWith120Margin.bottom - windowClientRectWith120Margin.left);
}

// TODO not byte accurate
void __fastcall updateActorsAfterWindowResize(short centreX, short centreY) {
    Actor *actor;

    for(actor = actorListPtr; actor != NULL; actor = actor->next) {
        if (((actor->flags & FLAG_4) != 0) && ((actor->flags & FLAG_2) == 0)) {
            if ((actor->flags & FLAG_1) != 0) {
                duplicateAndLinkActor(actor);
            }
            actor->flags &= 0xfffffffb;
        }
    }

    skierScreenYOffset = centreY;
    skierScreenXOffset = centreX;
}

// TODO not byte accurate
void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5) {
    short spriteHeight;
    short spriteWidth;

    spriteWidth = sprite->width;
    spriteHeight = sprite->height;
    ski_assert(rect, 907);
    ski_assert(sprite, 908);

    rect->top = ((short)(newY + (short)((short)(skierScreenYOffset - playerY) - param_5)) - spriteHeight);
    rect->left = (newX + (short)((skierScreenXOffset - spriteWidth / 2) - playerX));
    rect->bottom = spriteHeight + rect->top;
    rect->right = spriteWidth + rect->left;
}

void __fastcall formatAndPrintStatusStrings(HDC windowDC) {
    short sVar1;
    short speed;
    short x = statusWindowLabelWidth + 2;
    short y = 2;
    CHAR strBuf [20];

    speed = 0;
    sVar1 = 0;

    if (playerActor != NULL) {
        if (timerFrameDurationInMillis != 0) {
            speed = (short)((int)(playerActor->verticalVelocityMaybe * 1000) / (int)(timerFrameDurationInMillis * 16));
        }
        else {
            speed = 0;
        }
        sVar1 = playerActor->yPosMaybe;
        if (isSsGameMode) {
            sVar1 = 8640 - sVar1;
        } else {
            if (isFsGameMode) {
                sVar1 = 16640 - sVar1;

            }
            else {
                if (isGsGameMode) {
                    sVar1 = 16640 - sVar1;
                }
            }
        }
    }
    drawText(windowDC,strBuf,x,&y,formatElapsedTime(elapsedTime,strBuf) & 0xffff);
    drawText(windowDC,strBuf,x,&y,wsprintfA(strBuf,getCachedString(IDS_DIST_FORMAT), (short)(sVar1 / 16)));
    drawText(windowDC,strBuf,x,&y,wsprintfA(strBuf,getCachedString(IDS_SPEED_FORMAT), speed));
    drawText(windowDC,strBuf,x,&y,wsprintfA(strBuf,getCachedString(IDS_STYLE_FORMAT), stylePoints));
    statusWindowLastUpdateTime = currentTickCount;
    return;
}

PermObject * __fastcall addPermObject(PermObjectList *objList, PermObject *permObject) {
    PermObject *pPVar1;

    pPVar1 = &permObjects[permObjectCount++]; // + uVar2;
    ski_assert(objList, 2587);
    ski_assert(permObject, 2588);
    ski_assert(permObjectCount <= NUM_PERM_OBJECTS, 2589);

    if (objList->startingObject == (PermObject *)0x0) {
        objList->currentObj = pPVar1;
        objList->nextObject = pPVar1;
        objList->startingObject = pPVar1;
    }
    ski_assert(objList->nextObject == pPVar1, 2592);
    objList->nextObject = objList->nextObject + 1;
    memcpy(pPVar1, permObject, sizeof(PermObject));
    pPVar1->actor = NULL;
    pPVar1->spritePtr = &sprites[(USHORT)pPVar1->spriteIdx];

    return pPVar1;
}

void setupPermObjects() {
    BOOL bVar1;
    USHORT uVar2;
    PermObject *pPVar3;
    short sVar4;
    PermObject permObject;

    permObject.unk_0x1e = 0;
    permObject.yVelocity = 0;
    permObject.xVelocity = 0;
    permObject.unk_0x18 = 0;
    setPointerToNull(&PermObjectList_0040c630);
    permObject.actorTypeMaybe = ACTOR_TYPE_17_SIGN;
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
    permObject.actorTypeMaybe = ACTOR_TYPE_12_SLALOM_FLAG;
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
    permObject.actorTypeMaybe = ACTOR_TYPE_17_SIGN;
    permObject.spriteIdx = 0x3b;
    permObject.maybeX = -576;
    permObject.maybeY = 8640;
    addPermObject(&PermObjectList_0040c630,&permObject);
    permObject.spriteIdx = 0x3c;
    permObject.maybeX = -320;
    addPermObject(&PermObjectList_0040c630,&permObject);
    setPointerToNull(&PermObjectList_0040c5e0);
    permObject.actorTypeMaybe = ACTOR_TYPE_17_SIGN;
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
        permObject.actorTypeMaybe = ACTOR_TYPE_12_SLALOM_FLAG;
        permObject.spriteIdx = bVar1 ? 0x17 : 0x18;
        permObject.maybeX = bVar1 ? 400 : 432;
        bVar1 = !bVar1;
        permObject.maybeY = sVar4;
        pPVar3 = addPermObject(&PermObjectList_0040c5e0,&permObject);
        if (FirstSlalomFlagRight == (PermObject *)0x0) {
            FirstSlalomFlagRight = pPVar3;
        }
        permObject.actorTypeMaybe = ACTOR_TYPE_13_TREE;
        permObject.spriteIdx = getSpriteIdxForActorType(ACTOR_TYPE_13_TREE);
        uVar2 = random(0x20);
        permObject.maybeX = uVar2 + 400;
        /* this should use the return value */
        random(400);
        sVar4 = sVar4 + 400;
    } while (sVar4 < 0x4100);
    permObject.actorTypeMaybe = ACTOR_TYPE_17_SIGN;
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

    permObject.actorTypeMaybe = ACTOR_TYPE_17_SIGN;
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
        permObject.actorTypeMaybe = ACTOR_TYPE_13_TREE;
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
    permObject.actorTypeMaybe = ACTOR_TYPE_7_YETI_LEFT;
    permObject.actorFrameNo = 0x2a;
    permObject.spriteIdx = 0;
    permObject.maybeX = -16060;
    permObject.unk_0x18 = 0;
    permObject.maybeY = 0;
    permObject.unk_0x1e = 0;
    permObject.yVelocity = 0;
    permObject.xVelocity = 0;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = ACTOR_TYPE_8_YETI_RIGHT;
    permObject.maybeX = 16060;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = ACTOR_TYPE_5_YETI_TOP;
    permObject.maybeX = 0;
    permObject.maybeY = -2060;
    addPermObject(&PermObjectList_0040c720,&permObject);
    permObject.actorTypeMaybe = ACTOR_TYPE_6_YETI_BOTTOM;
    permObject.maybeY = 32060;
    addPermObject(&PermObjectList_0040c720,&permObject);
}

// TODO not byte accurate
void __fastcall handleKeydownMessage(UINT charCode) {
    short sVar1;
    UINT ActorframeNo;

    switch(charCode) {
        case VK_ESCAPE:
            ShowWindow(hSkiMainWnd,6);
            return;
        case VK_F3:
            togglePausedState(); // TODO this is a jmp rather than a call in the original
            return;
        case VK_RETURN:
            if (playerActor != (Actor *)0x0) {
                return;
            }
            handleGameReset(); // TODO this is a jmp rather than a call in the original
            return;
        case VK_F2:
            handleGameReset(); // TODO this is a jmp rather than a call in the original
            return;
        default: break;
    }

    if (playerActor == (Actor *)0x0) {
        return;
    }
    ActorframeNo = playerActor->frameNo;
    sVar1 = playerActor->isInAir;
    if ((ActorframeNo != 0xb) && (ActorframeNo != 0x11)) {
        switch (charCode) {
            case 0x25:
            case 100:
                /* numpad 4
                   left */
                ski_assert(ActorframeNo < 0x16, 0xf63);

                ActorframeNo = playerTurnFrameNoTbl[ActorframeNo].leftFrameNo;
                if (ActorframeNo == 7) {
//                    iVar2 = (int)playerActor->HorizontalVelMaybe - 8;
//                    if (iVar2 <= -8) {
//                        iVar2 = -8;
//                    }
//                    playerActor->HorizontalVelMaybe = (short) iVar2;
                    playerActor->HorizontalVelMaybe = max(playerActor->HorizontalVelMaybe - 8, -8);
                }
                break;
            case 0x27:
            case 0x66:
                /* numpad 6, Right */
                ski_assert(ActorframeNo < 0x16, 3947);

                ActorframeNo = playerTurnFrameNoTbl[ActorframeNo].rightFrameNo;
                if (ActorframeNo == 8) {
//                    iVar2 = (int) playerActor->HorizontalVelMaybe + 8;
//                    if (iVar2 >= 8) {
//                        iVar2 = 8;
//                    }
//                    playerActor->HorizontalVelMaybe = (short) iVar2;

                    playerActor->HorizontalVelMaybe = min(playerActor->HorizontalVelMaybe + 8, 8);
                }
                break;

            case 0x28:
            case 0x62:
                /* down key pressed */
                if (sVar1 == 0) {
                    ActorframeNo = 0;
                    break;
                }
                switch (ActorframeNo) {
                    case 0xd:
                        ActorframeNo = 0x13;
                        break;
                    case 0x14:
                        ActorframeNo = 0xe;
                        break;
                    case 0x15:
                        ActorframeNo = 0xf;
                        break;
                    case 0x12:
                        ActorframeNo = 0xd;
                        break;
                    case 0x13:
                        ActorframeNo = 0x12;
                        break;
                }
                break;

            case 0x26:
            case 0x68:
                /* numpad 8 Up */
                switch (ActorframeNo) {
                    case 0xd:
//                switchD_0040628c_caseD_13:
                        ActorframeNo = 0x12;
                        break;
                    case 0x13:
//                switchD_0040628c_caseD_12:
                        ActorframeNo = 0xd;
                        break;
                    case 0xe:
                        ActorframeNo = 0x14;
                        break;
                    case 0xf:
                        ActorframeNo = 0x15;
                        break;
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
                    case 0x12:
//                switchD_0040628c_caseD_d:
                        ActorframeNo = 0x13;
                        break;

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

            case 0x21:
            case 0x69:
                /* numpad 9
                   Up right */
                if (sVar1 == 0) {
                    ActorframeNo = 6;
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

            case 0x22:
            case 99:
                /* numpad 3
                   down right */
                if (sVar1 == 0) {
                    ActorframeNo = 4;
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
    }

    if ((ActorframeNo != playerActor->frameNo) &&
        (setActorFrameNo(playerActor,ActorframeNo), redrawRequired != 0)) {
        drawWindow(mainWindowDC,&windowClientRect);
        redrawRequired = 0;
    }
}

void updateGameState() {
    int iVar1;
    Actor *actor;
    RECT *ptVar6;
    RECT *rect2;
    Actor *pAVar7;

    DAT_0040c714 = DAT_0040c714 - (short)playerX;
    DAT_0040c5d8 = DAT_0040c5d8 - playerY;

    for (pAVar7 = actorListPtr; pAVar7 != NULL; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & (FLAG_2 | FLAG_8)) == 0) {
            pAVar7->flags &= 0xffffffdf;
            if ((pAVar7->permObject == NULL) && (pAVar7->typeMaybe < 0xb)) {
                updateActor(pAVar7);
            }
            if (((pAVar7->flags & FLAG_1) == 0) && (pAVar7 != playerActor)) {
                if ((pAVar7->flags & FLAG_4) != 0) {
                    ptVar6 = &pAVar7->someRect;
                }
                else {
                    ptVar6 = updateActorSpriteRect(pAVar7);
                }
                if (doRectsOverlap(ptVar6,&windowClientRectWith120Margin) == FALSE) {
                    totalAreaOfActorSprites = totalAreaOfActorSprites - pAVar7->spritePtr->totalPixels;
                    actorSetFlag8IfFlag1IsUnset(pAVar7);
                }
            }
        }
    }

    FUN_004046e0(&PermObjectList_0040c630);
    FUN_004046e0(&PermObjectList_0040c5e0);
    FUN_004046e0(&PermObjectList_0040c658);
    FUN_004046e0(&PermObjectList_0040c738);
    updateAllPermObjectsInList(&PermObjectList_0040c720);
    removeFlag8ActorsFromList();
    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & FLAG_2) == 0) {
            if ((pAVar7->flags & FLAG_4) != 0) {
                ptVar6 = &pAVar7->someRect;
            }
            else {
                ptVar6 = updateActorSpriteRect(pAVar7);
            }
            // testing FLAG_20
            iVar1 = pAVar7->flags << 26;
            iVar1 = iVar1 >> 31;   //(pAVar7->flags & FLAG_20) ? TRUE : FALSE;
            for (actor = actorListPtr; (actor != NULL && (pAVar7 != actor)); actor = actor->next)
            {
                if (((actor->flags & FLAG_2) == 0) && (iVar1 != 0 || ((actor->flags & FLAG_20) != 0))) {
                    if ((actor->flags & FLAG_4) != 0) {
                        rect2 = &actor->someRect;
                    }
                    else {
                        rect2 = updateActorSpriteRect(actor);
                    }

                    if (doRectsOverlap(ptVar6,rect2)) {
                        handleActorCollision(pAVar7,actor);
                        if ((pAVar7->flags & FLAG_8) == 0 && (actor->flags & FLAG_8) == 0) {
                            handleActorCollision(actor,pAVar7);
                        }
                    }
                }
            }
        }
    }
    DAT_0040c714 = DAT_0040c714 + (short)playerX;
    for (DAT_0040c5d8 = DAT_0040c5d8 + playerY; 0x3c < DAT_0040c5d8;
         DAT_0040c5d8 = DAT_0040c5d8 + -0x3c) {
        addRandomActor(BORDER_BOTTOM);
    }
    for (; DAT_0040c5d8 < -0x3c; DAT_0040c5d8 = DAT_0040c5d8 + 0x3c) {
        addRandomActor(BORDER_TOP);
    }
    for (; 0x3c < DAT_0040c714; DAT_0040c714 = DAT_0040c714 + -0x3c) {
        addRandomActor(BORDER_RIGHT);
    }
    for (; DAT_0040c714 < -0x3c; DAT_0040c714 = DAT_0040c714 + 0x3c) {
        addRandomActor(BORDER_LEFT);
    }

    if (random(0x29a) != 0) {
        return;
    }
    pAVar7 = addActorOfType(ACTOR_TYPE_3_SNOWBOARDER,0x1f);

    /* top of screen */
    updateActorWithOffscreenStartingPosition(pAVar7,2);
}

// TODO not byte accurate register usage is swapped.
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

// TODO not byte accurate
void __fastcall drawWindow(HDC hdc, RECT *windowRect) {
    RECT *rect1;
    RECT *ptVar3;
    UINT uVar4;
    Actor *pAVar6;
    Actor *pAVar7;

    ski_assert(hdc, 1272);
    ski_assert(windowRect, 1273);

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
    for (pAVar7 = actorListPtr; pAVar7 != (Actor *)0x0; pAVar7 = pAVar7->next) {
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
            pAVar7->flags = (pAVar7->flags & 0xffffffef) | ((uVar4 & 1) << 4);
            if ((uVar4 & 1) != 0) {
                (pAVar7->rect).left = ptVar3->left;
                (pAVar7->rect).top = ptVar3->top;
                (pAVar7->rect).right = ptVar3->right;
                (pAVar7->rect).bottom = ptVar3->bottom;
                pAVar7->actorPtr = (Actor *)0x0;
            }
        }
    }

    for (pAVar7 = actorListPtr; pAVar7 != NULL; pAVar7 = pAVar7->next) {
        if ((pAVar7->flags & FLAG_10) != 0) {
            pAVar6 = pAVar7->linkedActor;

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

void __fastcall drawActor(HDC hdc,Actor *actor) {
    Actor **ppAVar1;
    short y;
    RECT *rect;
    USHORT uVar6;
    Actor *pAVar7;
    short sVar8;
    short newWidth;
    USHORT newHeight;
    Actor *actor_00;
    short sVar10;
    Actor **ppAVar11;
    DWORD rop;
    Actor *local_24;
    Actor *local_20;
    int local_1c;
    UINT local_14;
    UINT actorRectLeft;
    short sheetY;
    int local_c;
    UINT local_8;
    Actor **local_4;
    Sprite *sprite;
    short spriteWidth;
    short spriteHeight;

    uVar6 = *(USHORT *)&(actor->rect).left;
    actorRectLeft = (actor->rect).left;

    y = *(short *)&(actor->rect).top;
    newWidth = *(short *)&(actor->rect).right - uVar6;
    newHeight = *(short *)&(actor->rect).bottom - y;

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
            ppAVar1 = &actor->actorPtr;
            if ((actor->flags & FLAG_2) == 0) {
                if ((actor->flags & FLAG_40) == 0) {
                    sVar8 = 0;
                }
                else {
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
                if ((actor->flags & FLAG_1) != 0) {
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

            local_14 = rect->left - actorRectLeft;
            sVar10 = *(short *)&rect->top - y;
            ski_assert(rect->right - rect->left == spriteWidth, 1203);
            ski_assert(rect->bottom - rect->top == spriteHeight, 1204);
            ski_assert(local_14 >= 0, 1205);
            ski_assert(sVar10 >= 0, 1206);
            ski_assert(newWidth >= spriteWidth, 1207);

            if (newHeight < spriteHeight) {
                assertFailed(sourceFilename,1208);
            }
            if (local_1c == 0) {
                local_1c = 1;
                if ((((0 < (short)local_14) || (0 < sVar10)) || (spriteWidth < newWidth)) || (spriteHeight < newHeight))  {
                    PatBlt(bitmapSourceDC,0,0,(int)newWidth,(int)newHeight,0xff0062);
                }
                rop = 0xcc0020;
            }
            else {
                BitBlt(bitmapSourceDC,(int)(short)local_14,(int)sVar10,spriteWidth,spriteHeight,sprite->sheetDC_1bpp,0,(int)sheetY ,
                       0xee0086);
                rop = 0x8800c6;
            }
            BitBlt(bitmapSourceDC,(int)(short)local_14,(int)sVar10,spriteWidth,spriteHeight,sprite->sheetDC,0,(int)sheetY,rop);
            local_24->flags |= FLAG_1;
            *local_4 = local_24->actorPtr;
            actor = local_20;
        }
    } while (actor != (Actor *)0x0);
    if (local_1c != 0) {
        BitBlt(hdc,(int)(short)actorRectLeft,(int)y,(int)newWidth,(int)(short)newHeight,bitmapSourceDC,0
                ,0,0xcc0020);
        return;
    }
    if (local_c != 0) {
        PatBlt(hdc,(int)(short)actorRectLeft,(int)y,(int)newWidth,(int)(short)newHeight,0xff0062);
    }
}