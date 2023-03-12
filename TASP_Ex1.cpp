#include "Framework.hpp"

// 0b0000.0000 0b0000.0001
// 
// 0b0000.0010 0b0000.0011
// 
// 0b0000.0100 0b0000.0101 0b0000.0110 0b0000.0111
// 
// 0b0000.1000 0b0000.1001 0b0000.1010 0b0000.1011
// 0b0000.1100 0b0000.1101 0b0000.1110 0b0000.1111 
// 
// 0b0001.0000 0b0001.0001 0b0001.0010 0b0001.0011
// 0b0001.0100 0b0001.0101 0b0001.0110 0b0001.0111
// 0b0001.1000 0b0001.1001 0b0001.1010 0b0001.1011
// 0b0001.1100 0b0001.1101 0b0001.1110 0b0001.1111
// 
// 0b0010.0000 0b0010.0001 0b0010.0010 0b0010.0011
// 0b0010.0100 0b0010.0101 0b0010.0110 0b0010.0111
// 0b0010.1000 0b0010.1001 0b0010.1010 0b0010.1011
// 0b0010.1100 0b0010.1101 0b0010.1110 0b0010.1111
// 0b0011.0000 0b0011.0001 0b0011.0010 0b0011.0011
// 0b0011.0100 0b0011.0101 0b0011.0110 0b0011.0111
// 0b0011.1000 0b0011.1001 0b0011.1010 0b0011.1011
// 0b0011.1100 0b0011.1101 0b0011.1110 0b0011.1111
// 
// 0b0100.0000 0b0100.0001 0b0100.0010 0b0100.0011
// 0b0100.0100 0b0100.0101 0b0100.0110 0b0100.0111
// 0b0100.1000 0b0100.1001 0b0100.1010 0b0100.1011
// 0b0100.1100 0b0100.1101 0b0100.1110 0b0100.1111
// 0b0101.0000 0b0101.0001 0b0101.0010 0b0101.0011
// 0b0101.0100 0b0101.0101 0b0101.0110 0b0101.0111
// 0b0101.1000 0b0101.1001 0b0101.1010 0b0101.1011
// 0b0101.1100 0b0101.1101 0b0101.1110 0b0101.1111
// 0b0110.0000 0b0110.0001 0b0110.0010 0b0110.0011
// 0b0110.0100 0b0110.0101 0b0110.0110 0b0110.0111
// 0b0110.1000 0b0110.1001 0b0110.1010 0b0110.1011
// 0b0110.1100 0b0110.1101 0b0110.1110 0b0110.1111
// 0b0111.0000 0b0111.0001 0b0111.0010 0b0111.0011
// 0b0111.0100 0b0111.0101 0b0111.0110 0b0111.0111
// 0b0111.1000 0b0111.1001 0b0111.1010 0b0111.1011
// 0b0111.1100 0b0111.1101 0b0111.1110 0b0111.1111


// Odległość pomiędzy słowami wynosi 2. Można więc wywnioskować przy zmianie 1 bitu wiadomość docelową.
// + 00.1001
// 00.0000, 00.1001, 01.0010, 01.1011, 10.0100, 10.1101, 11.0110, 11.1111
// 
// 00.0000, 00.0111, 11.1000, 
// 01.0101, 10.1010
// 

// wiadomosci - dł. x bitów         2 = 00, 01, 10, 11; 3 = 000, 001, 010, 011, 100, 101, 110, 111 
// istnieje więc. 2^x wiadomości.
// 
// y - bity parzystości
// dł. wiadomość = x + y
//
// Warunek bitów parzystośći: HT = 0, gdzie 
//  T = (x + y)
//  H = n x (n + m)

