/* channel.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "channel_functions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing argument.\n\nExpected format:\nchannel inputfile outputfile");
        return -1;
    }
	
	int bytesReadCount = 0, bytesEncodedCount = 0;
	int flippedBitCounts[8] = {0};

    srand(time(NULL));
    encode_file(argv[1], argv[2], &bytesReadCount, &bytesEncodedCount, flippedBitCounts);
    printf("Read %d bytes.\n", bytesReadCount);
    printf("Encoded %d bytes.\n\n", bytesEncodedCount);

    for (int i = 0; i < 8; i++)
        printf("Bits with position %d are flipped %d times.\n", i, flippedBitCounts[i]);

    return 0;
}
