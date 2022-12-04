//
// Created by Eric on 22/10/2022.
//

#ifndef SKIFREE_DECOMP_DATA_H
#define SKIFREE_DECOMP_DATA_H

char s_assertErrorFormat[] = "%s line %u";
char s_Assertion_Failed_0040c0a8[] = "Assertion Failed";
char s_insufficient_local_memory[] = "Insufficient local memory.";
char s_nosound_0040c0fc[] = "nosound";
char iniSsConfigKey[] = "SS";
char entpack_ini_section_name_ski[] = "Ski";
char s_entpack_ini[] = "entpack.ini";
char scoreFormatString[] = "%ld ";
char stylePointsFormatString[] = "%9ld";
char scoreStringFormatString[] = "%s";
char newlineString[] = "\n\n";
char iniFsConfigKey[] = "FS";
char iniGsConfigKey[] = "GS";
char s_out_o_memory[] = "[out o' memory]";

const USHORT actorFrameToSpriteTbl[] = {
        0x1,      0x2,      0x3,      0x4,
        0x5,      0x6,      0x7,      0x8,
        0x9,      0xA,      0xB,      0xC,
        0xD,      0xE,      0xF,      0x10,
        0x11,     0x12,     0x13,     0x14,
        0x15,     0x16,     0x1C,     0x1D,
        0x1E,     0x1F,     0x20,     0x21,
        0x22,     0x23,     0x24,     0x25,
        0x26,     0x27,     0x28,     0x29,
        0x2A,     0x2B,     0x2C,     0x41,
        0x42,     0x43,     0x44,     0x45,
        0x46,     0x47,     0x48,     0x49,
        0x4A,     0x4B,     0x4C,     0x4D,
        0x4E,     0x4F,     0x50,     0x51,
        0x53,     0x54,     0x55,     0x54,
        0x31,     0x57,     0x58,     0x59
};

const UINT UINT_ARRAY_0040a22c[] = {
         6,            22,            27,            31,
        39,            42,            42,            42,
        42,            56,            60
};

const ActorVelStruct ActorVelStruct_ARRAY_0040a308[] = {
        {
                1,          //             unk_0                             XREF[1]:     updatePlayerActor:00402a79 (*)
                16,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                0         //              frameNo
        },
        {
                1,          //             unk_0
                12,         //             unk_2
                1,          //             unk_4
                1,          //             unk_6
                -1,       //             xRelated
                0,          //             unk_a
                1         //              frameNo
        },
        {
                1,          //             unk_0
                6,          //             unk_2
                1,          //             unk_4
                4,          //             unk_6
                -1,       //             xRelated
                0,          //             unk_a
                2         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                1,          //             unk_4
                8,          //             unk_6
                -1,       //             xRelated
                0,          //             unk_a
                3         //              frameNo
        },
        {
                1,          //             unk_0
                12,         //             unk_2
                1,          //             unk_4
                1,          //             unk_6
                1,        //             xRelated
                0,          //             unk_a
                4         //              frameNo
        },
        {
                1,          //             unk_0
                6,          //             unk_2
                1,          //             unk_4
                4,          //             unk_6
                1,        //             xRelated
                0,          //             unk_a
                5         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                1,          //             unk_4
                8,          //             unk_6
                1,        //             xRelated
                0,          //             unk_a
                6         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                1,          //             unk_4
                8,          //             unk_6
                -1,       //             xRelated
                0,          //             unk_a
                7         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                1,          //             unk_4
                8,          //             unk_6
                1,        //             xRelated
                0,          //             unk_a
                8         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                9         //              frameNo
        },
        {
                1,          //             unk_0
                0,          //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                10        //              frameNo
        },
        {
                0,          //             unk_0
                0,          //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                11        //              frameNo
        },
        {
                0,          //             unk_0
                0,          //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                12        //              frameNo
        },
        {
                1,          //             unk_0
                24,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                13        //              frameNo
        },
        {
                1,          //             unk_0
                22,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                14        //              frameNo
        },
        {
                1,          //             unk_0
                22,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                15        //              frameNo
        },
        {
                1,          //             unk_0
                20,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                16        //              frameNo
        },
        {
                1,          //             unk_0
                24,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                17        //              frameNo
        },
        {
                1,          //             unk_0
                20,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                18        //              frameNo                           XREF[1]:     updatePlayerActor:00402ac9 (R)
        },
        {
                1,          //             unk_0
                20,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                19        //              frameNo
        },
        {
                1,          //             unk_0
                22,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                20        //              frameNo
        },
        {
                1,          //             unk_0
                22,         //             unk_2
                0,          //             unk_4
                0,          //             unk_6
                0,        //             xRelated
                0,          //             unk_a
                21        //              frameNo
        }
};

