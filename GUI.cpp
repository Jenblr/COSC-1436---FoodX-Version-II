// COSC 1436 - FoodX Version II.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "COSC 1436 - FoodX Version II.h"
#include "mainfunction.h"
#include <windows.h>
#include <tchar.h>

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND Logo;                                      // Window handle = contains part of logo image insertion
HBITMAP bitmap, hLogoImage;                     // Allows insertion of images
HDC localDC;

void AddControls(HWND);
void InsertImage();

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // The main function for a windows application, just like a regular C++ app
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COSC1436FOODXVERSIONII, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COSC1436FOODXVERSIONII));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COSC1436FOODXVERSIONII));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COSC1436FOODXVERSIONII);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
  

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // Tells Windows to make the window visible
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//*********************************************************
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)         *
//                                                        *
//  PURPOSE: Processes messages for the main window.      *
//                                                        *
//  WM_COMMAND  - process the application menu            *
//  WM_PAINT    - Paint the main window                   *
//  WM_DESTROY  - post a quit message and return          *
//                                                        *
//*********************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Welcome to FoodX! Our application's purpose is to provide meal recipes based on dietary needs and wants. Please begin below.");
    TCHAR BrandName[] = _T("FoodX");

    switch (message)
    {
	case WM_CREATE:
	{
			InsertImage();
            AddControls(hWnd);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

			HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            TextOut(hdc,
                5, 5,
                greeting, _tcslen(greeting));
           
           // For inserting logo
			HDC hMemDC = CreateCompatibleDC(hdc);
			::SelectObject(hMemDC, bitmap);
			BitBlt(hdc, 0, 0, 200, 400, hMemDC, 0, 0, SRCCOPY);
			::DeleteDC(hMemDC);
			EndPaint(hWnd, &ps);
           

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Controls images
void AddControls(HWND hWnd)
{
    Logo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 100, 60, 100, 100, hWnd, NULL, NULL, NULL);
    SendMessageW(Logo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
}

// Allows program to insert image
// Remember to resize image to 32bitdepth using iconfx *******
void InsertImage()
{
    hLogoImage = (HBITMAP)LoadImageW(NULL, L"TrialLogo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // Defaulted image size from 0,0 

}