#ifndef ENCODE_FUNCTIONS_H
#define ENCODE_FUNCTIONS_H

void to_binary(uint8_t b);
uint8_t set_bit(uint8_t b, uint8_t pos);
uint8_t get_bit(uint8_t b, uint8_t pos);
int write_byte_to_file(uint8_t b, int* bytesEncodedCount, FILE *fpWrite);
int encode_nibble_byte(uint8_t b, int* bytesEncodedCount, FILE *fpWrite);
int encode_file(char* inputFileName, char* outputFileName, int* charsReadCount, int* bytesEncodedCount);

#endif /* ENCODE_FUNCTIONS_H */
