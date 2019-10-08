#Archivo Makefile que simplifica la compilacion

myshell: main.o prompt.o commands.o
		gcc $(CFLAGS) -o myshell main.o prompt.o commands.o

main.o: main.c
		gcc $(CFLAGS) -c main.c

prompt.o: prompt.c
		gcc $(CFLAGS) -c prompt.c

commands.o: commands.c
		gcc $(CFLAGS) -c commands.c

.PHONY: clean
clean:
		rm -fv *.o rdproc 