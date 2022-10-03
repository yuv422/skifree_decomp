// ski32_decomp.cpp : Defines the entry point for the application.
//


#include "stdafx.h"

typedef struct {
    HDC hdc1;
    HDC hdc2;
    short sheetYOffset;
    short width;
    short height;
    short totalPixels;
} Sprite;

typedef struct Actor {
    struct Actor *next;
    Sprite *sprite;
    UINT spriteIdx1;
    struct Actor *unkActorPtr;
    UINT spriteIdx2;
    Sprite *spritePtr;
    int typeMaybe;
    UINT unk_0x1c;
    RECT someRect;
    RECT rect;
    short xPosMaybe;
    short yPosMaybe;
    short isInAir;
    short HorizontalVelMaybe;
    short verticalVelocityMaybe;
    short inAirCounter;
    UINT flags;
} Actor;

typedef struct {
    HGLOBAL soundResource;
    LPVOID soundData;
} Sound;

#define NUM_ACTORS 100
#define NUM_SPRITES 90
#define NUM_STRINGS 20

int __fastcall initWindows(HINSTANCE param_1, HINSTANCE param_2, int param_3);
void __fastcall assertFailed(char *srcFilename, int lineNumber);
int __fastcall showErrorMessage(LPCSTR text);
int allocateMemory();
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
Actor * __fastcall addActor(Actor *actor, BOOL insertBack);
HBITMAP __fastcall loadBitmapResource(UINT resourceId);
BOOL __fastcall loadBitmaps(HWND hWnd);
void __fastcall handleWindowMoveMessage(HWND hWnd);
void updateWindowsActiveStatus();
void __fastcall setPointerToNull(void **param_1);




extern char s_assertErrorFormat[];
extern char s_Assertion_Failed_0040c0a8[];
extern char s_insufficient_local_memory[];
extern char s_nosound_0040c0fc[];

//
// ASM Functions
//
extern int setupGame();
extern int resetGame();
extern void updateGameState();
extern void __fastcall drawWindow(HDC hdc, RECT *rect);
extern void __fastcall formatAndPrintStatusStrings(HDC windowDC);
extern void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5);
extern Actor * __fastcall FUN_00402120(Actor *actor, UINT frameNo);
extern void deleteWindowObjects();
extern Actor * __fastcall updateActorPositionMaybe(Actor *actor, short newX, short newY, short inAir);
extern BOOL __fastcall createBitmapSheets(HDC param_1);
extern void __fastcall updateWindowSize(HWND hWnd);
extern void __fastcall handleMouseMoveMessage(short xPos,short yPos);
extern void __fastcall handleKeydownMessage(UINT charCode);
extern void handleMouseClick(void);
extern void setupActorType0x11();
extern void FUN_00404b50();

