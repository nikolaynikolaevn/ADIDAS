/* decode_functions.c */

#include <stdio.h>
#include <stdint.h>
#include "decode_functions.h"

#define HI_NIBBLE(b) (((b) & 0x78) << 1)
#define LO_NIBBLE(b) (((b) & 0x78) >> 3)

uint8_t count_set_bits(uint8_t b)
{
    uint8_t mask = 0x80;
    uint8_t count = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (b & mask)
            count++;
        mask >>= 1;
    }
    return count;
}

int write_byte_to_file(uint8_t b, int* charsDecodedCount, FILE *fpWrite) {
    int bytesWritten = fwrite(&b, sizeof(uint8_t), 1, fpWrite);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return -3;
    }

    (*charsDecodedCount)++;

    return 0;
}

bool is_corrupted(uint8_t b, uint8_t circleMask) {
    uint8_t byteToCheck = b & circleMask;
    // true for odd, false for even
    return count_set_bits(byteToCheck) % 2 != 0;
}

uint8_t repair_byte(uint8_t b) {
    bool isFirstCircleCorrupted = is_corrupted(b, 0x39);
    bool isSecondCircleCorrupted = is_corrupted(b, 0x5A);
    bool isThirdCircleCorrupted = is_corrupted(b, 0x74);

    if (isFirstCircleCorrupted)
    {
        if (isSecondCircleCorrupted)
        {
            if (isThirdCircleCorrupted) b ^= 0x10; // flip d1
            else b ^= 0x08; // flip d0
        }
        else
        {
            if (isThirdCircleCorrupted) b ^= 0x20; // flip d2
            else b ^= 0x01; // flip p0
        }
    }
    else
    {
        if (isSecondCircleCorrupted)
        {
            if (isThirdCircleCorrupted) b ^= 0x40; // flip d3
            else b ^= 0x02; // flip p1
        }
        else
        {
            if (isThirdCircleCorrupted) b ^= 0x04; // flip p2
        }
    }
    return b;
}

int decode_bytes_to_char(uint8_t b1, uint8_t b2, int* charsDecodedCount, FILE *fpWrite) {
    uint8_t MSB = HI_NIBBLE(repair_byte(b1));
    uint8_t LSB = LO_NIBBLE(repair_byte(b2));
    uint8_t ch = MSB | LSB;

    write_byte_to_file(ch, charsDecodedCount, fpWrite);

    return 0;
}

int decode_file(char* inputFileName, char* outputFileName, int* bytesReadCount, int* charsDecodedCount) {
	FILE *fpRead, *fpWrite;
    fpRead = fopen(inputFileName, "rb");
    fpWrite = fopen(outputFileName, "wb");

    if (fpRead == NULL)
    {
        printf("Cannot read input file.\n");
        return -1;
    }
    if (fpWrite == NULL)
    {
        printf("Cannot write to output file.\n");
        return -2;
    }
    uint8_t bytes[2];
    while (fread(&bytes, 2, 1, fpRead) == 1) {
        (*bytesReadCount) += 2;
        decode_bytes_to_char(bytes[0], bytes[1], charsDecodedCount, fpWrite);
    }
    fclose(fpRead);
    fclose(fpWrite);

    return 0;
}
