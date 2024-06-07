// file_collector.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "file_collector.h"
#include "file_types_items.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <shellapi.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
 
file_collector::item_list itemList;
int window_size_x = 600;
int window_size_y = 400;

int possesed_item = -1;

int last_mouse_x = -1;
int last_mouse_y = -1;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    
    file_collector::start();

    file_collector::item i1;
    i1.x = .2f;
    i1.y = .1f;
    i1.file_path = L"\"C:\\Users\\judei\\text.txt\"";
    file_collector::item i2;
    i2.x = .7f;
    i2.y = .8f;
    i2.file_path = L"\"C:\\Program Files\\Obsidian\\Obsidian.1.5.3.exe\"";

    file_collector::add_item(itemList, i1);
    file_collector::add_item(itemList, i2);



    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FILECOLLECTOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILECOLLECTOR));

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
    file_collector::stop();
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILECOLLECTOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FILECOLLECTOR);
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
   RECT windowRect = { 0,0,window_size_x, window_size_y };
   AdjustWindowRect(&windowRect, CS_HREDRAW | CS_VREDRAW, TRUE);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, window_size_x, window_size_y, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
      if (wParam & MK_CONTROL)
      {
        file_collector::click_range cr;
        cr.x = 100.0f / float(window_size_x);
        cr.y = 30.0f / float(window_size_y);
        int search_index = file_collector::find_item_by_position(itemList, cr, float(GET_X_LPARAM(lParam)) / float(window_size_x), float(GET_Y_LPARAM(lParam)) / float(window_size_y));
        if (search_index != -1)
        {
          file_collector::delete_item(itemList, search_index);
        }
      }
      else if (wParam & MK_SHIFT)
      {
        file_collector::click_range cr;
        cr.x = 100.0f / float(window_size_x);
        cr.y = 30.0f / float(window_size_y);
        int search_index = file_collector::find_item_by_position(itemList, cr, float(GET_X_LPARAM(lParam)) / float(window_size_x), float(GET_Y_LPARAM(lParam)) / float(window_size_y));
        OutputDebugString(L"MK_SHIFT");
      }
      else
      {

        file_collector::click_range cr;
        cr.x = 100.0f / float(window_size_x);
        cr.y = 30.0f / float(window_size_y);
        int search_index = file_collector::find_item_by_position(itemList, cr, float(GET_X_LPARAM(lParam)) / float(window_size_x), float(GET_Y_LPARAM(lParam)) / float(window_size_y));
        if (search_index != -1)
        {
          possesed_item = search_index;
          InvalidateRect(hWnd, NULL, TRUE);
          UpdateWindow(hWnd);
        }
      }
    }
    break;
    case WM_LBUTTONUP:
    {
      possesed_item = -1;
      InvalidateRect(hWnd, NULL, TRUE);
      UpdateWindow(hWnd);
    }
    break;
    case WM_RBUTTONDOWN:
    {
      file_collector::click_range cr;
      cr.x = 100.0f / float(window_size_x);
      cr.y = 30.0f / float(window_size_y);
      int search_index = file_collector::find_item_by_position(itemList, cr, float(GET_X_LPARAM(lParam)) / float(window_size_x), float(GET_Y_LPARAM(lParam)) / float(window_size_y));
      if (search_index != -1)
      {
        std::wstring* wide = &itemList.item_vector[search_index].file_path;
        /*std::string normalStringFromWide;
        std::transform(wide->begin(), wide->end(), std::back_inserter(normalStringFromWide), [](wchar_t c) {
          return (char)c;
          });*/
        ShellExecute(hWnd, L"open", &wide->front(), NULL, NULL, SW_SHOWDEFAULT);
      }
    } 
    break;
    case WM_MOUSEMOVE:
    {
      if (possesed_item != -1)
      {
        if (abs(GET_X_LPARAM(lParam) - last_mouse_x) > 30 || abs(GET_Y_LPARAM(lParam) - last_mouse_y) > 30 || last_mouse_x == -1 || last_mouse_y == -1)
        {
          last_mouse_x = GET_X_LPARAM(lParam);
          last_mouse_y = GET_Y_LPARAM(lParam);
          itemList.item_vector[possesed_item].x = float(GET_X_LPARAM(lParam)) / float(window_size_x); 
          itemList.item_vector[possesed_item].y = float(GET_Y_LPARAM(lParam)) / float(window_size_y);
          
          InvalidateRect(hWnd, NULL, TRUE);
          UpdateWindow(hWnd);
        }
      }
    }
      break;
    case WM_SIZING:
      
      break;
    case WM_SIZE:

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
                OutputDebugString(L"b");
                DestroyWindow(hWnd);
                break;
            case IDM_ITEM_ADD:
            {
              file_collector::item itm;
              itm.x = .5f;
              itm.y = .5f;
              itm.file_path = L"this works";
              file_collector::add_item(itemList, itm);
              InvalidateRect(hWnd, NULL, TRUE);
              UpdateWindow(hWnd);
            }
            break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            file_collector::draw_button(window_size_x, window_size_y, hdc, itemList);
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