// Macierz reprezentująca 4-bit wiadomości i 3-bit kontrolki
// [ 1 1 0 1 1 0 0 ]
// [ 1 0 1 1 0 1 0 ]
// [ 0 1 1 1 0 0 1 ]
//
// 0000 0000.000
// 0001 0001.111
// 0010 0010.011
// 0011 0011.100
// 0100 0100.101
// 0101 0101.010
// 0110 0110.110
// 0111 0011.001
// 1000 1000.110
// 1001 1001.001
// 1010 1010.101
// 1011 1011.010
// 1100 1100.011
// 1101 1101.100
// 1110 1110.000
// 1111 1111.111
// 
// 1.   (1 * 0) + (1 * 0) + (0 * 0) + (1 * 0) + (1 * 0) + (0 * 0) + (0 * 0) = 0
//      (1 * 0) + (0 * 0) + (1 * 0) + (1 * 0) + (0 * 0) + (1 * 0) + (0 * 0) = 0
//      (0 * 0) + (1 * 0) + (1 * 0) + (1 * 0) + (0 * 0) + (0 * 0) + (1 * 0) = 0
// 
// 2.   (1 * 0) + (1 * 0) + (0 * 0) + (1 * 1) + (1 * 1) + (0 * 1) + (0 * 1) = 2
//      (1 * 0) + (0 * 0) + (1 * 0) + (1 * 1) + (0 * 1) + (1 * 1) + (0 * 1) = 2
//      (0 * 0) + (1 * 0) + (1 * 0) + (1 * 1) + (0 * 1) + (0 * 1) + (1 * 1) = 2
//
// 3.   (1 * 0) + (1 * 0) + (0 * 1) + (1 * 0) + (1 * 0) + (0 * 1) + (0 * 1) = 0
//      (1 * 0) + (0 * 0) + (1 * 1) + (1 * 0) + (0 * 0) + (1 * 1) + (0 * 1) = 2
//      (0 * 0) + (1 * 0) + (1 * 1) + (1 * 0) + (0 * 0) + (0 * 1) + (1 * 1) = 2

// 3 - 2
// 4 - 3
// 8 - 7

namespace BitError1 {

    // 'word' type is 16-bits
    //  - thats because we need 8 bits for "messageBites" and
    //   4 bits for parityBites, therefore
    //   4 starting bits are useless.
    const size messageBites = 8;
    const size parityBites = 4;
    const array<const word, parityBites> matrix {
        0b0000'0111'0110'1000,
        0b0000'1011'0011'0100,
        0b0000'1101'1001'0010,
        0b0000'1110'1100'0001,
    };

    auto RepairMessage(const word& message) {

    }

    auto EncodeMessage(const byte& data) {
        word message = 0b0000'0000'0000'0000;

        return message;
    }

    auto DecodeMessage(const word& message) {
        byte data = 0b0000'0000;

        return data;
    }

}

namespace BitError2 {

    // 'word' type is 16-bits
    //  - thats because we need 8 bits for "messageBites" and
    //   8 bits for parityBites, therefore theres
    //   0 starting bits that are useless. Look BitError1.
    const size messageBites = 8;
    const size parityBites = 8;
    const array<const word, parityBites> matrix {
        0b0111'1111'1000'0000,
        0b1011'1111'0100'0000,
        0b1101'1111'0010'0000,
        0b1110'1111'0001'0000,
        0b1111'0111'0000'1000,
        0b1111'1011'0000'0100,
        0b1111'1101'0000'0010,
        0b1111'1110'0000'0001,
    };

}


//uint32 wmain(uint64 argumentsCount, wchar** arguments)
uint32 main (uint64 argumentsCount, bchar** arguments) {

    // encode --method 1 -f sample.txt -o output1
    // decode --method 1 -f output1 -o output2.txt
    // code invalid ...

    // 1. Opracować kod korygujący pojedynczy błąd bitowy dla wiadomości ośmiobitowych(1 bajt)
    //  - data -> message -> data   // encoding-decoding
    //  - invalid -> data           // correcting method

    std::cout << "Hello World!\n";
    byte data = 0b0000'0000;
    word message = 0b1110'1110'1110'1110;

    std::cout << std::bitset<sizeof message * 8>(message);
}