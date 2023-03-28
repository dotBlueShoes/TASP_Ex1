#pragma once

// MANIFEST dependency for controls
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// WINDOWS
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Wyklucz rzadko używane rzeczy z nagłówków systemu Windows
#include <windows.h>
#include <shellapi.h>

// OTHER
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

// RESOURCE
#include "resource.h"

// Exercise
// 1. Opracować kod korygujący pojedynczy błąd bitowy dla wiadomości ośmiobitowych (1 bajt)
// 2. Opracować kod korygujący podwójny błąd bitowy dla wiadomości ośmiobitowych (1 bajt)
// 3. Napisać program przekodowujący dowolny plik do postaci zakodowanej jednym z
//  opracowanych kodów(przygotowanie do transmisji) i odkodowywujący do postaci
//  pierwotnej(odtworzenie danych po transmisji) z korekcją powstałych błędów.
// 
//  Dla ułatwienia zadania można kodować dane z upakowaniem na granicy 1 bajtu, czyli słowa o
//  długości od 9 do 16 bitów jako 2 bajty, 17 - 24 bity jako 3 bajty itd. 
//  Operacje kodowania / odkodowania powinny być uruchamiane niezależnie od siebie, tak by można
//  było poprzez ręczną modyfikację pliku zasymulować powstanie błędów transmisji.

// TODO
// 7. Try implementing 1 error

// TYPES
using sint32 = int32_t;
using sint64 = int64_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using wchar = wchar_t;
using bchar = char;

using size = uint64;

using word = uint16_t;
using byte = uint8_t;

// ARRAY
#include <array>
template <class T, size length>
using array = std::array<T, length>;