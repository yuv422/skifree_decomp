// ski32_decomp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
/*
#include "resource.h"


#define MAX_LOADSTRING 100


extern HINSTANCE skiFreeHInstance;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

HWND hSkiMainWnd;
BOOL isSoundDisabled = FALSE;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

char * __fastcall getCachedString(UINT stringIdx);


int __fastcall showErrorMessage(LPCSTR param_1) {

MessageBox(NULL, param_1, "test title", 0x30);
	return 1;
}

BOOL allocateMemory() { 
//	showErrorMessage("Insufficient local memory.");
	return FALSE; 
}

BOOL resetGame() { return TRUE; }
BOOL __fastcall initWindows(HINSTANCE hInstance, HINSTANCE hPrevInstance, int nCmdShow) {
	return TRUE;
}

BOOL FUN_00404a80() { return TRUE; }
void FUN_004056a0() { return; }

int __stdcall WinMain1(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
//	HICON icon = LoadIconA(hInstance, MAKEINTRESOURCE(134));
//	icon = LoadIconA(hInstance, "iconSki");
//"iconSki");
	return WinMain1(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	/ *
  int iVar1;
  BOOL retVal;
  MSG msg;
  char *testStr;
  char buf[100];

//  void *test2 = lstrcpyA;


  skiFreeHInstance = GetModuleHandle(NULL); // hInstance;


  if(LoadBitmap(skiFreeHInstance, MAKEINTRESOURCE(IDB_BITMAP1)) == NULL) {
	  return 0;
  }
  
  testStr = getCachedString(2);
  showErrorMessage(testStr);

  LoadStringA(skiFreeHInstance, 2, buf, 99);
  showErrorMessage(buf);

  iVar1 = lstrcmpi(lpCmdLine,"nosound");
  if (iVar1 == 0) {
    isSoundDisabled = 1;
  }
  retVal = allocateMemory();
  if (retVal == 0) {
    return 0;
  }
  retVal = resetGame();
  if (retVal == 0) {
    return 0;
  }
  retVal = initWindows(hInstance, hPrevInstance, nCmdShow);
  if (retVal == 0) {
    return 0;
  }
  iVar1 = FUN_00404a80();
  if (iVar1 == 0) {
    DestroyWindow(hSkiMainWnd);
    FUN_004056a0();
    return 0;
  }
  iVar1 = GetMessage(&msg,(HWND)0x0,0,0);
  while (iVar1 != 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    iVar1 = GetMessage(&msg,(HWND)0x0,0,0);
  }
  FUN_004056a0();
  return msg.wParam;
  * /
/ *
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SKI32_DECOMP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SKI32_DECOMP);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
* /
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SKI32_DECOMP);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SKI32_DECOMP;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
				RECT rt;
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);


	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...

			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
*/