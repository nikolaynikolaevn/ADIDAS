CFLAGS=-Wall -Werror -Iproduct

all: encode channel decode

encode: product/encode.c
	gcc $(CFLAGS) product/encode.c product/encode_functions.c -o encode

channel: product/channel.c
	gcc $(CFLAGS) product/channel.c product/channel_functions.c -o channel

decode: product/decode.c
	gcc $(CFLAGS) product/decode.c product/decode_functions.c -o decode
   
clean:
	@rm -rf encode channel decode

valgrind: 
	valgrind ./encode ./channel ./decode
