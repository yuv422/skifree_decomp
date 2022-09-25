// ski32_decomp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

void __fastcall assertFailed(char *srcFilename, int lineNumber);

#define ski_assert(exp, src, line) (void)( (exp) || (assertFailed(src, line), 0) )

extern char s_assertErrorFormat[];
extern char s_Assertion_Failed_0040c0a8[];

extern void setWindowTitle();
extern char sourceFilename[];
extern HWND hSkiMainWnd;

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