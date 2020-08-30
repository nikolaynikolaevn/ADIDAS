/* channel_functions.c */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "channel_functions.h"

int write_byte_to_file(uint8_t b, FILE *fpWrite) {
    int bytesWritten = fwrite(&b, sizeof(uint8_t), 1, fpWrite);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return -3;
    }

    return 0;
}

void to_binary(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((b << i) & 0x80));
    }
    printf("\n");
}

int corrupt_byte(uint8_t b, int* bytesEncodedCount, int* flippedBitCounts, FILE *fpWrite) {
    // printf("Before: ");
    // to_binary(b);

    // Encode

    // Toggle a random bit
    int randomNumber = rand();
    int randomBitPosition = randomNumber % 8; // 0 to 7
    b ^= 1 << randomBitPosition;

    // Increment count of flipped bits on this position
    (flippedBitCounts[randomBitPosition])++;

    write_byte_to_file(b, fpWrite);

    // printf("\nAfter:  ");
    // to_binary(b);

    (*bytesEncodedCount)++;

    return 0;
}

int encode_file(char* inputFileName, char* outputFileName, int* bytesReadCount, int* bytesEncodedCount, int* flippedBitCounts) {
	FILE *fpRead, *fpWrite;
    fpRead = fopen(inputFileName, "rb");
    fpWrite = fopen(outputFileName, "wb");
    uint8_t b;

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
    while (fread(&b, sizeof(uint8_t), 1, fpRead) != 0) {
        (*bytesReadCount)++;
        // printf("Char %c\n\n", b);
        corrupt_byte(b, bytesEncodedCount, flippedBitCounts, fpWrite);
    }
    fclose(fpRead);
    fclose(fpWrite);

    return 0;
}
