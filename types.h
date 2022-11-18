//
// Created by Eric on 22/10/2022.
//

#ifndef SKIFREE_DECOMP_TYPES_H
#define SKIFREE_DECOMP_TYPES_H

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

typedef struct PermObjectList {
    struct PermObject *startingObject;
    struct PermObject *nextObject;
    struct PermObject *currentObj;
} PermObjectList;

typedef struct Actor {
    struct Actor *next;
    struct Actor *linkedActor;
    struct Actor *actorPtr;
    struct PermObject *permObject;
    USHORT spriteIdx2;
    //2 byte padding TODO check alignment of struct
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

typedef struct {
    short unk_0;
    short unk_2;
    short unk_4;
    short unk_6;
    short xRelated;
    short unk_a;
    UINT frameNo;
} ActorVelStruct;

typedef struct {
    HGLOBAL soundResource;
    LPVOID soundData;
} Sound;

#define NUM_ACTORS 100
#define NUM_SPRITES 90
#define NUM_STRINGS 20
#define NUM_PERM_OBJECTS 256

// Actor bit flags

#define FLAG_1  1
#define FLAG_2  2
#define FLAG_4  4
#define FLAG_8  8
#define FLAG_10 0x10
#define FLAG_20 0x20
#define FLAG_40 0x40
#define FLAG_80 0x80

#define BORDER_LEFT   0
#define BORDER_RIGHT  1
#define BORDER_TOP    2
#define BORDER_BOTTOM 3

#define ACTOR_TYPE_0_PLAYER      0
#define ACTOR_TYPE_1_BEGINNER    1
#define ACTOR_TYPE_2_DOG         2
#define ACTOR_TYPE_3_SNOWBOARDER 3

#endif //SKIFREE_DECOMP_TYPES_H
