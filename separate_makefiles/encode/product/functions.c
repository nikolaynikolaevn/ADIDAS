#include <stdio.h>
#include "functions.h"

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

FILE *fpRead, *fpWrite;

void to_binary(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((b << i) & 0x80));
    }
    printf("\n");
}

uint8_t set_bit(uint8_t b, uint8_t pos)
{
    uint8_t tmp = 1 << pos;
    return b | tmp;
}

uint8_t get_bit(uint8_t b, uint8_t pos)
{
    uint8_t tmp = 1 << pos;
    return (b & tmp) >> pos;
}

int write_byte_to_file(uint8_t b, int* bytesEncodedCount) {
    int bytesWritten = fwrite(&b, sizeof(uint8_t), 1, fpWrite);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return -3;
    }

    (*bytesEncodedCount)++;

    return 0;
}

int encode_nibble_byte(uint8_t b, int* bytesEncodedCount) {
    printf("Before: ");
    to_binary(b);

    // Data bits
    int d0 = get_bit(b, 0);
    int d1 = get_bit(b, 1);
    int d2 = get_bit(b, 2);
    int d3 = get_bit(b, 3);

    // Encode

    // Parity bits
    int p0 = d0 ^ d1 ^ d2;
    printf("First parity bit: %d\n", p0);
    int p1 = d0 ^ d1 ^ d3;
    printf("Second parity bit: %d\n", p1);
    int p2 = d1 ^ d2 ^ d3;
    printf("Third parity bit: %d\n", p2);

    b <<= 3; // Shift 3 bits to the left to make space for parity bits

    // Check if parity bits are set. If yes, set them in the encoded byte.
    if (p0 == 1)
        b = set_bit(b, 0);
    if (p1 == 1)
        b = set_bit(b, 1);
    if (p2 == 1)
        b = set_bit(b, 2);

    write_byte_to_file(b, bytesEncodedCount);

    printf("\nAfter:  ");
    to_binary(b);

    return 0;
}

int encode_file(char* inputFileName, char* outputFileName, int* charsReadCount, int* bytesEncodedCount) {
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
    uint8_t b;
    while (fread(&b, sizeof(uint8_t), 1, fpRead) != 0) {
        (*charsReadCount)++;
        printf("Char %c\n\n", b);

        printf("High nibble\n");
        encode_nibble_byte(HI_NIBBLE(b), bytesEncodedCount);

        printf("\nLow nibble\n");
        encode_nibble_byte(LO_NIBBLE(b), bytesEncodedCount);
    }
    fclose(fpRead);
    fclose(fpWrite);

    return 0;
}
