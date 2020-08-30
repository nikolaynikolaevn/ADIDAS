PN=decode

CFLAGS=-Wall -Werror -Iproduct

SHARED=product/functions.c

all: 
	gcc $(CFLAGS) product/$(PN).c $(SHARED) -o $(PN)
   
clean:
	@rm -rf $(PN)

valgrind: 
	valgrind ./$(PN)