extern char sourceFilename[];
extern HWND hSkiMainWnd;
extern HWND hSkiStatusWnd;
extern char **stringCache;
extern HINSTANCE skiFreeHInstance;
extern char s_out_o_memory[];
extern Sprite *sprites;
extern Actor *actors;
extern Actor *actorListPtr;
extern Actor *playerActor;
extern Actor *playerActorPtrMaybe_1;
extern void *PTR_0040c758;
extern int isSoundDisabled;
extern USHORT SCREEN_WIDTH;
extern USHORT SCREEN_HEIGHT;
extern HBRUSH whiteBrush;
extern BOOL isPaused;
extern BOOL isMinimised;
extern UINT mainWndActivationFlags;
extern BOOL inputEnabled;
extern int skierScreenXOffset;
extern int skierScreenYOffset;
extern BOOL redrawRequired;
extern DWORD timerFrameDurationInMillis;
extern DWORD currentTickCount;
extern DWORD prevTickCount;
extern DWORD pauseStartTickCount;
extern DWORD statusWindowLastUpdateTime;
extern DWORD timedGameRelated;
extern RECT windowClientRect;
extern RECT statusBorderRect;
extern HDC mainWindowDC;
extern HDC statusWindowDC;
extern Sound sound_1;
extern Sound sound_2;
extern Sound sound_3;
extern Sound sound_4;
extern Sound sound_5;
extern Sound sound_6;
extern Sound sound_7;
extern Sound sound_8;
extern Sound sound_9;
extern LPCSTR statusWindowNameStrPtr;
extern HGDIOBJ statusWindowFont;
extern short textLineHeight;
extern short statusWindowHeight;
extern short statusWindowTotalTextWidth;
extern short statusWindowLabelWidth;
extern BOOL isGameTimerRunning;
extern BOOL isSsGameMode;
extern BOOL isGsGameMode;
extern int updateTimerDurationMillis;
extern void *DAT_0040c78c;
extern Actor blankTemplateActor;
extern Actor *currentFreeActor;
extern BOOL isTurboMode;
extern HDC smallBitmapDC;
extern HDC smallBitmapDC_1bpp;
extern HDC largeBitmapDC;
extern HDC largeBitmapDC_1bpp;
extern HDC bitmapSourceDC;
extern HGDIOBJ smallBitmapSheet;
extern HGDIOBJ smallBitmapSheet_1bpp;
extern HGDIOBJ largeBitmapSheet;
extern HGDIOBJ largeBitmapSheet_1bpp;
extern HGDIOBJ scratchBitmap;


extern BOOL (WINAPI *sndPlaySoundAFuncPtr)(LPCSTR, UINT);
extern void (CALLBACK* timerCallbackFuncPtr)(HWND, UINT, UINT, DWORD);

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
    if (0x147 < (int)(currentTickCount - statusWindowLastUpdateTime)) {
        formatAndPrintStatusStrings(statusWindowDC);
        return;
    }
    redrawRequired = TRUE;
}

void __fastcall assertFailedDialog(LPCSTR lpCaption, LPCSTR lpText) {
    int iVar1;

    iVar1 = MessageBoxA((HWND)0x0,lpText,lpCaption,0x31);
    if (iVar1 == IDCANCEL) {
        DestroyWindow(hSkiMainWnd);
    }
}

void __fastcall assertFailed(char *srcFilename, int lineNumber) {
    CHAR local_20 [32];

    wsprintfA(local_20, s_assertErrorFormat, srcFilename, lineNumber);
    assertFailedDialog(s_Assertion_Failed_0040c0a8,local_20);
    togglePausedState();
}

int __fastcall doRectsOverlap(RECT *rect1, RECT *rect2) {
    ski_assert(rect1 != NULL, 352);
    ski_assert(rect2 != NULL, 353);

    if ((((rect2->left < rect1->right) && (rect1->left < rect2->right)) &&
         (rect2->top < rect1->bottom)) && (rect1->top < rect2->bottom)) {
        return 1;
    }
    return 0;
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

void __fastcall formatElapsedTime(int totalMillis, LPSTR outputString) {
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
    wsprintfA(outputString,pcVar2,uVar4,uVar3,uVar5,uVar6);
}

void __fastcall drawText(HDC hdc, LPCSTR textStr, short x, short *y, int textLen) {
    TextOutA(hdc,(int)x,(int)*y,textStr,textLen);
    *y = *y + textLineHeight;
}

void CALLBACK timerCallbackFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    if (inputEnabled != 0) {
        timerUpdateFunc();
    }
}

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

int allocateMemory() {
    int iVar1;

    stringCache = (char **)LocalAlloc(0,NUM_STRINGS * sizeof(char **));
    sprites = (Sprite *)LocalAlloc(0,NUM_SPRITES * sizeof(Sprite));
    actors = (Actor *)LocalAlloc(0,NUM_ACTORS * sizeof(Actor));
    PTR_0040c758 = LocalAlloc(0,9216);

    if ((((stringCache != NULL) && (actors != NULL)) && (sprites != NULL) ) &&
        (PTR_0040c758 != NULL)) {

        for (iVar1 = 0; iVar1 < NUM_STRINGS; iVar1++) {
            stringCache[iVar1] = NULL;
        }
        return 1;
    }

    showErrorMessage(s_insufficient_local_memory);
    return 0;
}

