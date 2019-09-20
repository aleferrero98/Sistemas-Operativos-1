#Archivo Makefile que simplifica la compilacion

rdproc: main.o stepA.o stepB.o stepC.o stepD.o
		gcc $(CFLAGS) -o rdproc main.o stepA.o stepB.o stepC.o stepD.o

main.o: main.c
		gcc $(CFLAGS) -c main.c

stepA.o: stepA.c
		gcc $(CFLAGS) -c stepA.c

stepB.o: stepB.c
		gcc $(CFLAGS) -c stepB.c

stepC.o: stepC.c
		gcc $(CFLAGS) -c stepC.c

stepD.o: stepD.c
		gcc $(CFLAGS) -c stepD.c

.PHONY: clean
clean:
		rm -fv *.o rdproc 