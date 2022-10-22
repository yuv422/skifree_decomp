#include <windows.h>

#include "../types.h"

extern void __fastcall assertFailed(char *srcFilename, int lineNumber);

#include "../data.h"

#define ski_assert(exp, line) (void)( (exp) || (assertFailed(sourceFilename, line), 0) )

// FUNCTION GOES HERE
//

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