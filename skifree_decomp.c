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

#define NUM_ACTORS 100
#define NUM_SPRITES 90
#define NUM_STRINGS 20

void __fastcall assertFailed(char *srcFilename, int lineNumber);
int __fastcall showErrorMessage(LPCSTR text);

#define ski_assert(exp, src, line) (void)( (exp) || (assertFailed(src, line), 0) )

extern char s_assertErrorFormat[];
extern char s_Assertion_Failed_0040c0a8[];
extern char s_insufficient_local_memory[];

extern void setWindowTitle();
extern char sourceFilename[];
extern HWND hSkiMainWnd;
extern char **stringCache;
extern HINSTANCE skiFreeHInstance;
extern char s_out_o_memory[];
extern Sprite *sprites;
extern Actor *actors;
extern void *PTR_0040c758;

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