// The original optimises the data packing by omitting the first 13 records
const UINT UINT_ARRAY_0040a434[] = {
        0,       0,             0,             0,
        0,       0,             0,             0,
        0,       0,             0,             0,
        0,             0,             3,             6,
        11,            11,            11,            11,
        11,            11,            0
};

const ActorVelStruct beginnerActorMovementTbl[] = {
        {
                1,  // unk_0
                1,  // unk_2
                0,  // unk_4
                0,  // unk_6
                0,  // xRelated
                0,  // unk_a
                22 // frameNo
        },
        {
                1,  // unk_0
                1,  // unk_2
                1,  // unk_4
                4,  // unk_6
                -1, // xRelated
                0,  // unk_a
                23 // frameNo
        },
        {
                1,  // unk_0
                1,  // unk_2
                1,  // unk_4
                4,  // unk_6
                1,  // xRelated
                0,  // unk_a
                24 // frameNo
        },
        {
                0,  // unk_0
                0,  // unk_2
                0,  // unk_4
                0,  // unk_6
                0,  // xRelated
                0,  // unk_a
                25 // frameNo
        },
        {
                0,  // unk_0
                0,  // unk_2
                0,  // unk_4
                0,  // unk_6
                0,  // xRelated
                0,  // unk_a
                26 // frameNo
        }
};

const ActorVelStruct snowboarderActorMovementTbl[] = {
        {
                2,    // unk_0
                18,   // unk_2
                2,    // unk_4
                1,    // unk_6
                -1,   // xRelated
                0,    // unk_a
                31    // frameNo
        },
        {
                2,    // unk_0
                18,   // unk_2
                2,    // unk_4
                1,    // unk_6
                1,    // xRelated
                0,    // unk_a
                32    // frameNo
        },
        {
                1,    // unk_0
                22,   // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                33    // frameNo
        },
        {
                1,    // unk_0
                4,    // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                34    // frameNo
        },
        {
                1,    // unk_0
                4,    // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                35    // frameNo
        },
        {
                1,    // unk_0
                4,    // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                36    // frameNo
        },
        {
                1,    // unk_0
                4,    // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                37    // frameNo
        },
        {
                1,    // unk_0
                4,    // unk_2
                0,    // unk_4
                0,    // unk_6
                0,    // xRelated
                0,    // unk_a
                38   // frameNo
        }
};

const PlayerTurnFrameNoLookupTbl playerTurnFrameNoTbl[] = {
        {1, 4 },
        {2,0 },
        {3, 1 },
        {7,2 },
        {0, 5 },
        {4,6 },
        {5, 8 },
        {3,2 },
        {5, 6 },
        {9,2 },
        {5, 10 },
        {3,6 },
        {3, 6 },
        {14,15 },
        {16, 13 },
        {13,16 },
        {15, 14 },
        {14,15 },
        {20, 21 },
        {20,21 },
        {16, 13 },
        {13,16 }
};

char sourceFilename[] = "V:\\hack\\ski32\\ski2.c";

