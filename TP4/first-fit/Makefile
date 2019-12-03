firstFit: main.o malloc.o calloc.o free.o realloc.o 
		gcc $(CFLAGS) -o firstFit main.o malloc.o calloc.o free.o realloc.o

main.o: main.c
		gcc $(CFLAGS) -c main.c

malloc.o: malloc.c
		gcc $(CFLAGS) -c malloc.c

calloc.o: calloc.c
		gcc $(CFLAGS) -c calloc.c

free.o: free.c
		gcc $(CFLAGS) -c free.c

realloc.o: realloc.c
		gcc $(CFLAGS) -c realloc.c

.PHONY: clean
clean:
		rm -fv *.o firstFit