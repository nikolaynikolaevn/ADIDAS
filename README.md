# ADIDAS
Advanced Development for Internet where all Data Arrives Safely.

Simple handling of data transmission corruption.

This implementation will only work when there is no more than onecorrupted bit per byte.

This repository contains 3 sub-programs:

## encode

This program is responsible for encoding an input file.

For every byte from the inputfile, two bytes are generated and placed in the output file.

Byte 1 has the 4 databits + 3 parity bits of high nibble.

Byte 2 has the 4 databits + 3 parity bits of low nibble.

The program prints at the end how many characters are read and how many bytes are encoded.

Use: **encode** *inputfile outputfile*

## channel

This program is responsible for adding noise bits to the data.

For all bytes one random bit is flipped.

The program prints at the end how many bytes are read, how many bytes are encoded and how often each bit is flipped.

Use: **channel** *inputfile outputfile*

## decode

This program is responsible for error correction (the decoding) on a file.

The program prints at the end how many bytes are read and how many characters are decoded.

Use: **decode** *inputfile outputfile*


Developed as a personal assignment during the Fontys PRC1 course.
