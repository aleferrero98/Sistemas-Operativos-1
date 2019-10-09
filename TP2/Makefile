#Archivo Makefile que simplifica la compilacion

myshell: main.o prompt.o commands.o program.o batchFile.o
		gcc $(CFLAGS) -o myshell main.o prompt.o commands.o program.o batchFile.o

main.o: main.c
		gcc $(CFLAGS) -c main.c

prompt.o: prompt.c
		gcc $(CFLAGS) -c prompt.c

commands.o: commands.c
		gcc $(CFLAGS) -c commands.c

program.o: program.c
		gcc $(CFLAGS) -c program.c

batchFile.o: batchFile.c
		gcc $(CFLAGS) -c batchFile.c

.PHONY: clean
clean:
		rm -fv *.o rdproc 