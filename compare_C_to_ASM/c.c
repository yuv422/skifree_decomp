#include <windows.h>

typedef struct {
    HDC hdc1;
    HDC hdc2;
    short sheetYOffset;
    short width;
    short height;
    short totalPixels;
} Sprite;

typedef struct PermObject {
    struct Actor *actor;
    Sprite *spritePtr;
    short spriteIdx;
    // 2 bytes padding
    int actorTypeMaybe;
    int actorFrameNo;
    short maybeX;
    short maybeY;
    short unk_0x18;
    short unk_0x1a;
    short unk_0x1c;
    short unk_0x1e;
    int unk_0x20;
} PermObject;

typedef struct Actor {
    struct Actor *next;
    struct Actor *linkedActor;
    struct Actor *actorPtr;
    struct PermObject *permObject;
    UINT spriteIdx2;
    Sprite *spritePtr;
    int typeMaybe;
    UINT frameNo;
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

#define FLAG_1 1
#define FLAG_8 8

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);
extern char sourceFilename[];

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//

void __fastcall actorSetFlag8IfFlag1IsUnset(Actor *actor) {
    ski_assert(actor, 865);

    if ((actor->flags & FLAG_1) == 0) {
        if (actor->linkedActor) {
            actor->linkedActor->linkedActor = NULL;
        }
        actor->flags |= FLAG_8;
    }
}