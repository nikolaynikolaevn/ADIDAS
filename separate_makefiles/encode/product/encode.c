/* encode.c */

#include <stdio.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing argument.\n\nExpected format:\nencode inputfile outputfile");
        return -1;
    }
	
	int charsReadCount = 0, bytesEncodedCount = 0;

    encode_file(argv[1], argv[2], &charsReadCount, &bytesEncodedCount);
    printf("Read %d characters.\n", charsReadCount);
    printf("Encoded %d bytes.", bytesEncodedCount);

    return 0;
}
