#include <windows.h>

#include "../types.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern void __fastcall enlargeRect(RECT *rect1, RECT *rect2);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//

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