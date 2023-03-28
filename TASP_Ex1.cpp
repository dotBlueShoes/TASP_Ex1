#include "Framework.hpp"
#include "Logic.hpp"

#define MAX_LOADSTRING 100
#define IDC_BUTTON_A_CLICK 201
#define IDC_BUTTON_B_CLICK 202

// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(
    IN          HINSTANCE hInstance,
    OPTIONAL IN HINSTANCE hPrevInstance,
    IN          LPWSTR    lpCmdLine,
    IN          int       nCmdShow
) {

    UNREFERENCED_PARAMETER(hPrevInstance);

    { // Taking care of possible arguments.
        int argumentsCount;
        LPWSTR* arguments;

        arguments = CommandLineToArgvW(lpCmdLine, &argumentsCount);
        
        // First arg. IS NOT THE PATH OF THE EXECUTABLE.
        //  Therefore 1 extra arg. is needed at the start.
        //if (argumentsCount == 1) return 1;
        if (argumentsCount > 1) {

            const size maxArgumentLength = 100;
            LPCWSTR wideStr = L"Some message";
            
            char** buffer = new char*[argumentsCount];
            
            { // WCHAR** to CHAR** conversion
                #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
                for (size i = 0; i < argumentsCount; i++) {
                    buffer[i] = new char[maxArgumentLength];
                    wcstombs(buffer[i], arguments[i], maxArgumentLength);
                    //MessageBoxA(nullptr, buffer[i], buffer[i], 0); // DEBUG
                }
            }

            main(argumentsCount, buffer);
            
            for (int i = 0; i < argumentsCount; i++)
                delete buffer[i];
            delete[] buffer;

            return 0;
        }

    }

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TASPEX1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASPEX1));
    MSG msg;

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASPEX1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_TASPEX1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 206, 100, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   HWND buttonA = CreateWindowW (
       L"BUTTON",
       L"Encode",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10,
       10,
       80,
       40,
       hWnd,
       (HMENU)IDC_BUTTON_A_CLICK,
       hInstance,
       nullptr
   );

   HWND buttonB = CreateWindowW (
       L"BUTTON",                                               // Predefined class
       L"Decode",                                               // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,   // Styles 
       10 + 80 + 10,                                            // x position 
       10,                                                      // y position 
       80,                                                      // Button width
       40,                                                      // Button height
       hWnd,                                                    // Parent window
       (HMENU)IDC_BUTTON_B_CLICK,                                                 // No menu.
       hInstance,
       nullptr                                                  // Pointer not needed.
   );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam
) {
    switch (message) {
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            switch (wmId) {

                case IDC_BUTTON_A_CLICK: {
                    namespace PDECC = ParityDoubleErrorCorrectingCode;
                    const auto iFilePath("nocoded.txt");
                    const auto oFilePath("encoded.txt");
                    PDECC::ReadAndEncode(iFilePath, oFilePath);
                    MessageBeep(MB_OK); // Just to give user more feedback.
                } break;

                case IDC_BUTTON_B_CLICK: {
                    namespace PDECC = ParityDoubleErrorCorrectingCode;
                    const auto iFilePath("encoded.txt");
                    const auto oFilePath("decoded.txt");
                    PDECC::ReadAndDecode(iFilePath, oFilePath);
                    MessageBeep(MB_OK);// Just to give user more feedback.
                } break;


                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Tutaj dodaj kod rysujący używający elementu hdc...
            EndPaint(hWnd, &ps);
        } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;

        default: {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    return 0;
}