int __fastcall showErrorMessage(LPCSTR text) {
    char *lpCaption;

    lpCaption = getCachedString(IDS_TITLE);
    return MessageBoxA(NULL, text, lpCaption, 0x30);
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

USHORT __fastcall random(short maxValue) {
    return (USHORT)rand() % maxValue;
}

Actor * __fastcall addActor(Actor *actor, BOOL insertBack) {
    Actor *targetActor;

    targetActor = currentFreeActor;
    if (actor == (Actor *)0x0) {
        assertFailed(sourceFilename,840);
    }
    if (targetActor == (Actor *)0x0) {
        assertFailed(sourceFilename,857);
        return (Actor *)0x0;
    }
    currentFreeActor = targetActor->next;
//    pAVar2 = actor;
//    pAVar3 = targetActor;
//    for (iVar1 = 20; iVar1 != 0; iVar1 = iVar1 + -1) {
//        pAVar3->next = pAVar2->next;
//        pAVar2 = (Actor *)&pAVar2->unk_0x4;
//        pAVar3 = (Actor *)&pAVar3->unk_0x4;
//    }

    memcpy(targetActor, actor, sizeof(Actor));

    targetActor->unkActorPtr = NULL;
    if (insertBack) {
        targetActor->next = actor->next;
        actor->next = targetActor;
    } else {
        targetActor->next = actorListPtr;
        actorListPtr = targetActor;
    }

    return targetActor;
}

Actor * getFreeActor() {
    Actor *actor;

    blankTemplateActor.spritePtr = sprites;
    actor = addActor(&blankTemplateActor,0);
    return actor;
}

Actor * __fastcall addActorOfType(int actorType, UINT param_2) {
    Actor *actor;

    actor = getFreeActor();
    if (actor != NULL) {
        if (actorType < 0) {
            assertFailed(sourceFilename,1388);
        }
        if (0x11 < actorType) {
            assertFailed(sourceFilename,1389);
        }
        actor->typeMaybe = actorType;
        actor = FUN_00402120(actor, param_2);
        return actor;
    }
    return NULL;
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
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe - 2,playerActor->yPosMaybe,playerActor->isInAir);
                return;
            }
            break;
        case 'Y':
            /* 'Y' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe,playerActor->yPosMaybe + -2,playerActor->isInAir);
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
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe + 2,playerActor->yPosMaybe,playerActor->isInAir);
                return;
            }
            break;
        case 'y':
            /* 'y' */
            if (playerActor) {
                updateActorPositionMaybe(playerActor,playerActor->xPosMaybe,playerActor->yPosMaybe + 2,playerActor->isInAir);
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
    if (actor == (Actor *)0x0) {
        assertFailed(sourceFilename,931);
    }
    if ((actor->flags & 4) != 0) {
        assertFailed(sourceFilename,932);
    }
    if (actor->spriteIdx2 == 0) {
        assertFailed(sourceFilename,933);
    }
    if (sprites + actor->spriteIdx2 != actor->spritePtr) {
        assertFailed(sourceFilename,934);
    }
    updateRectForSpriteAtLocation(&actor->someRect,actor->spritePtr,actor->xPosMaybe,actor->yPosMaybe,actor->isInAir);
    actor->flags = actor->flags | 4;
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

BOOL setupGame() {
    Actor *actor;
    short newY;
    short inAir;

    inAir = 0;
    newY = 0;
    actor = addActorOfType(0,3);
    playerActorPtrMaybe_1 = updateActorPositionMaybe(actor,0,newY,inAir);
    playerActor = playerActorPtrMaybe_1;
    if (!playerActorPtrMaybe_1) {
        return FALSE;
    }
    setupActorType0x11();
    FUN_00404b50();
    isPaused = 0;
    startGameTimer();
    return TRUE;
}

void __fastcall setPointerToNull(void **param_1) {
    ski_assert(param_1, 2578);
    *param_1 = NULL;
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
