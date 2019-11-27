bestFit: main.o malloc.o  
		gcc $(CFLAGS) -o bestFit main.o malloc.o 

main.o: main.c
		gcc $(CFLAGS) -c main.c

malloc.o: malloc.c
		gcc $(CFLAGS) -c malloc.c

.PHONY: clean
clean:
		rm -fv *.o bestFit