#include "Framework.hpp"

// https://en.wikipedia.org/wiki/Hamming_weight

using bit = byte;

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

namespace BitMatrix {

    template<size bitCount>
    using BitMatrix = array<bit, bitCount>;

}

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

    // min 8
    template <size resultBitsCount = 8, size dataOffset = 0> 
    auto ByteToArray(byte data) {
        array<bit, resultBitsCount> result { 0 };

        for (size i = 0 + dataOffset; i < resultBitsCount + dataOffset; i++) {
            result[i] = (data >> 7 - i) & 1;
        }

        return result;
    }

    // min 16
    template <size resultBitsCount = 16, size dataOffset = 0>
    auto WordToArray(word data) {
        array<bit, resultBitsCount> result { 0 };

        for (size i = 0 + dataOffset; i < resultBitsCount + dataOffset; i++) {
            result[i] = (data >> 15 - i) & 1;
        }

        return result;
    }

    auto ArrayToByte(array<bit, 8> data) {
        byte result (data[0]);

        for (size i = 1; i < data.size(); i++) {
            result <<= 1;
            result += data[i];
        }

        return result;
    }

    auto ArrayToWord(array<bit, 16> data) {
        word result (data[0]);

        for (size i = 1; i < data.size(); i++) {
            result <<= 1;
            result += data[i];
        }

        return result;
    }

    auto Dot( // row-col relation
        const array<array<bit, 16>, 8>& a,
        const array<bit, 16>& b
    ) {
        array<bit, 8> result { 0 };

        for (size i = 0; i < 8; i++) {
            result[i] =
                a[i][0X0] * b[0X0] + a[i][0X1] * b[0X1] + a[i][0X2] * b[0X2] + a[i][0X3] * b[0X3] +
                a[i][0X4] * b[0X4] + a[i][0X5] * b[0X5] + a[i][0X6] * b[0X6] + a[i][0X7] * b[0X7] +
                a[i][0X8] * b[0X8] + a[i][0X9] * b[0X9] + a[i][0XA] * b[0XA] + a[i][0XB] * b[0XB] +
                a[i][0XC] * b[0XC] + a[i][0XD] * b[0XD] + a[i][0XE] * b[0XE] + a[i][0XF] * b[0XF];
        }

        return result;
    }

    auto Dot ( // equal
        const array<array<bit, 16>, 16>& a,
        const array<bit, 16>& b
    ) {
        array<bit, 16> result { 0 };

        for (size i = 0; i < 16; i++) {
            result[i] = 
                b[i] * a[i][0X0] + b[i] * a[i][0X1] + b[i] * a[i][0X2] + b[i] * a[i][0X3] +
                b[i] * a[i][0X4] + b[i] * a[i][0X5] + b[i] * a[i][0X6] + b[i] * a[i][0X7] +
                b[i] * a[i][0X8] + b[i] * a[i][0X9] + b[i] * a[i][0XA] + b[i] * a[i][0XB] +
                b[i] * a[i][0XC] + b[i] * a[i][0XD] + b[i] * a[i][0XE] + b[i] * a[i][0XF];
        }

        return result;
        // x * a + y * b + z * c + w * d;
        // x * e + y * f + z * g + w * h;
        // x * i + y * j + z * k + w * l;
        // x * m + y * n + z * o + w * p
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

//namespace BitError1 {
//
//    // Hamming Code (11/4) but we only use (8/4)
//
//    // S3 S2 S1 S0 | ERROR
//    // ----------------------
//    //  0  0  0  0 | No ERROR
//    //  0  0  0  1 | P0             P0 = D0^D1^D3^D4^D6
//    //  0  0  1  0 | P1             P1 = D0^D2^D3^D5^D6
//    //  0  0  1  1 | D0             P2 = D1^D2^D3^D7
//    //  0  1  0  0 | P2             P3 = D4^D5^D6^D7
//    //  0  1  0  1 | D1
//    //  0  1  1  0 | D2
//    //  0  1  1  1 | D3
//    //  1  0  0  0 | P3
//    //  1  0  0  1 | D4
//    //  1  0  1  0 | D5
//    //  1  0  1  1 | D6
//    //  1  1  0  0 | D7
//    //  1  1  0  1 | 
//    //  1  1  1  0 | 
//    //  1  1  1  1 | 
//
//    // 'word' type is 16-bits
//    //  - thats because we need 8 bits for "messageBites" and
//    //   4 bits for parityBites, therefore
//    //   4 starting bits are useless.
//    const size messageBites = 8;
//    const size parityBites = 4;
//    const array<const word, parityBites> matrixH {
//        0b0000'0111'0110'1000,
//        0b0000'1011'0011'0100,
//        0b0000'1101'1001'0010,
//        0b0000'1110'1100'0001,
//    };
//
//    auto EncodeMessage(const byte& data) {
//        const word preParityBits = 0b0000'0000'0000'1111;
//
//        word message = data << 4;
//        message += preParityBits;
//
//        // Equation of x, y, z, w.
//        const word equationX = message & matrixH[0];
//        const word equationY = message & matrixH[1];
//        const word equationZ = message & matrixH[2];
//        const word equationW = message & matrixH[3];
//
//        // -1, because one bit stands for said x or y, z, w thats inside equation.
//        const word parityX = (Math::CountSetBits(equationX) - 1) & 1;
//        const word parityY = (Math::CountSetBits(equationY) - 1) & 1;
//        const word parityZ = (Math::CountSetBits(equationZ) - 1) & 1;
//        const word parityW = (Math::CountSetBits(equationW) - 1) & 1;
//
//        message = data;
//        message <<= 1;
//        message += parityX;
//        message <<= 1;
//        message += parityY;
//        message <<= 1;
//        message += parityZ;
//        message <<= 1;
//        message += parityW;
//
//        return message;
//    }
//
//    auto DecodeMessage(const word& message) {
//        // Equation of x, y, z, w.
//        const word equationX = message & matrixH[0];
//        const word equationY = message & matrixH[1];
//        const word equationZ = message & matrixH[2];
//        const word equationW = message & matrixH[3];
//
//        // Check if equal to 0
//        const word parityX = Math::CountSetBits(equationX) & 1;
//        const word parityY = Math::CountSetBits(equationY) & 1;
//        const word parityZ = Math::CountSetBits(equationZ) & 1;
//        const word parityW = Math::CountSetBits(equationW) & 1;
//
//        if (!parityX && !parityY && !parityZ && !parityW) {
//            return (byte)(message >> 4);
//        } else {
//            std::cout << "Message error encountered!" << std::endl;
//
//            word errorIndex = parityX;
//            errorIndex <<= 1;
//            errorIndex += parityY;
//            errorIndex <<= 1;
//            errorIndex += parityZ;
//            errorIndex <<= 1;
//            errorIndex += parityW;
//
//            const word mask = 0b0000'0000'0000'0001 << errorIndex - 1;
//            byte data = (message ^ mask) >> 4;
//
//            //std::cout << std::bitset<sizeof errorIndex * 8>(errorIndex) << std::endl;
//            //std::cout << "result: " << std::bitset<sizeof message * 8>(message) << std::endl;
//
//            return data;
//        }
//
//    }
//
//}

//namespace BitError2 {
//
//    // 'word' type is 16-bits
//    //  - thats because we need 8 bits for "messageBites" and
//    //   8 bits for parityBites, therefore theres
//    //   0 starting bits that are useless. Look BitError1.
//    const size messageBites = 8;
//    const size parityBites = 8;
//    //const array<const word, parityBites> matrixH {
//    //    0b0111'1111'1000'0000,
//    //    0b1011'1111'0100'0000,
//    //    0b1101'1111'0010'0000,
//    //    0b1110'1111'0001'0000,
//    //    0b1111'0111'0000'1000,
//    //    0b1111'1011'0000'0100,
//    //    0b1111'1101'0000'0010,
//    //    0b1111'1110'0000'0001,
//    //};
//
//    const array<const word, parityBites> matrixH {
//        0b1110'0111'1000'0000,
//        0b1101'1111'0100'0000,
//        0b1010'1001'0010'0000,
//        0b0110'1011'0001'0000,
//        0b1001'0110'0000'1000,
//        0b0101'0101'0000'0100,
//        0b0011'0011'0000'0010,
//        0b0000'1111'0000'0001,
//    };
//	
//	//const array<const word, parityBites> matrixH {
//    //    0b1011'1100'1000'0000,
//    //    0b0111'1001'0100'0000,
//    //    0b1110'1000'0010'0000,
//    //    0b1001'1111'0001'0000,
//    //    0b0110'0111'0000'1000,
//    //    0b1101'1011'0000'0100,
//    //    0b0001'1011'0000'0010,
//    //    0b0011'1110'0000'0001,
//    //}; // !!!!
//
//    //const array<const word, parityBites> matrixH {
//    //    0b1111'1111'1000'0000,
//    //    0b1101'1111'0100'0000,
//    //    0b1101'1101'0010'0000,
//    //    0b1101'0101'0001'0000,
//    //    0b1001'0101'0000'1000,
//    //    0b1001'0100'0000'0100,
//    //    0b1001'0000'0000'0010,
//    //    0b1000'0000'0000'0001,
//    //};
//
//    auto EncodeMessage(const byte& data) {
//        const word preParityBits = 0b0000'0000'1111'1111;
//
//        word message = data << 8;
//        message += preParityBits;
//
//        // Equation of x, y, z, w.
//        const word equationX = message & matrixH[0];
//        const word equationY = message & matrixH[1];
//        const word equationZ = message & matrixH[2];
//        const word equationW = message & matrixH[3];
//        //const word equationU = message & matrixH[0];
//        //const word equationI = message & matrixH[1];
//        //const word equationO = message & matrixH[2];
//        //const word equationP = message & matrixH[3];
//        const word equationU = message & matrixH[4];
//        const word equationI = message & matrixH[5];
//        const word equationO = message & matrixH[6];
//        const word equationP = message & matrixH[7];
//
//        // -1, because one bit stands for said x or y, z, w thats inside equation.
//        const word parityX = (Math::CountSetBits(equationX) - 1) & 1;
//        const word parityY = (Math::CountSetBits(equationY) - 1) & 1;
//        const word parityZ = (Math::CountSetBits(equationZ) - 1) & 1;
//        const word parityW = (Math::CountSetBits(equationW) - 1) & 1;
//        const word parityU = (Math::CountSetBits(equationU) - 1) & 1;
//        const word parityI = (Math::CountSetBits(equationI) - 1) & 1;
//        const word parityO = (Math::CountSetBits(equationO) - 1) & 1;
//        const word parityP = (Math::CountSetBits(equationP) - 1) & 1;
//
//        message = data;
//        message <<= 1;
//        message += parityX;
//        message <<= 1;
//        message += parityY;
//        message <<= 1;
//        message += parityZ;
//        message <<= 1;
//        message += parityW;
//        message <<= 1;
//        message += parityU;
//        message <<= 1;
//        message += parityI;
//        message <<= 1;
//        message += parityO;
//        message <<= 1;
//        message += parityP;
//
//        std::cout <<
//            "equation: " << std::bitset<sizeof message * 8>(message) << '\n' <<
//            "eqX: " << std::bitset<sizeof equationX * 8>(equationX) << '\n' <<
//            "eqY: " << std::bitset<sizeof equationY * 8>(equationY) << '\n' <<
//            "eqZ: " << std::bitset<sizeof equationZ * 8>(equationZ) << '\n' <<
//            "eqW: " << std::bitset<sizeof equationW * 8>(equationW) << '\n' <<
//            "eqU: " << std::bitset<sizeof equationU * 8>(equationU) << '\n' <<
//            "eqI: " << std::bitset<sizeof equationI * 8>(equationI) << '\n' <<
//            "eqO: " << std::bitset<sizeof equationO * 8>(equationO) << '\n' <<
//            "eqP: " << std::bitset<sizeof equationP * 8>(equationP) << std::endl;
//
//        return message;
//    }
//
//    auto DecodeMessage(const word& message) {
//
//        // Equation of x, y, z, w.
//        const word equationX = message & matrixH[0];
//        const word equationY = message & matrixH[1];
//        const word equationZ = message & matrixH[2];
//        const word equationW = message & matrixH[3];
//        const word equationU = message & matrixH[4];
//        const word equationI = message & matrixH[5];
//        const word equationO = message & matrixH[6];
//        const word equationP = message & matrixH[7];
//        //const word equationU = message & matrixH[0];
//        //const word equationI = message & matrixH[1];
//        //const word equationO = message & matrixH[2];
//        //const word equationP = message & matrixH[3];
//
//        // Check if equal to 0
//        const word parityX = Math::CountSetBits(equationX) & 1;
//        const word parityY = Math::CountSetBits(equationY) & 1;
//        const word parityZ = Math::CountSetBits(equationZ) & 1;
//        const word parityW = Math::CountSetBits(equationW) & 1;
//        const word parityU = Math::CountSetBits(equationU) & 1;
//        const word parityI = Math::CountSetBits(equationI) & 1;
//        const word parityO = Math::CountSetBits(equationO) & 1;
//        const word parityP = Math::CountSetBits(equationP) & 1;
//
//        std::cout <<
//            "message: " << std::bitset<sizeof message * 8>(message) << '\n' <<
//            "eqX: " << std::bitset<sizeof equationX * 8>(equationX) << '\n' <<
//            "eqY: " << std::bitset<sizeof equationY * 8>(equationY) << '\n' <<
//            "eqZ: " << std::bitset<sizeof equationZ * 8>(equationZ) << '\n' <<
//            "eqW: " << std::bitset<sizeof equationW * 8>(equationW) << '\n' << // std::endl;
//            "eqU: " << std::bitset<sizeof equationU * 8>(equationU) << '\n' <<
//            "eqI: " << std::bitset<sizeof equationI * 8>(equationI) << '\n' <<
//            "eqO: " << std::bitset<sizeof equationO * 8>(equationO) << '\n' <<
//            "eqP: " << std::bitset<sizeof equationP * 8>(equationP) << std::endl;
//
//        std::cout <<
//            "message: " << std::bitset<sizeof message * 8>(message) << '\n' <<
//            "eqX: " << std::bitset<sizeof parityX * 8>(parityX) << '\n' <<
//            "eqY: " << std::bitset<sizeof parityY * 8>(parityY) << '\n' <<
//            "eqZ: " << std::bitset<sizeof parityZ * 8>(parityZ) << '\n' <<
//            "eqW: " << std::bitset<sizeof parityW * 8>(parityW) << '\n' << // std::endl;
//            "eqU: " << std::bitset<sizeof parityU * 8>(parityU) << '\n' <<
//            "eqI: " << std::bitset<sizeof parityI * 8>(parityI) << '\n' <<
//            "eqO: " << std::bitset<sizeof parityO * 8>(parityO) << '\n' <<
//            "eqP: " << std::bitset<sizeof parityP * 8>(parityP) << std::endl;
//
//        
//        word parity = parityX;
//        parity <<= 1;
//        parity += parityY;
//        parity <<= 1;
//        parity += parityZ;
//        parity <<= 1;
//        parity += parityW;
//        parity <<= 1;
//        parity += parityU;
//        parity <<= 1;
//        parity += parityI;
//        parity <<= 1;
//        parity += parityO;
//        parity <<= 1;
//        parity += parityP;
//
//        if (!parity) {
//            return (byte)(message >> 8);
//        } else {
//
//            //const word error_mask_1 = 0b0000'0000'1000'0000;
//            //const word error_mask_2 = 0b0000'0000'0100'0000;
//            //const word error_mask_3 = 0b0000'0000'0010'0000;
//            //const word error_mask_4 = 0b0000'0000'0001'0000;
//            //const word error_mask_5 = 0b0000'0000'0000'1000;
//            //const word error_mask_6 = 0b0000'0000'0000'0100;
//            //const word error_mask_7 = 0b0000'0000'0000'0010;
//            //const word error_mask_8 = 0b0000'0000'0000'0001;
//            //
//            //const word error_mask_9 = 0b0000'0000'1000'0000;
//            //const word error_mask_10 = 0b0000'0000'0100'0000;
//            //const word error_mask_11 = 0b0000'0000'0010'0000;
//            //const word error_mask_12 = 0b0000'0000'0001'0000;
//            //const word error_mask_13 = 0b0000'0000'0000'1000;
//            //const word error_mask_14 = 0b0000'0000'0000'0100;
//            //const word error_mask_15 = 0b0000'0000'0000'0010;
//            //const word error_mask_16 = 0b0000'0000'0000'0001;
//
//            if (parity > 2) {
//                std::cout << "more then 2 errors" << std::endl;
//                return (byte)(0b00000000);
//            }
//            else if (parity > 1) {
//                std::cout << "2 errors" << std::endl;
//
//                // Jeśli zamienie 1 i z kolejnym obiegiem powie o istnieniu 3 błędów.
//                // Jeśli zamienie 1 i z kolejnym obiegiem powie o istnieniu 1 błędu.
//
//            }
//            else if (parity > 0) {
//                std::cout << "single error" << std::endl;
//
//                word errorIndex = parityX;
//                    errorIndex <<= 1;
//                    errorIndex += parityY;
//                    errorIndex <<= 1;
//                    errorIndex += parityZ;
//                    errorIndex <<= 1;
//                    errorIndex += parityW;
//                    errorIndex <<= 1;
//                    errorIndex += parityU;
//                    errorIndex <<= 1;
//                    errorIndex += parityI;
//                    errorIndex <<= 1;
//                    errorIndex += parityO;
//                    errorIndex <<= 1;
//                    errorIndex += parityP;
//
//                const word mask = 0b0000'0000'0000'0001 << errorIndex - 1;
//                byte data = (message ^ mask) >> 4;
//                return data;
//            }
//
//            //if (!parityX && !parityY && !parityZ && !parityW) {
//            //    std::cout << "1" << std::endl;
//            //}
//            //
//            //if (!parityU && !parityI && !parityO && !parityP) {
//            //    std::cout << "2" << std::endl;
//            //}
//
//            return (byte)(0b00000000);
//        }
//        //    std::cout << "Message error encountered!" << std::endl;
//        //
//        //    word errorIndex = parityX;
//        //    errorIndex <<= 1;
//        //    errorIndex += parityY;
//        //    errorIndex <<= 1;
//        //    errorIndex += parityZ;
//        //    errorIndex <<= 1;
//        //    errorIndex += parityW;
//        //
//        //    const word mask = 0b0000'0000'0000'0001 << errorIndex - 1;
//        //    byte data = (message ^ mask) >> 4;
//        //
//        //    //std::cout << std::bitset<sizeof errorIndex * 8>(errorIndex) << std::endl;
//        //    //std::cout << "result: " << std::bitset<sizeof message * 8>(message) << std::endl;
//        //
//        //    return data;
//        //}
//
//    }
//
//
//}

//namespace Data {
//
//    auto Encode(
//        const char* const originFilePath,
//        const char* const outputFilePath
//    ) {
//        std::ifstream originFile(originFilePath, std::ios::binary);
//        std::ofstream resultFile(outputFilePath, std::ios::binary);
//
//        std::vector<byte> inputBuffer(std::istreambuf_iterator<char>(originFile), {});
//        originFile.close();
//
//        //std::cerr << inputBuffer.size() << std::endl;
//        // Initialize buffer with the size of input but for ( word type ).
//        //std::vector<word> outputBuffer(inputBuffer.size());
//        word encodedMessage;
//
//        //resultFile << (byte)(0b00000000);
//
//        for (const auto& value : inputBuffer) {
//            encodedMessage = BitError1::EncodeMessage(value);
//            //outputBuffer.push_back(encodedMessage);
//            resultFile << (byte)(encodedMessage >> 8) << (byte)(encodedMessage);    // File output.
//            //std::cout << "Value: " << std::bitset<sizeof value * 8>(value) << std::endl;
//            //std::cout << "Encoded Message: " << std::bitset<sizeof encodedMessage * 8>(encodedMessage) << std::endl;
//        }
//
//        resultFile.close();
//    }
//
//    auto Decode(
//        const char* const originFilePath,
//        const char* const outputFilePath
//    ) {
//        std::ifstream originFile(originFilePath, std::ios::binary);
//        std::ofstream resultFile(outputFilePath, std::ios::binary);
//
//        //originFile.get();
//
//        std::vector<byte> inputBuffer(std::istreambuf_iterator<char>(originFile), {});
//        originFile.close();
//
//        word encodedMessage;
//        byte decodedMessage;
//
//        //std::cout << inputBuffer.size() << std::endl;
//
//        for (size i = 0; i < inputBuffer.size(); i += 2) {
//
//            encodedMessage = inputBuffer[i];
//            encodedMessage <<= 8;
//            encodedMessage += inputBuffer[i + 1];
//
//            decodedMessage = BitError1::DecodeMessage(encodedMessage);
//
//            //std::cout << "Decoded Message:: " << std::bitset<sizeof encodedMessage * 8>(encodedMessage) << std::endl;
//            //std::cout << "Encoded Message: " << std::bitset<sizeof decodedMessage * 8>(decodedMessage) << std::endl;
//
//            resultFile << decodedMessage;    // File output.
//        }
//
//        resultFile.close();
//    }
//
//}



//uint32 wmain(uint64 argumentsCount, wchar** arguments)
//uint32 main (uint64 argumentsCount, bchar** arguments) {
//
//    // encode --method 1 -f sample.txt -o output1
//    // decode --method 1 -f output1 -o output2.txt
//    // encode invalid ...
//
//    // IO
//    //const auto iFilePath("nocoded.txt");
//    //const auto oFilePath("encoded.txt");
//    //const auto rFilePath("decoded.txt");
//    //
//    //if (argumentsCount <= 1) return 1;
//    //
//    //if (strcmp(arguments[1], "encode") == 0) {
//    //    std::cout << "encoding..." << std::endl;
//    //    Data::Encode(iFilePath, oFilePath);
//    //} else if (strcmp(arguments[1], "decode") == 0) {
//    //    std::cout << "decoding..." << std::endl;
//    //    Data::Decode(oFilePath, rFilePath);
//    //}
//        
//    
//    
//    // { // No IO. 1
//    //     const word errorMessage = 0b0000'1010'1010'0100;
//    //     byte data = 0b1010'1010;
//    //     word encodedMessage = BitError1::EncodeMessage(data);
//    //     byte decodedMessage = BitError1::DecodeMessage(encodedMessage);
//    //     byte decodedErrorMessage = BitError1::DecodeMessage(errorMessage);
//    // 
//    // 
//    //     std::cout << "Encoded Message: " << std::bitset<sizeof encodedMessage * 8>(encodedMessage) << std::endl;
//    //     std::cout << "Decoded Message: " << std::bitset<sizeof decodedMessage * 8>(decodedMessage) << std::endl;
//    //     std::cout << "Decoded Error Message: " << std::bitset<sizeof decodedErrorMessage * 8>(decodedErrorMessage) << std::endl;
//    // }
//
//    { // No IO. 2
//
//        // const word errorMessage = 0b1010'1010'0100'1010; // ????????
//        //const word errorMessage = 0b1010'1010'1011'0101; // HERE
//        //const word errorMessage = 0b1010'1001'1010'1010;
//
//
//
//        //const word errorMessage = 0b1010'1010'1010'0000;
//        const word errorMessage = 0b1010'1010'1111'0000;
//
//        byte data = 0b1010'1010;
//        word encodedMessage = BitError2::EncodeMessage(data);
//        byte decodedMessage = BitError2::DecodeMessage(encodedMessage);
//        std::cout << "ERROR MSG" << std::endl;
//        byte decodedErrorMessage = BitError2::DecodeMessage(errorMessage);
//    
//    
//        std::cout << "Encoded Message: " << std::bitset<sizeof encodedMessage * 8>(encodedMessage) << std::endl;
//        std::cout << "Decoded Message: " << std::bitset<sizeof decodedMessage * 8>(decodedMessage) << std::endl;
//        std::cout << "Decoded Error Message: " << std::bitset<sizeof decodedErrorMessage * 8>(decodedErrorMessage) << std::endl;
//    }
//    
//}

namespace ParitySingleErrorCorrectingCode {

    // 'word' type is 16-bits
    //  - thats because we need 8 bits for "messageBites" and
    //   4 bits for parityBites, therefore
    //   4 starting bits are useless.
    const size messageBites = 8;
    const size parityBites = 4;

    // Matrix that satisfies two conditions:
    // - there are no repeating rows
    // - each row has unique sum of all of its values
    const array<const word, parityBites> matrixH {
        0b0000'0111'0110'1000,
        0b0000'1011'0011'0100,
        0b0000'1101'1001'0010,
        0b0000'1110'1100'0001,
    };

}

namespace ParityDoubleErrorCorrectingCode {

    // Żadna z dwóch dowolnych kolumn tej macierzy nie może tworzyć innej kolumny
    // Wtedy poprawa 2 błędów jest możliwa
    // taka częściowa liniowa niezależność
    // do osiągnięcia tego minimum to 8 bitów parzystości dla 8 bitowej wiadomości
    // dla 2 błędów będzie to suma kolumn
    // więc musisz porównać sumy wszystkich kolumn i znaleźć te kolumny które stworzą taką sumę

    // constant values, improves readability
    const int parityBites = 8;
    //const int number_of_bits_in_byte = 8;

    // Matrix which satisfies two conditions :
    // - there are no repeating rows
    // - each row has unique sum of all of its values
    const array<const word, parityBites> matrixH {
        0b1111'0000'1000'0000,
        0b1100'1100'0100'0000,
        0b1010'1010'0010'0000,
        0b0101'0110'0001'0000,
        0b1110'1001'0000'1000,
        0b1001'0101'0000'0100,
        0b0111'1011'0000'0010,
        0b1110'0111'0000'0001,
    };

    using row = array<bit, 8 + 8>;
    const array<row, 8> altMatrixH {
        //row { 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        //row { 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        //row { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        //row { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        //row { 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
        //row { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
        //row { 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
        //row { 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
        row { 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        row { 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        row { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        row { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        row { 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
        row { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
        row { 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
        row { 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    };

    auto Encode(const byte& message) {
        word result = 0;

        array<bit, 16> bytearr = Math::ByteToArray<16>(message);
        array<bit, 8> mulResult = Math::Dot(altMatrixH, bytearr);

        for (size i = 0; i < 8; i++) { 
            mulResult[i] = (byte)mulResult[i] % 2;
        }

        std::string outputA = "W: " + std::to_string((byte)bytearr[0]);
        for (size i = 1; i < 8; i++) {
            outputA += ", ";
            outputA += std::to_string((byte)bytearr[i]);
        }
        std::cout << outputA << std::endl;

        std::string output = "M: " + std::to_string((byte)mulResult[0]);
        for (size i = 1; i < 8; i++) {
            output += ", ";
            output += std::to_string((byte)mulResult[i]);
        }
        std::cout << output << std::endl;

        return result;
    }

    // read file bytes, encode
    // and save result to a different file
    auto ReadAndEncode(
        const char* const originFilePath,
        const char* const outputFilePath
    ) {

        std::ifstream originFile(originFilePath, std::ios::binary);
        std::ofstream resultFile(outputFilePath, std::ios::binary);

        // READ
        std::vector<byte> inputBuffer(std::istreambuf_iterator<char>(originFile), {});
        originFile.close();

        word encodedMessage;

        //for (size i = 0; i < inputBuffer.size())

        for (auto& message : inputBuffer) {
            // ENCODING
            encodedMessage = Encode(message);
            // WRITE
            resultFile << (byte)(encodedMessage >> 8) << (byte)(encodedMessage);
        }

        resultFile.close();
    }

}

namespace PSECC = ParitySingleErrorCorrectingCode;
namespace PDECC = ParityDoubleErrorCorrectingCode;


uint32 main(uint64 argumentsCount, bchar** arguments) {
    
    const auto iFilePath("nocoded.txt");
    const auto oFilePath("encoded.txt");
    const auto rFilePath("decoded.txt");

    //byte a = 0b0000'1111;
    //word b = 0b1111'0000'1111'0000;
    //
    //array<bool, 8> byteToArrayResult = Math::ByteToArray(a);
    //array<bool, 16> wordToArrayResult = Math::WordToArray(b);
    //byte aResult = Math::ArrayToByte(byteToArrayResult);
    //word bResult = Math::ArrayToWord(wordToArrayResult);

    //if (argumentsCount <= 1) return 1;
    
    //if (strcmp(arguments[1], "encode") == 0) {
        std::cout << "encoding..." << std::endl;
        PDECC::ReadAndEncode(iFilePath, oFilePath);
    //} else if (strcmp(arguments[1], "decode") == 0) {
    //    std::cout << "decoding..." << std::endl;
    //    //PDECC::Decode(oFilePath, rFilePath);
    //}
    
    return 0;
}

