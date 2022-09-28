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


#define ski_assert(exp, src, line) (void)( (exp) || (assertFailed(src, line), 0) )

extern char s_assertErrorFormat[];
extern char s_Assertion_Failed_0040c0a8[];
extern char s_insufficient_local_memory[];
extern char s_nosound_0040c0fc[];

//
// ASM Functions
//
extern void setWindowTitle();
extern void cleanupSound();
extern int setupGame();
extern int resetGame();
extern void updateGameState();
extern void __fastcall drawWindow(HDC hdc, RECT *rect);
extern void __fastcall formatAndPrintStatusStrings(HDC windowDC);
extern LRESULT CALLBACK skiMainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK skiStatusWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern char sourceFilename[];
extern HWND hSkiMainWnd;
extern HWND hSkiStatusWnd;
extern char **stringCache;
extern HINSTANCE skiFreeHInstance;
extern char s_out_o_memory[];
extern Sprite *sprites;
extern Actor *actors;
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
extern DWORD statusWindowLastUpdateTime;
extern RECT windowClientRect;
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


extern BOOL (WINAPI *sndPlaySoundAFuncPtr)(LPCSTR, UINT);
extern int (*timerCallbackFuncPtr)();

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
    setWindowTitle();
}

int __fastcall doRectsOverlap(RECT *rect1, RECT *rect2) {
    ski_assert(rect1 != NULL, sourceFilename, 352);
    ski_assert(rect2 != NULL, sourceFilename, 353);

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

int timerCallbackFunc() {
    if (inputEnabled != 0) {
        timerUpdateFunc();
    }
    return 1;
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