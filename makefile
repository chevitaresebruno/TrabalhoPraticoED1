all: mainFile

mainFile: main.o patient.o exam.o
	gcc -o mainFile main.o patient.o exam.o

main.o: main.c patient.h exam.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

patient.o: patient.c patient.h
	gcc -o patient.o patient.c -c -W -Wall -ansi -pedantic

exam.o: exam.c exam.h
	gcc -o exam.o exam.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ mainFile

.PHONY: all clean