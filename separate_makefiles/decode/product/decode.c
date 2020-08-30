#include <stdio.h>
#include "functions.h"

int bytesReadCount = 0, charsDecodedCount = 0;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing argument.\n\nExpected format:\ndecode inputfile outputfile");
        return -1;
    }

    decode_file(argv[1], argv[2], &bytesReadCount, &charsDecodedCount);
    printf("Read %d bytes.\n", bytesReadCount);
    printf("Decoded %d characters.", charsDecodedCount);

    return 0;
}
