#include <iostream>
#include <bitset>
#include <vector>
#include <string>

// Exercise
// 1. Opracowa� kod koryguj�cy pojedynczy b��d bitowy dla wiadomo�ci o�miobitowych (1 bajt)
// 2. Opracowa� kod koryguj�cy podw�jny b��d bitowy dla wiadomo�ci o�miobitowych (1 bajt)
// 3. Napisa� program przekodowuj�cy dowolny plik do postaci zakodowanej jednym z
//  opracowanych kod�w(przygotowanie do transmisji) i odkodowywuj�cy do postaci
//  pierwotnej(odtworzenie danych po transmisji) z korekcj� powsta�ych b��d�w.
// 
//  Dla u�atwienia zadania mo�na kodowa� dane z upakowaniem na granicy 1 bajtu, czyli s�owa o
//  d�ugo�ci od 9 do 16 bit�w jako 2 bajty, 17 - 24 bity jako 3 bajty itd. 
//  Operacje kodowania / odkodowania powinny by� uruchamiane niezale�nie od siebie, tak by mo�na
//  by�o poprzez r�czn� modyfikacj� pliku zasymulowa� powstanie b��d�w transmisji.

using sint32 = int32_t;
using sint64 = int64_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using wchar = wchar_t;
using bchar = char;

using size = uint64;

using word = uint16_t;
using byte = uint8_t;

#include <array>
template <class T, size length>
using array = std::array<T, length>;

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotycz�ce rozpoczynania pracy:
//   1. U�yj okna Eksploratora rozwi�za�, aby doda� pliki i zarz�dza� nimi
//   2. U�yj okna programu Team Explorer, aby nawi�za� po��czenie z kontrol� �r�d�a
//   3. U�yj okna Dane wyj�ciowe, aby sprawdzi� dane wyj�ciowe kompilacji i inne komunikaty
//   4. U�yj okna Lista b��d�w, aby zobaczy� b��dy
//   5. Wybierz pozycj� Projekt > Dodaj nowy element, aby utworzy� nowe pliki kodu, lub wybierz pozycj� Projekt > Dodaj istniej�cy element, aby doda� istniej�ce pliku kodu do projektu
//   6. Aby w przysz�o�ci ponownie otworzy� ten projekt, przejd� do pozycji Plik > Otw�rz > Projekt i wybierz plik sln