Actor blankTemplateActor = {
        NULL, // next
        NULL, // linkedActor
        NULL, // actorPtr
        NULL, // permObject
        0,    // spriteIdx2
        NULL, // spritePtr
        18,   // typeMaybe
        64,   // frameNo
        {0,0,0,0}, // someRect
        {0,0,0,0}, // rect

        0,         // xPosMaybe
        0,         // yPosMaybe
        0,         // isInAir
        0,         // HorizontalVe
        0,         // verticalVelo
        0,         // inAirCounter
        0          // flags
};

HWND hSkiMainWnd = NULL;
HWND hSkiStatusWnd = NULL;
char **stringCache = NULL;
HINSTANCE skiFreeHInstance = NULL;
Sprite *sprites = NULL;
Actor *actors = NULL;
Actor *actorListPtr = NULL;
Actor *playerActor = NULL;
Actor *playerActorPtrMaybe_1 = NULL;
PermObject *permObjects = NULL;
BOOL isSoundDisabled = FALSE;
USHORT SCREEN_WIDTH = 0;
USHORT SCREEN_HEIGHT = 0;
HBRUSH whiteBrush;
BOOL isPaused;
BOOL isMinimised;
UINT mainWndActivationFlags;
BOOL inputEnabled;
int skierScreenXOffset;
int skierScreenYOffset;
BOOL redrawRequired;
DWORD timerFrameDurationInMillis;
DWORD currentTickCount;
DWORD prevTickCount;
DWORD pauseStartTickCount;
DWORD statusWindowLastUpdateTime;
DWORD timedGameRelated;
RECT windowClientRect;
RECT statusBorderRect;
RECT windowClientRectWith120Margin;
HDC mainWindowDC;
HDC statusWindowDC;
Sound sound_1;
Sound sound_2;
Sound sound_3;
Sound sound_4;
Sound sound_5;
Sound sound_6;
Sound sound_7;
Sound sound_8;
Sound sound_9;
LPCTSTR statusWindowNameStrPtr;
HGDIOBJ statusWindowFont;
short textLineHeight;
short statusWindowHeight;
short statusWindowTotalTextWidth;
short statusWindowLabelWidth;
BOOL isGameTimerRunning;
BOOL isSsGameMode;
BOOL isGsGameMode;
int updateTimerDurationMillis;
void *DAT_0040c78c;
Actor *currentFreeActor;
BOOL isTurboMode;
HDC smallBitmapDC;
HDC smallBitmapDC_1bpp;
HDC largeBitmapDC;
HDC largeBitmapDC_1bpp;
HDC bitmapSourceDC;
HGDIOBJ smallBitmapSheet;
HGDIOBJ smallBitmapSheet_1bpp;
HGDIOBJ largeBitmapSheet;
HGDIOBJ largeBitmapSheet_1bpp;
HGDIOBJ scratchBitmap;
BOOL isFsGameMode;
int stylePoints;
int playerX;
short playerY;
USHORT permObjectCount;
short scratchBitmapWidth;
short scratchBitmapHeight;
int elapsedTime;
int totalAreaOfActorSprites;
short windowHeight;
short windowWidth;
int windowWithMarginTotalArea;
PermObject *currentSlalomFlag;
PermObject *firstSlalomFlagLeft;
PermObject *FirstSlalomFlagRight;
int INT_0040c964;
int INT_0040c968;
int INT_0040c960;
short DAT_0040c5d8;
short DAT_0040c714;
int DAT_0040c760;
short prevMouseX;
short prevMouseY;
PermObjectList PermObjectList_0040c630;
PermObjectList PermObjectList_0040c5e0;
PermObjectList PermObjectList_0040c658;
PermObjectList PermObjectList_0040c738; // ski lift poles
PermObjectList PermObjectList_0040c720;


BOOL (WINAPI *sndPlaySoundAFuncPtr)(LPCSTR, UINT);
void (CALLBACK* timerCallbackFuncPtr)(HWND, UINT, UINT, DWORD);

#endif //SKIFREE_DECOMP_DATA_H
