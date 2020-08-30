#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int write_byte_to_file(uint8_t b, FILE *fpWrite);
void to_binary(uint8_t b);
int corrupt_byte(uint8_t b, int* bytesEncodedCount, int* flippedBitCounts, FILE *fpWrite);
int encode_file(char* inputFileName, char* outputFileName, int* bytesReadCount, int* bytesEncodedCount, int* flippedBitCounts);

#endif /* FUNCTIONS_H */
