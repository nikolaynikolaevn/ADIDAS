#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef int bool;
#define true 1
#define false 0

uint8_t count_set_bits(uint8_t b);
int write_byte_to_file(uint8_t b, int* charsDecodedCount, FILE *fpWrite);
bool is_corrupted(uint8_t b, uint8_t circleMask);
uint8_t repair_byte(uint8_t b);
int decode_bytes_to_char(uint8_t b1, uint8_t b2, int* charsDecodedCount, FILE *fpWrite);
int decode_file(char* inputFileName, char* outputFileName, int* bytesReadCount, int* charsDecodedCount);

#endif /* FUNCTIONS_H */
