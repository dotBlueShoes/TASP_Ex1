#include "Framework.hpp"

using bit = byte;

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
            result[i] = (data >> (7 - i)) & 1;
        }

        return result;
    }

    // min 16
    template <size resultBitsCount = 16, size dataOffset = 0>
    auto WordToArray(word data) {
        array<bit, resultBitsCount> result { 0 };

        for (size i = 0 + dataOffset; i < resultBitsCount + dataOffset; i++) {
            result[i] = (data >> (15 - i)) & 1;
        }

        return result;
    }

    auto ArrayToByte(array<bit, 8> data) {
        byte result(data[0]);

        for (size i = 1; i < data.size(); i++) {
            result <<= 1;
            result += data[i];
        }

        return result;
    }

    auto ArrayToWord(array<bit, 16> data) {
        word result(data[0]);

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

    auto Dot( // equal
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
}

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
    using col = array<bit, 8>;

    const array<row, 8> altMatrixH {
        row { 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        row { 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        row { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        row { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        row { 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
        row { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
        row { 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
        row { 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    };

    const array<col, 16> altMatrixH_T {
        col { 1, 1, 1, 0, 1, 1, 0, 1 },
        col { 1, 1, 0, 1, 1, 0, 1, 1 },
        col { 1, 0, 1, 0, 1, 0, 1, 1 },
        col { 1, 0, 0, 1, 0, 1, 1, 0 },
        col { 0, 1, 1, 0, 1, 0, 1, 0 },
        col { 0, 1, 0, 1, 0, 1, 0, 1 },
        col { 0, 0, 1, 1, 0, 0, 1, 1 },
        col { 0, 0, 0, 0, 1, 1, 1, 1 },
        col { 1, 0, 0, 0, 0, 0, 0, 0 },
        col { 0, 1, 0, 0, 0, 0, 0, 0 },
        col { 0, 0, 1, 0, 0, 0, 0, 0 },
        col { 0, 0, 0, 1, 0, 0, 0, 0 },
        col { 0, 0, 0, 0, 1, 0, 0, 0 },
        col { 0, 0, 0, 0, 0, 1, 0, 0 },
        col { 0, 0, 0, 0, 0, 0, 1, 0 },
        col { 0, 0, 0, 0, 0, 0, 0, 1 },
    };

    auto Encode(const byte& message) {
        word result = message;

        array<bit, 16> bitarr = Math::ByteToArray<16>(message);
        array<bit, 8> mulResult = Math::Dot(altMatrixH, bitarr);

        for (size i = 0; i < 8; i++) { 
            mulResult[i] = (byte)mulResult[i] % 2;
        }

        // DEBUG
        std::string output = "M: " + std::to_string(mulResult[0]);
        for (size i = 1; i < 8; i++) {
            output += ", ";
            output += std::to_string(mulResult[i]);
        }
        std::cout << output << std::endl;

        result <<= 8;
        result += Math::ArrayToByte(mulResult);

        return result;
    }

    auto Decode(const word& message) {
        array<bit, 16> bitarr = Math::WordToArray<16>(message);
        array<bit, 8> mulResult = Math::Dot(altMatrixH, bitarr);

        for (size i = 0; i < 8; i++) {
            mulResult[i] = (byte)mulResult[i] % 2;
        }

        // DEBUG
        std::string output = "M: " + std::to_string(mulResult[0]);
        for (size i = 1; i < 8; i++) {
            output += ", ";
            output += std::to_string(mulResult[i]);
        }
        std::cout << output << std::endl;

        // CORRECTING AND RETURNING
        {
            byte syndrome = Math::ArrayToByte(mulResult);

             
            if (!syndrome) { // See if correct eg. byte is all 0'es.
                return (byte)(Math::ArrayToWord(bitarr) >> 8);
            }

            // We can detect single error by enumerating through Transposed MatrixH
            //  if any is equal to our syndrome we can tell then at what index we need to flip the bit (^).

            { // See if it's a single ERROR. 
                for (size i = 0; i < altMatrixH_T.size(); i++) {
                    byte matrixRow = Math::ArrayToByte(altMatrixH_T[i]);
                    if (syndrome == matrixRow) {
                        //std::cout << std::to_string(i) << std::endl;
                        byte result = (byte)(Math::ArrayToWord(bitarr) >> 8);

                        // Important Note !
                        // right shift operator (>>) gets outside of the number when 
                        //  it is the parity byte that has the error.
                        //  However that doesn't matter and theres no real reason to branch that.

                        const byte mask = 0b1000'0000 >> i;
                        result ^= mask;
                        return result;
                    }
                }
            }

            // Because double bit error is essensially a sum of 2 rows of Transposed MatrixH
            //  what we need to do is to get all posible sums and then enumerate through those.

            { // See if it's a double ERROR.
                for (size i = 0; i < altMatrixH_T.size(); i++) {
                    const byte iRow = Math::ArrayToByte(altMatrixH_T[i]);
                    for (size j = 0; j < altMatrixH_T.size(); j++) {
                        const byte jRow = Math::ArrayToByte(altMatrixH_T[j]);
                        byte sum = jRow ^ iRow;
                        //std::cout << std::bitset<sizeof sum * 8>(sum) << std::endl;
                        if (syndrome == sum) {
                            //std::cout << std::to_string(i) << ", " << std::to_string(j) << std::endl;
                            byte result = (byte)(Math::ArrayToWord(bitarr) >> 8);

                            // Important Note !
                            // right shift operator (>>) gets outside of the number when 
                            //  it is the parity byte that has the error.
                            //  However that doesn't matter and theres no real reason to branch that.

                            const byte iMask = 0b1000'0000 >> i;
                            const byte jMask = 0b1000'0000 >> j;

                            result = (result ^ iMask) ^ jMask;
                            return result;
                        }
                    }
                }
            }

            // If more then 2 return ERROR data signalizing the ERROR.
            return (byte)0b0;
        }
    }

    auto SimulateSingleError(word& message) {
        const word errorMask(0b0001'0000'0000'0000);
        message ^= errorMask;
    }

    auto SimulateDoubleError(word& message) {
        const word errorMask(0b0010'0000'0010'0000);
        message ^= errorMask;
    }

    auto SimulateTripleError(word& message) {
        const word errorMask(0b0000'0100'0100'0010);
        message ^= errorMask;
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

        for (auto& message : inputBuffer) {
            // ENCODING
            encodedMessage = Encode(message);
            // WRITE
            resultFile << (byte)(encodedMessage >> 8) << (byte)(encodedMessage);
        }

        resultFile.close();
    }

    auto ReadAndDecode(
        const char* const originFilePath,
        const char* const outputFilePath
    ) {
        std::ifstream originFile(originFilePath, std::ios::binary);
        std::ofstream resultFile(outputFilePath, std::ios::binary);

        // READ
        std::vector<byte> inputBuffer(std::istreambuf_iterator<char>(originFile), {});
        originFile.close();

        
        byte decodedMessage = 'a';
        word wholeMessage;

        // buffer is per byte therefore we need to read 2 bytes and move by 2 bytes.
        for (size i = 0; i < inputBuffer.size(); i += 2) {

            // Parse into one.
            wholeMessage = inputBuffer[i];
            wholeMessage <<= 8;
            wholeMessage += inputBuffer[i + 1];

            // Decode
            decodedMessage = Decode(wholeMessage);

            // Write
            resultFile << decodedMessage;
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
    //    std::cout << "encoding..." << std::endl;
    //    PDECC::ReadAndEncode(iFilePath, oFilePath);
    //} else if (strcmp(arguments[1], "decode") == 0) {
    //    std::cout << "decoding..." << std::endl;
    //    PDECC::ReadAndDecode(oFilePath, rFilePath);
    //}

            // TODO
            // 4. understand again
            // 5. console
            // 6. window
            // 7. try implementing 1 error

    const word correctMessage = 0b0000'1111'0000'0011;
    const word error1Message = 0b0000'1111'0001'0011;
    const word error2Message = 0b0001'1111'0000'0011;
    const word error3Message = 0b0001'1111'0001'0011;
    const byte data = 0b0000'1111;

    word resultEncoded = PDECC::Encode(data);
    byte resultCorrect = PDECC::Decode(correctMessage);
    byte resultError1 = PDECC::Decode(error1Message);
    byte resultError2 = PDECC::Decode(error2Message);
    byte resultError3 = PDECC::Decode(error3Message);

    std::cout << "\n" <<
        "RE: " << std::bitset<sizeof resultEncoded * 8>(resultEncoded) << '\n' <<
        "RC: " << std::bitset<sizeof resultCorrect * 8>(resultCorrect) << '\n' <<
        "R1: " << std::bitset<sizeof resultError1 * 8>(resultError1) << '\n' <<
        "R2: " << std::bitset<sizeof resultError2 * 8>(resultError2) << '\n' <<
        "R3: " << std::bitset<sizeof resultError3 * 8>(resultError3) << std::endl;
    
    return 0;
}

