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

namespace Math {

    const word m1 = 0b0101010101010101; //binary: 0101...
    const word m2 = 0b0011001100110011; //binary: 00110011..
    const word m4 = 0b0000111100001111; //binary:  4 zeros,  4 ones ...
    const word m8 = 0b0000000011111111; //binary:  8 zeros,  8 ones ...
    //const byte m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
    //const byte m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones

    word CountSetBits(word x) {
        x = (x & m1) + ((x >> 1) & m1);
        x = (x & m2) + ((x >> 2) & m2);
        x = (x & m4) + ((x >> 4) & m4);
        x = (x & m8) + ((x >> 8) & m8);
        //x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
        return x;
    }

    //template <class T, size length>
    //using Vector = array<T, length>;
    //
    //template <class T, size lengthX, size lengthY>
    //using Matrix = array<array<T, lengthX>, lengthY>;
    //
    //template <class T, size lengthX, size lengthY>
    //void Multiply(
    //    const Matrix<T, lengthX, lengthY>& matrix,
    //    const Vector<T, lengthX>& vector
    //) {
    //    Vector<T, lengthX> result {0};
    //
    //    for (size y = 0; y < matrix.size(); y++) {
    //        for (size x = 0; x < matrix.data().size(); x++) {
    //            result[0] += 10;
    //        }
    //    }
    //
    //    return result;
    //}

    // template <class length>
    // using BitVector = length;
    // 
    // template <class lengthX, size lengthY>
    // using BitMatrix = array<lengthX, lengthY>;
    // 
    // template <class lengthX, size lengthY>
    // void Multiply(
    //     const BitMatrix<lengthX, lengthY>& matrix,
    //     const BitVector<lengthX>& vector
    // ) {
    //     Vector<T, lengthX> result { 0 };
    // 
    //     for (size y = 0; y < matrix.size(); y++) {
    //         for (size x = 0; x < matrix.data().size(); x++) {
    //             result[0] += 10;
    //         }
    //     }
    // 
    //     return result;
    // }

}

namespace BitError1 {

    // Hamming Code (11/4) but we only use (8/4)

    // S3 S2 S1 S0 | ERROR
    // ----------------------
    //  0  0  0  0 | No ERROR
    //  0  0  0  1 | P0             P0 = D0^D1^D3^D4^D6
    //  0  0  1  0 | P1             P1 = D0^D2^D3^D5^D6
    //  0  0  1  1 | D0             P2 = D1^D2^D3^D7
    //  0  1  0  0 | P2             P3 = D4^D5^D6^D7
    //  0  1  0  1 | D1
    //  0  1  1  0 | D2
    //  0  1  1  1 | D3
    //  1  0  0  0 | P3
    //  1  0  0  1 | D4
    //  1  0  1  0 | D5
    //  1  0  1  1 | D6
    //  1  1  0  0 | D7
    //  1  1  0  1 | 
    //  1  1  1  0 | 
    //  1  1  1  1 | 

    // 'word' type is 16-bits
    //  - thats because we need 8 bits for "messageBites" and
    //   4 bits for parityBites, therefore
    //   4 starting bits are useless.
    const size messageBites = 8;
    const size parityBites = 4;
    const array<const word, parityBites> matrixH {
        0b0000'0111'0110'1000,
        0b0000'1011'0011'0100,
        0b0000'1101'1001'0010,
        0b0000'1110'1100'0001,
    };

    auto RepairMessage(const word& message) {

    }

    auto EncodeMessage(const byte& data) {
        const word preParityBits = 0b0000'1111;

        word message = data << 4;
        message += preParityBits;

        // Equation of x, y, z, w.
        const word equationX = message & BitError1::matrixH[0];
        const word equationY = message & BitError1::matrixH[1];
        const word equationZ = message & BitError1::matrixH[2];
        const word equationW = message & BitError1::matrixH[3];

        const word parityX = (Math::CountSetBits(equationX) - 1) & 1;
        const word parityY = (Math::CountSetBits(equationY) - 1) & 1;
        const word parityZ = (Math::CountSetBits(equationZ) - 1) & 1;
        const word parityW = (Math::CountSetBits(equationW) - 1) & 1;

        message = data;
        message <<= 1;
        message += parityX;
        message <<= 1;
        message += parityY;
        message <<= 1;
        message += parityZ;
        message <<= 1;
        message += parityW;

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
    const array<const word, parityBites> matrixH {
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
    
    byte data = 0b1010'1010;
    word endcodedMessage = BitError1::EncodeMessage(data);

    std::cout << std::bitset<sizeof endcodedMessage * 8>(endcodedMessage) << std::endl;
    //std::cout << std::bitset<sizeof result * 8>(result) << std::endl;

    //std::cout << std::to_string(parityX) << std::endl;
    //std::cout << std::to_string(parityY) << std::endl;
    //std::cout << std::to_string(parityZ) << std::endl;
    //std::cout << std::to_string(parityW) << std::endl;

    //std::cout << std::bitset<sizeof resultX * 8>(resultX) << std::endl;
    //std::cout << std::bitset<sizeof resultY * 8>(resultY) << std::endl;
    //std::cout << std::bitset<sizeof resultZ * 8>(resultZ) << std::endl;
    //std::cout << std::bitset<sizeof resultW * 8>(resultW) << std::endl;

    //std::cout << std::to_string(countSetBits(resultX)) << std::endl;
    //std::cout << std::to_string(countSetBits(resultY)) << std::endl;
    //std::cout << std::to_string(countSetBits(resultZ)) << std::endl;
    //std::cout << std::to_string(countSetBits(resultW)) << std::endl;
}