//
// Created by Eric on 22/10/2022.
//

#ifndef SKIFREE_DECOMP_DATA_H
#define SKIFREE_DECOMP_DATA_H

extern char s_assertErrorFormat[];
extern char s_Assertion_Failed_0040c0a8[];
extern char s_insufficient_local_memory[];
extern char s_nosound_0040c0fc[];
extern char iniSsConfigKey[];
extern char entpack_ini_section_name_ski[];
extern char s_entpack_ini[];
extern char scoreFormatString[];
extern char stylePointsFormatString[];
extern char scoreStringFormatString[];
extern char newlineString[];
extern char iniFsConfigKey[];
extern char iniGsConfigKey[];

extern USHORT actorFrameToSpriteTbl[];
extern UINT UINT_ARRAY_0040a22c[];
extern ActorVelStruct ActorVelStruct_ARRAY_0040a308[];
extern ActorVelStruct snowboarderActorMovementTbl[];
extern UINT UINT_ARRAY_0040a434[];

extern char sourceFilename[];
extern HWND hSkiMainWnd;
extern HWND hSkiStatusWnd;
extern char **stringCache;
extern HINSTANCE skiFreeHInstance;
extern char s_out_o_memory[];
extern Sprite *sprites;
extern Actor *actors;
extern Actor *actorListPtr;
extern Actor *playerActor;
extern Actor *playerActorPtrMaybe_1;
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
extern DWORD pauseStartTickCount;
extern DWORD statusWindowLastUpdateTime;
extern DWORD timedGameRelated;
extern RECT windowClientRect;
extern RECT statusBorderRect;
extern RECT windowClientRectWith120Margin;
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
extern LPCTSTR statusWindowNameStrPtr;
extern HGDIOBJ statusWindowFont;
extern short textLineHeight;
extern short statusWindowHeight;
extern short statusWindowTotalTextWidth;
extern short statusWindowLabelWidth;
extern BOOL isGameTimerRunning;
extern BOOL isSsGameMode;
extern BOOL isGsGameMode;
extern int updateTimerDurationMillis;
extern void *DAT_0040c78c;
extern Actor blankTemplateActor;
extern Actor *currentFreeActor;
extern BOOL isTurboMode;
extern HDC smallBitmapDC;
extern HDC smallBitmapDC_1bpp;
extern HDC largeBitmapDC;
extern HDC largeBitmapDC_1bpp;
extern HDC bitmapSourceDC;
extern HGDIOBJ smallBitmapSheet;
extern HGDIOBJ smallBitmapSheet_1bpp;
extern HGDIOBJ largeBitmapSheet;
extern HGDIOBJ largeBitmapSheet_1bpp;
extern HGDIOBJ scratchBitmap;
extern BOOL isFsGameMode;
extern int stylePoints;
extern short playerX;
extern short playerY;
extern short permObjectCount;
extern ActorVelStruct beginnerActorMovementTbl;
extern short scratchBitmapWidth;
extern short scratchBitmapHeight;
extern int elapsedTime;
extern int totalAreaOfActorSprites;
extern short windowHeight;
extern short windowWidth;
extern int windowWithMarginTotalArea;
extern PermObject *currentSlalomFlag;
extern PermObject *firstSlalomFlagLeft;
extern PermObject *FirstSlalomFlagRight;
extern int INT_0040c964;
extern int INT_0040c968;
extern int INT_0040c960;
extern short DAT_0040c5d8;
extern short DAT_0040c714;


extern BOOL (WINAPI *sndPlaySoundAFuncPtr)(LPCSTR, UINT);
extern void (CALLBACK* timerCallbackFuncPtr)(HWND, UINT, UINT, DWORD);

#endif //SKIFREE_DECOMP_DATA_H
