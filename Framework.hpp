#include <iostream>
#include <bitset>
#include <vector>
#include <string>

// Exercise
// 1. Opracowaæ kod koryguj¹cy pojedynczy b³¹d bitowy dla wiadomoœci oœmiobitowych (1 bajt)
// 2. Opracowaæ kod koryguj¹cy podwójny b³¹d bitowy dla wiadomoœci oœmiobitowych (1 bajt)
// 3. Napisaæ program przekodowuj¹cy dowolny plik do postaci zakodowanej jednym z
//  opracowanych kodów(przygotowanie do transmisji) i odkodowywuj¹cy do postaci
//  pierwotnej(odtworzenie danych po transmisji) z korekcj¹ powsta³ych b³êdów.
// 
//  Dla u³atwienia zadania mo¿na kodowaæ dane z upakowaniem na granicy 1 bajtu, czyli s³owa o
//  d³ugoœci od 9 do 16 bitów jako 2 bajty, 17 - 24 bity jako 3 bajty itd. 
//  Operacje kodowania / odkodowania powinny byæ uruchamiane niezale¿nie od siebie, tak by mo¿na
//  by³o poprzez rêczn¹ modyfikacjê pliku zasymulowaæ powstanie b³êdów transmisji.

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

// Porady dotycz¹ce rozpoczynania pracy:
//   1. U¿yj okna Eksploratora rozwi¹zañ, aby dodaæ pliki i zarz¹dzaæ nimi
//   2. U¿yj okna programu Team Explorer, aby nawi¹zaæ po³¹czenie z kontrol¹ Ÿród³a
//   3. U¿yj okna Dane wyjœciowe, aby sprawdziæ dane wyjœciowe kompilacji i inne komunikaty
//   4. U¿yj okna Lista b³êdów, aby zobaczyæ b³êdy
//   5. Wybierz pozycjê Projekt > Dodaj nowy element, aby utworzyæ nowe pliki kodu, lub wybierz pozycjê Projekt > Dodaj istniej¹cy element, aby dodaæ istniej¹ce pliku kodu do projektu
//   6. Aby w przysz³oœci ponownie otworzyæ ten projekt, przejdŸ do pozycji Plik > Otwórz > Projekt i wybierz plik sln