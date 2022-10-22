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
#define FLAG_10 10
#define FLAG_20 20
#define FLAG_40 40
#define FLAG_80 80

#endif //SKIFREE_DECOMP_TYPES_H
