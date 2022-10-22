#include <windows.h>

#include "../types.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern void __fastcall updateRectForSpriteAtLocation(RECT *rect, Sprite *sprite, short newX, short newY, short param_5);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//

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